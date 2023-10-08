#include "ImageManager.h"
#include "Buffers.h"
#include "Images.h"
#include "utils.h"
#include "CleanupManager.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <array>

static std::vector<std::function<void(void)> > callbacks;       //to be called when pushToGPU complete
static std::map<std::string, Image*> _imgmap;
static VulkanContext* ctx;


namespace ImageManager{

bool initialized()
{
    return ctx != nullptr;
}

void initialize(VulkanContext* ctx_){
    if(initialized())
        return;
    ctx=ctx_;
}

Image* load(std::string filename)
{
    auto it = _imgmap.find(filename);
    if(it!=_imgmap.end()){
        if( it->second->format != VK_FORMAT_R8G8B8A8_UNORM ||
            it->second->viewType != VK_IMAGE_VIEW_TYPE_2D_ARRAY){
                throw std::runtime_error("Two images have the same name but different formats: "+filename);
        }
        return it->second;
    }

    std::vector<char> pix = utils::readFile(filename);
    auto tmp = imagedecode::decode(pix);
    int width = std::get<0>(tmp);
    int height = std::get<1>(tmp);
    if( std::get<2>(tmp) != "RGBA8" ){
        throw std::runtime_error("Bad image format: Got "+std::get<2>(tmp)+" but expected RGBA8");
    }

    std::vector< std::span<const char> > layerData{
        { std::get<3>(tmp).data(), std::get<3>(tmp).data()+std::get<3>(tmp).size()}
    };

    Image* img = new Image(
        width,height,(int)layerData.size(),
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT,
        0,      //flags
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        VK_IMAGE_ASPECT_COLOR_BIT,
        layerData,
        filename
    );

    _imgmap[filename]=img;
    //~ _offset = img->startingOffset+img->byteSize;
    return img;
}

Image* loadFromData(const std::vector<char>& data, std::string name)
{
    return loadFromData(std::span<const char>(data.data(), data.data()+data.size()), name );
}

Image* loadFromData(std::span<const char> data, std::string name)
{
    std::map<std::string,Image*>::iterator it = _imgmap.find(name);
    if(it!=_imgmap.end()){
        if( it->second->format != VK_FORMAT_R8G8B8A8_UNORM ||
            it->second->viewType != VK_IMAGE_VIEW_TYPE_2D_ARRAY){
                throw std::runtime_error("Two images have the same name but different formats: "+name);
        }
        return it->second;
    }

    auto tmp = imagedecode::decode(data);
    int width = std::get<0>(tmp);
    int height = std::get<1>(tmp);
    assert(std::get<2>(tmp) == "RGBA8");
    std::vector<std::span<const char>> layerData(1);
    layerData[0] = std::get<3>(tmp);

    Image* img = new Image(
        width,height,(int)layerData.size(),
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT,
        0,      //flags
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        VK_IMAGE_ASPECT_COLOR_BIT,
        layerData,
        name
    );


    //~ auto img = new Images::BufferImage(data,_offset);
    //~ _offset = img->startingOffset+img->byteSize;
    _imgmap[name]=img;
    return img;
}

Image* createSolidColorImage(float r, float g, float b, float a){

    std::ostringstream oss;
    oss << r << "," << g << "," << b << "," << a;
    std::string name = oss.str();
    auto it = _imgmap.find(name);
    if(it!=_imgmap.end()){
        if( it->second->format != VK_FORMAT_R8G8B8A8_UNORM ||
            it->second->viewType != VK_IMAGE_VIEW_TYPE_2D_ARRAY){
                throw std::runtime_error("Two images have the same name but different formats: "+name);
        }
        return it->second;
    }

    std::uint8_t r_ = std::uint8_t(r*255);
    std::uint8_t g_ = std::uint8_t(g*255);
    std::uint8_t b_ = std::uint8_t(b*255);
    std::uint8_t a_ = std::uint8_t(a*255);
    std::vector<char> tmp{ char(r_), char(g_), char(b_), char(a_) };
    std::vector<std::span<const char>> T{
        {
            tmp.data(), tmp.data()+tmp.size()
        }
    };

    Image* img = new Image(
        1,1,1,
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT,
        0,      //flags
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        VK_IMAGE_ASPECT_COLOR_BIT,
        T,
        name
    );

    //~ _offset = img->startingOffset+img->byteSize;
    _imgmap[name]=img;
    return img;
}

Image* loadCube(std::array<std::string,6> filenames)
{
    std::string name;
    for(auto& f: filenames)
        name += f+" / ";

    auto it = _imgmap.find(name);
    if(it!=_imgmap.end()){
        if( it->second->format != VK_FORMAT_R8G8B8A8_UNORM ||
            it->second->viewType != VK_IMAGE_VIEW_TYPE_CUBE){
                throw std::runtime_error("Two images have the same name but different formats: "+name);
        }
        return it->second;
    }
    std::vector< std::vector<char> > layerData(6);
    int width=-1,height=-1;
    for(int i=0;i<6;++i){
        std::vector<char> pix = utils::readFile(filenames[i]);
        auto tmp = imagedecode::decode(pix);
        int w = std::get<0>(tmp);
        int h = std::get<1>(tmp);
        assert(std::get<2>(tmp) == "RGBA8");

        if( w != h ){
            throw std::runtime_error("Non-square cubemap image: "+filenames[i]);
        }

        if( i == 0 ){
            width=w;
            height=h;
        } else{
            if(w!=width || h !=height){
                throw std::runtime_error("Mismatched cubemap image size: Expected "+
                    std::to_string(width)+"x"+std::to_string(height)+" but image "+
                    filenames[i]+" is size "+std::to_string(w)+"x"+std::to_string(h));
            }
        }
        layerData[i].swap(std::get<3>(tmp));
    }

    std::vector<std::span<const char> >layers;
    for(int i=0;i<6;++i){
        layers.push_back( {
            layerData[i].data(),
            layerData[i].data()+layerData[i].size()
        });
    }

    Image* img = new Image(
        width,height,(int)layers.size(),
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT,
        VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT,      //flags
        VK_IMAGE_VIEW_TYPE_CUBE,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        VK_IMAGE_ASPECT_COLOR_BIT,
        layers,
        name
    );

    _imgmap[name] = img;
    return img;
}


Image* createUninitializedImage(
    int w, int h, int numLayers,
    VkFormat format, VkImageUsageFlags usage,
    VkImageViewType viewType,
    VkImageLayout finalLayout, VkImageAspectFlags aspect,
    std::string name
){

    Image* img = new Image(
        w,h,numLayers,
        format,
        usage,
        VkImageCreateFlags(0),       //flags
        viewType,       //VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        finalLayout,    //VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        aspect,         //VK_IMAGE_ASPECT_COLOR_BIT,
        std::vector<std::span<const char>>(),
        name
    );

    std::string unique = "$uninitialized" + std::to_string(_imgmap.size());
    _imgmap[unique]=img;
    return img;
}


void pushToGPU()
{

    //compute size parameters for all the images
    std::vector<VkDeviceSize> sizes;
    std::vector<VkDeviceSize> offsets;
    sizes.reserve(_imgmap.size());
    offsets.reserve(_imgmap.size());

    VkDeviceSize offset=0;
    VkDeviceSize largestImageSize=0;

    Image* img=nullptr;

    for(auto& it : _imgmap){
        img = it.second;

        if( img->pushedToGPU() )
            continue;

        int padding = utils::computePadding(
            offset,
            (int)img->memoryRequirements.alignment
        );
        offset += padding;

        offsets.push_back(offset);
        sizes.push_back(img->memoryRequirements.size);

        offset += sizes.back();
        largestImageSize = std::max( sizes.back(), largestImageSize );
    }

    if( img == nullptr ){
        //no images need to be transferred
        return;
    }

    VkDeviceMemory memory = Buffers::allocateMemory(
        ctx,
        img->memoryRequirements.memoryTypeBits,     //OK to use any image's memory requirements here
        offset,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        "ImageManager"
    );

    CleanupManager::registerCleanupFunction( [memory](){
        vkFreeMemory( ctx->dev, memory, nullptr );
    });

    StagingBuffer* stagingBuffer = new StagingBuffer(ctx,nullptr,largestImageSize,"ImageManager staging");
    int idx=0;
    for(auto& it : _imgmap){
        img = it.second;
        if(img->pushedToGPU())
            continue;
        img->copyDataToGPU(
            stagingBuffer,
            memory,
            offsets[idx]
        );
        idx++;
    }

    stagingBuffer->cleanup();
    delete stagingBuffer;

    for(auto& f : callbacks){
        f();
    }
}

void addCallback( std::function<void(void)> f)
{
    callbacks.push_back(f);
}


}; //namespace
