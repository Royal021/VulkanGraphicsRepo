#include "Descriptors.h"
#include "Pipeline.h"
#include "mischelpers.h"
#include "CleanupManager.h"
#include "consoleoutput.h"
#include "utils.h"
#include <list>
#include <cassert>
#include <iostream>

static std::map<int, VkDescriptorSet> currentBindings;

static VkDescriptorPool _makePool(VulkanContext* ctx, unsigned num)
{
    std::vector<VkDescriptorPoolSize> PPS {
        VkDescriptorPoolSize{ .type=VK_DESCRIPTOR_TYPE_SAMPLER                  , .descriptorCount=num },
        VkDescriptorPoolSize{ .type=VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE            , .descriptorCount=num },
        VkDescriptorPoolSize{ .type=VK_DESCRIPTOR_TYPE_STORAGE_IMAGE            , .descriptorCount=num },
        VkDescriptorPoolSize{ .type=VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER     , .descriptorCount=num },
        VkDescriptorPoolSize{ .type=VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER     , .descriptorCount=num },
        VkDescriptorPoolSize{ .type=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER           , .descriptorCount=num },
        VkDescriptorPoolSize{ .type=VK_DESCRIPTOR_TYPE_STORAGE_BUFFER           , .descriptorCount=num },
        VkDescriptorPoolSize{ .type=VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT         , .descriptorCount=num }
        //~ VkDescriptorPoolSize{ .descriptorCount=_POOLSIZE,   .type=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER  },
    };

    VkDescriptorPool pool;
    check(vkCreateDescriptorPool(
        ctx->dev,
        VkDescriptorPoolCreateInfo{
            .sType=VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .maxSets=num,
            .poolSizeCount=unsigned(PPS.size()),
            .pPoolSizes=PPS.data()
        },
        nullptr,
        &(pool)
    ));
    return pool;
}
    

DescriptorSetLayout::DescriptorSetLayout( VulkanContext* ctx_, 
        const std::vector< DescriptorSetEntry >& entries_)
{
    this->ctx=ctx_;
    this->entries = entries_;
    std::vector<VkDescriptorSetLayoutBinding> L;
    int maxSlot=-1;
    for(const DescriptorSetEntry& e : entries ){
        maxSlot = std::max(e.slot,maxSlot);
        L.push_back(
            VkDescriptorSetLayoutBinding{
                .binding=(unsigned)e.slot,
                .descriptorType=e.type,
                .descriptorCount=1,
                .stageFlags=VK_SHADER_STAGE_ALL,
                .pImmutableSamplers=nullptr
            }
        );
    }
    this->types.resize(maxSlot+1, VK_DESCRIPTOR_TYPE_MAX_ENUM );
    //~ this->typeNames.resize(this->types.size());
    for(const DescriptorSetEntry& e : entries ){
        this->types[e.slot] = e.type;
        //~ switch(e.type){
            //~ case VK_DESCRIPTOR_TYPE_SAMPLER:  this->typeNames[e.slot]="VkSampler"; break;
            //~ case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:  this->typeNames[e.slot]="VkImageView (for sampled image)"; break;
            //~ case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:  this->typeNames[e.slot]="VkImageView (for storage image)"; break;
            //~ case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:  this->typeNames[e.slot]="VkBufferView (for uniform texel buffer)"; break;
            //~ case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:  this->typeNames[e.slot]="VkBufferView (for storage texel buffer)"; break;
            //~ case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:  this->typeNames[e.slot]="VkBuffer (for uniform buffer)"; break;
            //~ case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:  this->typeNames[e.slot]="VkBuffer (for storage buffer)"; break;
            //~ case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:  this->typeNames[e.slot]="VkImageView (for input attachment)"; break;
            //~ case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:  this->typeNames[e.slot]="VkImageView (for combined image sampler)"; break;
            //~ case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:  this->typeNames[e.slot]="VkBuffer (for uniform buffer dynamic)"; break;
            //~ case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:  this->typeNames[e.slot]="VkBuffer (for storage buffer dynamic)"; break;
            //~ default: this->typeNames[e.slot] = "Unknown type";
        //~ }
    };
    
    check(vkCreateDescriptorSetLayout(
        ctx->dev,
        VkDescriptorSetLayoutCreateInfo{
            .sType=VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .bindingCount=(unsigned)L.size(),
            .pBindings=L.data()
        },
        nullptr,
        &(this->layout)
    ));

    CleanupManager::registerCleanupFunction( [this](){
        vkDestroyDescriptorSetLayout(this->ctx->dev, this->layout, nullptr);
    });

}

void DescriptorSetFactory::cleanup()
{
    for(VkDescriptorPool& p : this->pools ){
        vkDestroyDescriptorPool(this->ctx->dev,p,nullptr);
    }
}
    
DescriptorSetFactory::DescriptorSetFactory(VulkanContext* ctx_, 
    std::string name_,
    int bindingPoint_,
    PipelineLayout* pipelineLayout_
){
    assert(pipelineLayout_);
    this->name=name_;
    this->ctx=ctx_;
    this->bindingPoint=bindingPoint_;
    this->pipelineLayout = pipelineLayout_;
    assert(bindingPoint >= 0 );
    assert(bindingPoint < (int)pipelineLayout->descriptorSetLayouts.size());
    this->layout=pipelineLayout->descriptorSetLayouts[bindingPoint];
    CleanupManager::registerCleanupFunction( [this](){
        for( VkDescriptorPool p : this->pools ){
            vkDestroyDescriptorPool(
                this->ctx->dev,
                p,
                nullptr
            );
        }
    });
            
}
    
//~ void DescriptorSetFactory::setPipelineLayout(VkPipelineLayout pipelineLayout)
//~ {
    //~ this->pipelineLayout = pipelineLayout;
//~ }

DescriptorSet* DescriptorSetFactory::make()
{
    DescriptorSet* ds = new DescriptorSet(
        this->ctx,
        this->bindingPoint,
        this->layout,
        this->pipelineLayout,
        this,
        "descriptor set from "+this->name
    );
    this->sets.push_back(ds);
    return ds;
}

//called by DescriptorSet 
VkDescriptorSet DescriptorSetFactory::allocate()
{
    if( this->numLeft < (int)this->layout->entries.size() ){
        unsigned num = unsigned(this->layout->entries.size()*16);
        this->pools.push_back( _makePool(this->ctx, (unsigned)num ) );
        ctx->setObjectName(this->pools.back(),"factory{"+this->name+"}["+std::to_string(this->pools.size()-1)+"]");
        this->numLeft = num;
    }
    
    VkDescriptorSet dset;
    check(vkAllocateDescriptorSets( 
        ctx->dev, 
        VkDescriptorSetAllocateInfo{
            .sType=VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .pNext=nullptr,
            .descriptorPool=this->pools.back(),
            .descriptorSetCount=1,
            .pSetLayouts=&(layout->layout)
        },
        &dset
    ));
    this->numLeft -= (int)this->layout->entries.size();

    assert(this->pipelineLayout != VK_NULL_HANDLE );
   
    return dset;
}

DescriptorSet::DescriptorSet(
        VulkanContext* ctx_, int bindingPoint_,
        DescriptorSetLayout* descriptorSetLayout_,
        PipelineLayout* pipelineLayout_,
        DescriptorSetFactory* factory_,
        std::string name_)
{
    this->ctx=ctx_;
    this->descriptorSetLayout=descriptorSetLayout_;
    this->pipelineLayout=pipelineLayout_;
    this->bindingPoint = bindingPoint_;
    this->factory=factory_;
    this->name=name_;
    utils::registerFrameCompleteCallback( [this](unsigned frameNumber){
        if( this->activeDescriptorSets.contains(frameNumber) ){
            this->availableDescriptorSets.insert(
                this->availableDescriptorSets.end(),
                this->activeDescriptorSets[frameNumber].begin(),
                this->activeDescriptorSets[frameNumber].end()
            );
            this->activeDescriptorSets.erase(frameNumber);
        }
    });
    
    int largestSlot = 0;
    for(DescriptorSetEntry& e : this->descriptorSetLayout->entries ){
        largestSlot = std::max(largestSlot,e.slot);
    }
    this->needsBind.resize(largestSlot+1,false);
}
  
    
//~ void DescriptorSet::bind(VkCommandBuffer cmd)
//~ {
    //~ vkCmdBindDescriptorSets( 
        //~ cmd,
        //~ VK_PIPELINE_BIND_POINT_GRAPHICS, 
        //~ this->pipelineLayout->pipelineLayout,
        //~ this->bindingPoint,             //first descriptor set
        //~ 1,                              //number of sets
        //~ &this->descriptorSet,           //things to bind
        //~ 0,                              //number of dynamic descriptors
        //~ nullptr                         //dynamic offsets
    //~ );
//~ }
     
//~ static void _checkWrite( 
    //~ VkDescriptorType expectedType,
    //~ const std::string& expectedTypeName,
    //~ const std::initializer_list<VkDescriptorType>& compatibleTypes,
    //~ const char* suppliedTypename
//~ ){
    //~ for(auto& t : compatibleTypes ){
        //~ if( t == expectedType )
            //~ return;
    //~ }
    //~ throw std::runtime_error( std::string("Bad type for item: Expected ")+
        //~ expectedTypeName + " but got "+suppliedTypename);
//~ }     

//~ static
//~ void setSlotHelper( VulkanContext* ctx, int slot, VkImageView item, 
                    //~ VkDescriptorType expected, 
                    //~ const std::string& expectedTypeName,
                    //~ VkDescriptorSet descriptorSet)
//~ {
    //~ _checkWrite(expected, expectedTypeName,
        //~ {
            //~ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 
            //~ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 
            //~ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT
        //~ },
        //~ "VkImageView"
    //~ );
    
    //~ //FIXME: What layout should storage images be in?
    //~ VkDescriptorImageInfo ii{
        //~ .sampler=VK_NULL_HANDLE,
        //~ .imageView=item,
        //~ .imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    //~ };
    
    //~ VkWriteDescriptorSet wr{
        //~ .sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        //~ .pNext=nullptr,
        //~ .dstSet=descriptorSet, 
        //~ .dstBinding=(unsigned)slot,
        //~ .dstArrayElement=0,
        //~ .descriptorCount=1,
        //~ .descriptorType=expected,
        //~ .pImageInfo=&ii,
        //~ .pBufferInfo=nullptr,
        //~ .pTexelBufferView=nullptr
    //~ };
    //~ vkUpdateDescriptorSets( ctx->dev, 
        //~ 1, &wr,
        //~ 0, nullptr      //ones to copy
    //~ );
//~ }

//~ static
//~ void setSlotHelper( VulkanContext* ctx, int slot, VkSampler item, 
                    //~ VkDescriptorType expected,
                    //~ const std::string& expectedTypeName,
                    //~ VkDescriptorSet descriptorSet)
//~ {
    //~ _checkWrite(expected, expectedTypeName,
        //~ {
            //~ VK_DESCRIPTOR_TYPE_SAMPLER, 
        //~ },
        //~ "VkSampler"
    //~ );
    
    //~ VkDescriptorImageInfo ii{
        //~ .sampler=item,
        //~ .imageView=nullptr,
        //~ .imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL   //ignored
    //~ };
    //~ VkWriteDescriptorSet wr{
        //~ .sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        //~ .pNext=nullptr,
        //~ .dstSet=descriptorSet, 
        //~ .dstBinding=(unsigned)slot,
        //~ .dstArrayElement=0,
        //~ .descriptorCount=1,
        //~ .descriptorType=expected,
        //~ .pImageInfo=&ii,
        //~ .pBufferInfo=nullptr,
        //~ .pTexelBufferView=nullptr
    //~ };
    //~ vkUpdateDescriptorSets( ctx->dev, 
        //~ 1, &wr,
        //~ 0, nullptr      //ones to copy
    //~ );
//~ }
 

//~ static
//~ void setSlotHelper( VulkanContext* ctx, int slot, VkBufferView item, 
                    //~ VkDescriptorType expected,
                    //~ const std::string& expectedTypeName,
                    //~ VkDescriptorSet descriptorSet)
//~ {
   
//~ }
  

//~ static
//~ void setSlotHelper( VulkanContext* ctx, int slot, VkBuffer item, 
                    //~ VkDescriptorType expected,
                    //~ const std::string& expectedTypeName,
                    //~ VkDescriptorSet descriptorSet)
//~ {
    //~ _checkWrite(expected,expectedTypeName,
        //~ {
            //~ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            //~ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 
        //~ },
        //~ "VkBuffer"
    //~ );
    
    //~ VkDescriptorBufferInfo info{
        //~ .buffer=item,
        //~ .offset=0,
        //~ .range=VK_WHOLE_SIZE
    //~ };
    
    //~ VkWriteDescriptorSet wr{
        //~ .sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        //~ .pNext=nullptr,
        //~ .dstSet=descriptorSet, 
        //~ .dstBinding=(unsigned)slot,
        //~ .dstArrayElement=0,
        //~ .descriptorCount=1,
        //~ .descriptorType=expected,
        //~ .pImageInfo=nullptr,
        //~ .pBufferInfo=&info,
        //~ .pTexelBufferView=nullptr
    //~ };
    //~ vkUpdateDescriptorSets( ctx->dev, 
        //~ 1, &wr,
        //~ 0, nullptr      //ones to copy
    //~ );
//~ }

void DescriptorSet::bind(VkCommandBuffer cmd)
{
    this->bind(cmd,{VK_PIPELINE_BIND_POINT_GRAPHICS,VK_PIPELINE_BIND_POINT_COMPUTE});
}

void DescriptorSet::bind(VkCommandBuffer cmd, std::initializer_list<VkPipelineBindPoint> bindPoints)
{
    if( this->currentDescriptorSet == VK_NULL_HANDLE ){
        //make a new set and initialize it with the most recently
        //used options
        this->ensureCurrentIsValid();
    }

    //FIXME: Check for partially initialized set?
    this->activeDescriptorSets[utils::getCurrentFrameIdentifier()].push_back(
        this->currentDescriptorSet);
  
    for(VkPipelineBindPoint p : bindPoints ){
        vkCmdBindDescriptorSets( 
            cmd,
            p, 
            this->pipelineLayout->pipelineLayout,
            this->bindingPoint,             //first descriptor set
            1,                              //number of sets
            &this->currentDescriptorSet,    //things to bind
            0,                              //number of dynamic descriptors
            nullptr                         //dynamic offsets
        );
    }
      
    this->currentDescriptorSet = VK_NULL_HANDLE;
    
    currentBindings[this->bindingPoint] = this->currentDescriptorSet;
    
    for(int i=0;i<(int)this->needsBind.size();++i){
        this->needsBind[i]=false;
    }
}

class DescriptorTypeError : public std::runtime_error
{
  public:
    DescriptorTypeError(int slot, std::string providedType, std::string expectedType) :
        runtime_error( "Bad type for write to descriptor set slot "+
            std::to_string(slot)+": Expected "+expectedType+" but got "+
            providedType )
    {}
};


static
void setWriteInfo( VkDescriptorImageInfo& ii, VkDescriptorBufferInfo& , VkBufferView& , VkSampler item)
{
    ii.sampler = item; 
}

static
void setWriteInfo( VkDescriptorImageInfo& ii, VkDescriptorBufferInfo& , VkBufferView& , VkImageView item)
{
    ii.imageView = item; 
    ii.imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
}

static
void setWriteInfo( VkDescriptorImageInfo& , VkDescriptorBufferInfo& bi, VkBufferView& , VkBuffer item)
{
    bi.buffer = item;
    bi.offset = 0;
    bi.range = VK_WHOLE_SIZE;
}


static
void setWriteInfo( VkDescriptorImageInfo& , VkDescriptorBufferInfo& , VkBufferView& bv, VkBufferView item)
{
    bv=item;
}

template<typename T>
void DescriptorSet::setSlotDoIt(int slot, const T& item)
{
    if(slot<0){
        throw std::runtime_error("Bad slot: Must be non-negative");
    }
    
    if( slot >= (int)this->descriptorSetLayout->types.size() ){
        throw std::runtime_error("Bad slot: Too large (must be less than "+
            std::to_string(this->descriptorSetLayout->types.size())+ ")" );
    }

    if( (int)this->currentResources.size() <= slot ){
        this->currentResources.resize( slot+1, Empty() );
    }
    
    if( this->needsBind[slot] ){
        warn("Descriptor set slot",slot,"was updated without bind() being called.",
        "Did you forget to call bind()?");
    }
    
    this->ensureCurrentIsValid();
    
    assert( this->currentDescriptorSet != VK_NULL_HANDLE);
    
    auto expected =  this->descriptorSetLayout->types[slot];  //expected type
    switch(expected){
        case VK_DESCRIPTOR_TYPE_SAMPLER:    
            if( !std::is_same<VkSampler,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkSampler");
            break;
        case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
            if( !std::is_same<VkImageView,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkImageView (for sampled image)");
            break;
        case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
            if( !std::is_same<VkImageView,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkImageView (for storage image)");
            break;
        case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
            if( !std::is_same<VkBufferView,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkBufferView (for uniform texel buffer)");
            break;
        case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
            if( !std::is_same<VkBufferView,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkBufferView (for storage texel buffer)");
            break;
        case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
            if( !std::is_same<VkBuffer,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkBuffer (for uniform buffer)");
            break;
        case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
            if( !std::is_same<VkBuffer,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkBuffer (for storage buffer)");
            break;
        case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
            if( !std::is_same<VkBuffer,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkImageView (for input attachment)");
            break;
        case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
            if( !std::is_same<VkImageView,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkImageView (for combined image sampler)");
            assert(0);  //the setWriteInfo function needs to write both sampler and image info
            break;
        case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
            if( !std::is_same<VkBuffer,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkBuffer (for uniform buffer dynamic)");
            break;
        case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
            if( !std::is_same<VkBuffer,T>::value ) 
                throw DescriptorTypeError(slot,typeid(T).name(),"VkBuffer (for storage buffer dynamic)");
            break;
        default:
            assert(0);
    }
    
    VkDescriptorImageInfo ii{};
    VkDescriptorBufferInfo bi{};
    VkBufferView bv{};

    setWriteInfo( ii,bi,bv, item);
        
    VkWriteDescriptorSet wr{
        .sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .pNext=nullptr,
        .dstSet=this->currentDescriptorSet, 
        .dstBinding=(unsigned)slot,
        .dstArrayElement=0,
        .descriptorCount=1,
        .descriptorType=expected,
        .pImageInfo=&ii,
        .pBufferInfo=&bi,
        .pTexelBufferView=&bv
    };
    
    vkUpdateDescriptorSets( ctx->dev, 
        1, &wr,
        0, nullptr      //ones to copy
    );
    
    this->currentResources[slot] = item;
    this->needsBind[slot] = true;
}

void DescriptorSet::setSlot( int slot, VkImageView item ){
    this->setSlotDoIt(slot,item);
}

void DescriptorSet::setSlot( int slot, VkSampler item ){
    this->setSlotDoIt(slot,item);
}

void DescriptorSet::setSlot( int slot, VkBufferView item ){
    this->setSlotDoIt(slot,item);
}

void DescriptorSet::setSlot( int slot, VkBuffer item ){
    this->setSlotDoIt(slot,item);
}
 

void DescriptorSet::ensureCurrentIsValid(){
    if( this->currentDescriptorSet != VK_NULL_HANDLE )
        return;
    if( this->availableDescriptorSets.empty()){
        verbose("Allocating a descriptor set for",this->name);
        this->currentDescriptorSet = this->factory->allocate();
        this->ctx->setObjectName(this->currentDescriptorSet,this->name);
    } else {
        this->currentDescriptorSet = this->availableDescriptorSets.back();
        this->availableDescriptorSets.pop_back();
    }
    
    for(int i=0;i<(int)this->currentResources.size();++i){
        Resource r = this->currentResources[i];
        if( std::holds_alternative<VkImageView>(r) )
            this->setSlot(i, std::get<VkImageView>(r) );
        else if( std::holds_alternative<VkSampler>(r) )
            this->setSlot(i, std::get<VkSampler>(r) );
        else if( std::holds_alternative<VkBufferView>(r) )
            this->setSlot(i, std::get<VkBufferView>(r) );
        else if( std::holds_alternative<VkBuffer>(r) )
            this->setSlot(i, std::get<VkBuffer>(r) );
        else if( std::holds_alternative<Empty>(r) ){
            //leave alone
        } else {
            assert(0);
        }
    }

    for(int i=0;i<(int)this->needsBind.size();++i){
        this->needsBind[i]=false;
    }
    

}

//~ std::map<int, VkDescriptorSet> Descriptors::getCurrentBindings()
//~ {
    //~ return currentBindings;
//~ }

//~ void Descriptors::restoreBindings(VkCommandBuffer cmd, const std::map<int,VkDescriptorSet>& m){
    //~ //FIXME: How to handle for compute shaders?
    
    //~ for(auto& it : m ){
        //~ int bindPoint = it.first;
        //~ VkDescriptorSet dset = it.second;
        
        //~ vkCmdBindDescriptorSets( 
            //~ cmd,
            //~ VK_PIPELINE_BIND_POINT_GRAPHICS, 
            //~ this->pipelineLayout->pipelineLayout,
            //~ this->bindingPoint,             //first descriptor set
            //~ 1,                              //number of sets
            //~ &this->currentDescriptorSet,    //things to bind
            //~ 0,                              //number of dynamic descriptors
            //~ nullptr                         //dynamic offsets
        //~ );
        
//~ }
