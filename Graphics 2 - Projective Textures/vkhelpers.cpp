#include "vkhelpers.h"
#include "mischelpers.h"
#include "platform.h"
#include "imageencode.h"
#include "consoleoutput.h"
#include <SDL.h>
#include <SDL_vulkan.h>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <array>

static VkDebugUtilsMessengerEXT _setupDebugPrintCallback(VkInstance instance);

static std::tuple<VkImage, VkDeviceMemory, VkImageView> _makeDepthbufferImage(
        VkDevice dev, VkPhysicalDevice physdev,
        VkFormat format, int width, int height);

static VkImageView _makeSwapchainImageView(VkDevice dev, 
    VkImage swapchainImage, VkFormat format);

  
static std::tuple<       
    VkPhysicalDevice,VkPhysicalDeviceProperties,
    VkPhysicalDeviceFeatures,VkSurfaceFormatKHR,
    int,int>  
    _getPhysdev(
        VkSurfaceKHR surface,
        VkInstance instance,
        bool discreteOK, 
        bool integratedOK,
        bool cpuOK, 
        std::string forceGPU
);

static VkDebugUtilsMessengerEXT _setupDebugPrintCallback(VkInstance instance);
  
static std::tuple<VkInstance,bool>  _makeInstance(
    SDL_Window* win,
    bool useDebugUtils, bool withShaderPrintf, 
    bool useValidation);
         
static std::tuple<       
    VkPhysicalDevice,
    VkPhysicalDeviceProperties,
    VkPhysicalDeviceFeatures,
    VkSurfaceFormatKHR,
    int,
    int> _selectGPU(
        VkSurfaceKHR surf,
        std::vector<VkPhysicalDevice>& physdevs,
        std::string forceGPU,
        bool discreteOK,
        bool integratedOK,
        bool cpuOK);
        

//~ static bool _printPerformance=true;
static bool _printLoader=false;


template<typename ...T>
void _shader(T... args)
{
    print("SHADER: ",args...);
}


void check(int res){
    if(res != VK_SUCCESS){             
        std::ostringstream oss;
        oss << "VK call failed"; 
        throw std::runtime_error(oss.str());
    }                                                              
}

static VKAPI_ATTR VkBool32 VKAPI_CALL _debugCallback( 
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT dtype,
        const VkDebugUtilsMessengerCallbackDataEXT* data,
        void* )
{
    if(!data){
        error("debugCallback with data==null");
        return 0;
    }
    
    std::string msgname = (data->pMessageIdName ? data->pMessageIdName : "");
    auto msgid = data->messageIdNumber;
    auto msg = ( data->pMessage ? data->pMessage : "(no message)");
    std::vector<VkDebugUtilsLabelEXT> queueLabels;
    for(unsigned i=0;i<data->queueLabelCount;++i){
        queueLabels.push_back( data->pQueueLabels[i] );
    }
    std::vector<VkDebugUtilsLabelEXT> cmdLabels;
    for(unsigned i=0;i<data->cmdBufLabelCount;++i){
        cmdLabels.push_back( data->pCmdBufLabels[i] );
    }
    std::vector<VkDebugUtilsObjectNameInfoEXT> objects;
    for(unsigned i=0;i<data->objectCount;++i){
        objects.push_back( data->pObjects[i] );
    }
     
    
    static std::set<int> performancePrinted;
    
    if(dtype & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT){
        if(performancePrinted.find(msgid) != performancePrinted.end() ){
            return 0;
        }
        performancePrinted.insert(msgid);
    }
    
    std::string pfx;
    bool exc=false;
    
    if(msgname.find("Loader Message") == 0 ){
        if(! _printLoader ){
            return 0;
        }
    }
    
    PrintStyle pstyle = PrintStyle::WHITE;
    
    if(severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT){
        pfx+="ERROR:   ";
        pstyle = PrintStyle::RED;
        exc=true;
    } else if( severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT ){
        pfx+="WARNING: ";
        pstyle = PrintStyle::YELLOW;
    } else if( severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT ){
        pfx+="INFO:    ";
        pstyle = PrintStyle::GREEN;
    } else if( severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT){
        pfx+="VERBOSE: ";
        pstyle = PrintStyle::DARKGREY;
    } else {
        pfx+="NOTE:    ";
    }
    
    if(dtype & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT){
    }
    if(dtype & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT){
        //pfx = "(Validation) " + pfx;
    }
    if(dtype & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT){
        pfx = "SPEED:  ";
        pstyle = PrintStyle::PURPLE;
    }
    
    if(msgname == "UNASSIGNED-DEBUG-PRINTF"){
        //from a shader printf
        pfx="SHADER:   ";
        msgname="PRINTF:";
        pstyle = PrintStyle::CYAN;
    } else {
    }
    
    std::vector<std::string> names;
    for(auto& ob : objects ){
        if(ob.pObjectName){
            names.push_back( ob.pObjectName );
        }
    }
    
    std::string nametext;
    if(!names.empty()){
        nametext = "Involved Objects:";
        bool first=true;
        for(auto& n : names ){
            if(!first)
                nametext += ", ";
            first=false;
            nametext+= n;
        }
    } else
        nametext = "";
    
    if(exc){
        print("");
        print("=======================================================");
    }
    printWrap(pstyle,pfx,msgname,msg,nametext );
    if(exc){
        print("=======================================================");
        print("");
    }

    if(exc){
        std::string m;
        if(msg)
            m = msg;
        auto pipeindex = m.rfind("|");
        if(pipeindex != std::string::npos){
            m = m.substr(pipeindex);
        }
        throw std::runtime_error(m);
    }
    
    return 0;
}
      

VulkanContext::VulkanContext(SDL_Window* win, VkPhysicalDeviceFeatures featuresToEnable,
        int numSubpasses): config("config.ini")
{
    bool withShaderPrintf=(this->config.get("shaderPrintf","yes") != "no");
    bool withDebugPrint=(this->config.get("debugPrint","yes") != "no");
    bool withGPUValidation=(this->config.get("gpuValidation","no") != "no");
    bool discreteOK=(this->config.get("useDiscreteGPU","yes") != "no");
    bool integratedOK=(this->config.get("useIntegratedGPU","yes") != "no");
    bool cpuOK=(this->config.get("useCPU","yes") != "no");
    _useColors=(this->config.get("useColor","yes") != "no");
    std::string forceGPU = this->config.get("forceGPU","");
    _printVerbose = this->config.get("printVerbose","no") != "no";
    _printInfo = this->config.get("printInfo","yes") != "no";
    _printWarnings = this->config.get("printWarnings","yes") != "no";
    _printErrors = this->config.get("printErrors","yes") != "no";
    _printLoader = this->config.get("printLoader","no") != "no";
    
    //these only control if we *can* use the specified extension.
    //we still need to verify that it's available.
    bool useValidation = (this->config.get("useValidation","yes") != "no");
    bool useDebugUtils = (this->config.get("useDebugUtils","yes") != "no");

    auto pmode = this->config.get("presentMode","VK_PRESENT_MODE_FIFO_KHR");
    std::map<std::string, VkPresentModeKHR> presentModes={ 
        { "VK_PRESENT_MODE_IMMEDIATE_KHR"   , VK_PRESENT_MODE_IMMEDIATE_KHR     },
        { "VK_PRESENT_MODE_MAILBOX_KHR"     , VK_PRESENT_MODE_MAILBOX_KHR       },
        { "VK_PRESENT_MODE_FIFO_KHR"        , VK_PRESENT_MODE_FIFO_KHR          },
        { "VK_PRESENT_MODE_FIFO_RELAXED_KHR", VK_PRESENT_MODE_FIFO_RELAXED_KHR  }
    };
    
    if(presentModes.find(pmode) == presentModes.end() )
        throw std::runtime_error("config file: Contains bad presentMode '"+pmode+"'");
                       
    auto presentMode = presentModes[pmode];
        
    auto compiler = this->config.get("shadercompiler","glslangValidator");
    
    int clientWidth;
    int clientHeight;
    SDL_GetWindowSize(win,&clientWidth,&clientHeight);
    this->width=clientWidth;
    this->height=clientHeight;
    
    //create the instance
    
    //to enable debug printf, we must set this
    std::vector<const char*> layerEnables;
    if(withShaderPrintf){
        layerEnables.push_back("VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT");
    }
    if(withGPUValidation){
        layerEnables.push_back("VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT");
        layerEnables.push_back("VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT");
    }
    
    if(useValidation){
        layerEnables.push_back("VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT");
        layerEnables.push_back("VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT");
    }
    
    //FIXME: Verify that this works on Windows; otherwise, we need to add to pNext pointers
    //for pNext: See: https://www.lunarg.com/wp-content/uploads/2019/02/GPU-Assisted-Validation_v3_02_22_19.pdf
    
    putEnvironmentVariable("VK_LAYER_ENABLES", join(":",layerEnables));
    
    {
        auto tmp = _makeInstance(
            win,
            useDebugUtils,
            withShaderPrintf, 
            useValidation
        );
        this->instance = std::get<0>(tmp);
        this->haveDebugUtils = std::get<1>(tmp);
    }
    
    if(withDebugPrint and useDebugUtils){
        this->messenger = _setupDebugPrintCallback(this->instance);
        //~ this->debugFuncPointer = tmp[1]  //prevent garbage collection
    } else{
        this->messenger = nullptr;
    }
        
    if(!SDL_Vulkan_CreateSurface(win,this->instance,&(this->surface))){
        throw std::runtime_error("Cannot create SDL VK surface");
    }
     
     
    auto physdevInfo = _getPhysdev(
        this->surface,
        this->instance,
        discreteOK,
        integratedOK,
        cpuOK,
        forceGPU
    );
        
    this->physdev = std::get<0>(physdevInfo);
    this->physdevProperties = std::get<1>(physdevInfo);
    this->physdevFeatures = std::get<2>(physdevInfo);
    this->surfaceFormat = std::get<3>(physdevInfo);
    this->graphicsQueueIndex = std::get<4>(physdevInfo);
    this->presentQueueIndex = std::get<5>(physdevInfo);
    
    if( this->physdev == VK_NULL_HANDLE ){
        throw std::runtime_error("Could not get physical device");
    }

    //note: vkDestroyInstance is responsible for deleting physdev;
    //that function is called elsewhere
    
    std::uint32_t ecount;
    vkEnumerateDeviceExtensionProperties(this->physdev,nullptr,&(ecount),nullptr);
    std::vector<VkExtensionProperties> eprops(ecount);
    vkEnumerateDeviceExtensionProperties(this->physdev,nullptr,&(ecount),eprops.data());
    
    std::vector<const char*> extensionNames;
    extensionNames.push_back( VK_KHR_SWAPCHAIN_EXTENSION_NAME );
    
            
    //ref: https://stackoverflow.com/questions/68575596/using-debugprintfext-in-vulkan

    for(unsigned i=0;i<ecount;++i){
        if(eprops[i].extensionName == std::string(VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME)){
            extensionNames.push_back(VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME);
        }
    }
            
    std::vector<const char*> extensionNameArray(extensionNames.size());
    for(std::size_t i=0;i<extensionNames.size();++i){
        extensionNameArray[i] = extensionNames[i];
    }
    unsigned extensionCount = unsigned(extensionNames.size());
    
    float priorities[1] = {1.0};
    std::vector<VkDeviceQueueCreateInfo> pQueueCreateInfos{
        {
            .sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .queueFamilyIndex=this->graphicsQueueIndex,
            .queueCount = 1,
            .pQueuePriorities = priorities
        },
        {
            .sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .queueFamilyIndex=this->presentQueueIndex,
            .queueCount = 1,
            .pQueuePriorities = priorities
        }
    };
       
       
    VkDeviceCreateInfo dci = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueCreateInfoCount = (unsigned)( (this->graphicsQueueIndex == this->presentQueueIndex) ? 1 : 2 ),
        .pQueueCreateInfos = pQueueCreateInfos.data(),
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount=extensionCount,
        .ppEnabledExtensionNames=extensionNameArray.data(),
        .pEnabledFeatures=&featuresToEnable
    };

    check( vkCreateDevice(
        this->physdev,
        &dci,
        nullptr,
        &(this->dev)
    ));

    vkGetDeviceQueue( this->dev, this->graphicsQueueIndex, 0, &(this->graphicsQueue));
    
    this->presentQueue = VkQueue();
    vkGetDeviceQueue( this->dev, this->presentQueueIndex, 0, &(this->presentQueue));
    
    VkSurfaceCapabilitiesKHR surfCaps;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->physdev,
        this->surface,&(surfCaps));
    
    //the device wants us to create at least minImageCount images...
    auto imageCount = surfCaps.minImageCount;
    
    //...but if we create an extra buffer, we get better performance
    //We check to make sure the implementation would allow that.
    if(surfCaps.maxImageCount == 0 or surfCaps.maxImageCount > surfCaps.minImageCount){
        imageCount += 1;
    }
    
    VkSwapchainCreateInfoKHR swapchainCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext=nullptr,
        .flags=0,
        .surface = this->surface,
        .minImageCount = imageCount,
        .imageFormat = this->surfaceFormat.format,
        .imageColorSpace = this->surfaceFormat.colorSpace,
        .imageExtent = VkExtent2D{
            .width=unsigned(clientWidth),
            .height=unsigned(clientHeight)
        },
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT|VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
        .imageSharingMode=(
            (this->graphicsQueueIndex == this->presentQueueIndex) ? 
                VK_SHARING_MODE_EXCLUSIVE  :
                VK_SHARING_MODE_CONCURRENT
        ),
        .queueFamilyIndexCount=(
            (this->graphicsQueueIndex == this->presentQueueIndex) ?
                std::uint32_t(0) : std::uint32_t(2)
        ),
        .pQueueFamilyIndices=(
            (this->graphicsQueueIndex == this->presentQueueIndex) ?
            nullptr : &presentQueueIndex
        ),
        .preTransform = surfCaps.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE
    };
        
    check(vkCreateSwapchainKHR(this->dev, &swapchainCreateInfo, 
        nullptr, &this->swapchain)
    );
     
    
    //get number of images
    std::uint32_t swapchainImageCount;
    vkGetSwapchainImagesKHR(this->dev,this->swapchain,
        &(swapchainImageCount),nullptr);
    
    //and then allocate the images themselves
    this->swapchainImages.resize(swapchainImageCount);
    this->numSwapchainImages = int(this->swapchainImages.size());
    check(vkGetSwapchainImagesKHR(
        this->dev,
        this->swapchain,
        &(swapchainImageCount),
        this->swapchainImages.data()
    ));
    
    this->numSwapchainImages = swapchainImageCount;

    //vk spec says that implementation must support at least one of
    //VK_FORMAT_D24_UNORM_S8_UINT or VK_FORMAT_D32_SFLOAT_S8_UINT
    VkFormat possibleDepthFormats[2] = {
            VK_FORMAT_D24_UNORM_S8_UINT,
            VK_FORMAT_D32_SFLOAT_S8_UINT
    };
    const char* depthFormatNames[2] = {
        "VK_FORMAT_D24_UNORM_S8_UINT",
        "VK_FORMAT_D32_SFLOAT_S8_UINT"
    };
    
    bool depthok=false;
    for(int i=0;i<2;++i){
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(
            this->physdev, 
            possibleDepthFormats[i],
            &(props)
        );
        if(props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
        {
            this->depthFormat=possibleDepthFormats[i];
            depthok=true;
            verbose("Selected depth buffer format",depthFormatNames[i]);
            break;
        }
    }
    
    if(!depthok){
        throw std::runtime_error("Could not find compatible depth buffer");
    }
    
    for(auto& swimg : this->swapchainImages){
        this->swapchainImageViews.push_back( 
            _makeSwapchainImageView(
                this->dev,
                swimg,
                this->surfaceFormat.format
            )
        );
   
        auto tmp = _makeDepthbufferImage(
            this->dev,
            this->physdev,
            this->depthFormat,
            this->width,
            this->height
        );
        auto img = std::get<0>(tmp);
        auto mem = std::get<1>(tmp);
        auto view = std::get<2>(tmp);
            
        this->setObjectName(img,"DepthBufferImage");
        this->setObjectName(mem,"DepthBufferMem");
        this->setObjectName(view,"DepthBufferView");

        this->depthbufferImages.push_back(img);
        this->depthbufferMemories.push_back(mem);
        this->depthbufferViews.push_back(view);
    }

    check(vkCreateCommandPool(
        this->dev,
        VkCommandPoolCreateInfo{
            .sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .pNext = nullptr,
            .flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
            .queueFamilyIndex=this->graphicsQueueIndex
        },
        nullptr,
        &(this->commandPool)
    ));

    VkSemaphoreCreateInfo seminfo{
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = nullptr,
        .flags=0
    };
    check(vkCreateSemaphore(this->dev,&(seminfo),nullptr,&(this->imageAcquiredSemaphore)));
    check(vkCreateSemaphore(this->dev,&(seminfo),nullptr,&(this->renderCompleteSemaphore)));
    
    check(vkAllocateCommandBuffers(
        this->dev, 
        VkCommandBufferAllocateInfo{
            .sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .pNext = nullptr,
            .commandPool=this->commandPool,
            .level=VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandBufferCount=1
        },
        &(this->_privateCmdBuffer)
    ));
    
    this->setObjectName(this->_privateCmdBuffer,"privateCmdBuffer");

    //doing separately because we will replicate this for each subpass
    VkAttachmentReference colorAttachments {
        .attachment=0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };
    VkAttachmentReference depthStencilAttachment {
        .attachment=1,
        .layout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
    };
    VkSubpassDescription subpassDescription{
        .flags=0,
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .inputAttachmentCount=0,
        .pInputAttachments=nullptr,
        .colorAttachmentCount = 1,
        .pColorAttachments = &colorAttachments,
        .pResolveAttachments=nullptr,
        .pDepthStencilAttachment=&depthStencilAttachment,
        .preserveAttachmentCount=0,
        .pPreserveAttachments=nullptr
    };
    
    std::vector<VkSubpassDependency> subpassDependencies {      
        VkSubpassDependency{
            .srcSubpass = VK_SUBPASS_EXTERNAL,
            .dstSubpass=0,
            .srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, //VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, //VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
            .srcAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT, //0,
            .dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT,
            .dependencyFlags=0
        }
    };
    
    for(int i=1;i<numSubpasses;++i){
        subpassDependencies.push_back(
            VkSubpassDependency{
                .srcSubpass = unsigned(i-1),
                .dstSubpass=unsigned(i),
                .srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                .dstStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                .srcAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT, //0,
                .dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT,
                .dependencyFlags=0,
            }
        );
    }
    
    std::vector<VkAttachmentDescription> renderpassAttachments{
        {
            .flags=0,
            .format = this->surfaceFormat.format,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            .stencilLoadOp=VK_ATTACHMENT_LOAD_OP_LOAD,
            .stencilStoreOp=VK_ATTACHMENT_STORE_OP_STORE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        },
        {
            .flags=0,
            .format=this->depthFormat,
            .samples=VK_SAMPLE_COUNT_1_BIT,
            .loadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE, 
            .storeOp=VK_ATTACHMENT_STORE_OP_STORE,
            .stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp=VK_ATTACHMENT_STORE_OP_STORE,
            .initialLayout=VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
        }
    };
      
    std::vector<VkSubpassDescription> subpassDescriptions(
        numSubpasses, subpassDescription
    );
    
    check(vkCreateRenderPass(
        this->dev,
        VkRenderPassCreateInfo{
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            .pNext = nullptr,
            .flags=0,
            .attachmentCount=2,  
            .pAttachments = renderpassAttachments.data(),
            .subpassCount = unsigned(numSubpasses),
            .pSubpasses = subpassDescriptions.data(),
            .dependencyCount=unsigned(subpassDependencies.size()),
            .pDependencies = subpassDependencies.data()
        },
        nullptr,
        &(this->renderPass)
    ));
      
    this->setObjectName(this->renderPass,"Default renderPass");
    
    for(int i=0;i<(int)swapchainImageViews.size();++i){
        VkFramebuffer fb;
        std::vector<VkImageView> attachments{
            this->swapchainImageViews[i], 
            this->depthbufferViews[i] 
        };
        check(vkCreateFramebuffer( 
            this->dev, 
            VkFramebufferCreateInfo{
                .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                .pNext = nullptr,
                .flags=0,
                .renderPass = this->renderPass,
                .attachmentCount = 2,
                .pAttachments = attachments.data(),
                .width = unsigned(clientWidth),
                .height = unsigned(clientHeight),
                .layers = 1
            },
            nullptr, 
            &(fb) 
        ));
        this->setObjectName(fb,"Default Framebuffer for swapchainImageViews["+
            std::to_string(i)+"]");
        this->framebuffers.push_back(fb);
    }
}
    
std::tuple<int,int,std::string,std::vector<char> >  VulkanContext::screenshot(int imageIndex)
{
    auto simg = this->swapchainImages[imageIndex];
    return this->screenshot(simg);
}
    
std::tuple<int,int,std::string,std::vector<char> > VulkanContext::screenshot(VkImage simg)
{
    //technique from     
    //https://github.com/SaschaWillems/Vulkan/blob/master/examples/screenshot/screenshot.cpp
    
    //make a destination image
    VkImage dimg;
    check( vkCreateImage( 
        this->dev,
        VkImageCreateInfo{
            .sType=VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .pNext = nullptr,
            .flags=0,
            .imageType=VK_IMAGE_TYPE_2D,
            .format=VK_FORMAT_R8G8B8A8_UNORM,
            .extent = VkExtent3D{
                (unsigned)this->width, 
                (unsigned)this->height, 
                1
            },
            .mipLevels=1,
            .arrayLayers=1,
            .samples=VK_SAMPLE_COUNT_1_BIT,
            .tiling=VK_IMAGE_TILING_LINEAR,
            .usage=VK_IMAGE_USAGE_TRANSFER_DST_BIT,
            .sharingMode=VK_SHARING_MODE_EXCLUSIVE,
            .queueFamilyIndexCount=0,
            .pQueueFamilyIndices=nullptr,
            .initialLayout=VK_IMAGE_LAYOUT_UNDEFINED
        },
        nullptr,
        &(dimg)
    ));

    VkSubresourceLayout dlayout;
    vkGetImageSubresourceLayout( 
        this->dev, 
        dimg, 
        VkImageSubresource{
            .aspectMask=VK_IMAGE_ASPECT_COLOR_BIT,
            .mipLevel=0,
            .arrayLayer=0
        },
        &(dlayout)
    );
        
    VkMemoryRequirements memreqs;
    vkGetImageMemoryRequirements(
        this->dev, dimg, &(memreqs) 
    );
    
    auto typeindex = this->getMemoryByTypeAndProperties(
        memreqs.memoryTypeBits,
        (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT  | 
         VK_MEMORY_PROPERTY_HOST_COHERENT_BIT )
    );

    VkDeviceMemory memory;
    check(vkAllocateMemory(
        this->dev,
        VkMemoryAllocateInfo{
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .pNext = nullptr,
            .allocationSize = memreqs.size,
            .memoryTypeIndex = unsigned( typeindex )
        },
        nullptr,
        &memory
    ));
    check( vkBindImageMemory(this->dev,dimg,memory,0));

    //transition image layouts to the ones we want
    
    auto cmd = this->_privateCmdBuffer;
    vkResetCommandPool(this->dev, this->commandPool, 0);
    vkBeginCommandBuffer(
        cmd,
        VkCommandBufferBeginInfo{
            .sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .pNext = nullptr,
            .flags=VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
            .pInheritanceInfo=nullptr
        }
    );
        
    //layout transition for dest image
    VkImageMemoryBarrier membar{
        .sType=VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .pNext = nullptr,
        .srcAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT,
        .dstAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT ,
        .oldLayout=VK_IMAGE_LAYOUT_UNDEFINED,
        .newLayout=VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        .srcQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED,
        .image=dimg,
        .subresourceRange = VkImageSubresourceRange{
            .aspectMask=VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel=0,
            .levelCount=1,
            .baseArrayLayer=0,
            .layerCount=1
        },
    };
    vkCmdPipelineBarrier(
        cmd,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        0,    
        0, nullptr,    //memory barriers
        0, nullptr,    //buffer barriers
        1, 
        &membar
    );


    VkImageMemoryBarrier b1{
        .sType=VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .pNext = nullptr,
        .srcAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT,
        .dstAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT ,
        .oldLayout=VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        .newLayout=VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        .srcQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED,
        .image=simg,
        .subresourceRange = VkImageSubresourceRange{ 
            .aspectMask=VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel=0,
            .levelCount=1,
            .baseArrayLayer=0,
            .layerCount=1
        }
    };
        
    //layout transition for source image
    vkCmdPipelineBarrier(
        cmd,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        0,    
        0, nullptr,    //memory barriers
        0, nullptr,    //buffer barriers
        1, &b1
    );

    vkCmdCopyImage(
        cmd,
        simg, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        dimg, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1,
        VkImageCopy{
            .srcSubresource = VkImageSubresourceLayers{
                .aspectMask=VK_IMAGE_ASPECT_COLOR_BIT,
                .mipLevel=0,
                .baseArrayLayer=0,
                .layerCount=1
            },
            .srcOffset = VkOffset3D{ .x=0, .y=0, .z=0 },
            .dstSubresource = VkImageSubresourceLayers{
                .aspectMask=VK_IMAGE_ASPECT_COLOR_BIT,
                .mipLevel=0,
                .baseArrayLayer=0,
                .layerCount=1
            },
            .dstOffset = VkOffset3D{ .x=0, .y=0, .z=0},
            .extent = VkExtent3D{
                .width=unsigned(this->width), 
                .height=unsigned(this->height), 
                .depth=1
            }
        }
    );
    
    //undo transition for source image
    VkImageMemoryBarrier b2{
        .sType=VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .pNext = nullptr,
        .srcAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT,
        .dstAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT, 
        .oldLayout=VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        .newLayout=VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        .srcQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED,
        .image=simg,
        .subresourceRange = VkImageSubresourceRange{
            .aspectMask=VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel=0,
            .levelCount=1,
            .baseArrayLayer=0,
            .layerCount=1
        },
    };
    vkCmdPipelineBarrier(
        cmd,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        0,    
        0, nullptr,    //memory barriers
        0, nullptr,    //buffer barriers
        1, &b2
    );
            
    //transition dest image to optimal so we can map it
    VkImageMemoryBarrier b3{
        .sType=VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .pNext = nullptr,
        .srcAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT,
        .dstAccessMask=VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT, 
        .oldLayout=VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        .newLayout=VK_IMAGE_LAYOUT_GENERAL,
        .srcQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED,
        .image=dimg,
        .subresourceRange = VkImageSubresourceRange{
            .aspectMask=VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel=0,
            .levelCount=1,
            .baseArrayLayer=0,
            .layerCount=1
        },
    };
    vkCmdPipelineBarrier(
        cmd,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        0,    
        0, nullptr,    //memory barriers
        0, nullptr,    //buffer barriers
        1, &b3
        
    );

    vkEndCommandBuffer(cmd);
    
    check(vkQueueWaitIdle(this->graphicsQueue));

    check(vkQueueSubmit(
        this->graphicsQueue, 
        1, 
        VkSubmitInfo{
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .pNext=0,
            .waitSemaphoreCount=0,
            .pWaitSemaphores=nullptr,
            .pWaitDstStageMask = nullptr,
            .commandBufferCount=1,
            .pCommandBuffers = &cmd,
            .signalSemaphoreCount=0,
            .pSignalSemaphores=nullptr
        },
        VK_NULL_HANDLE
    ));
    
    check(vkQueueWaitIdle(this->graphicsQueue));
    
    
    
    std::vector<char> cpubuffer(dlayout.size);
    void* p;
    vkMapMemory(this->dev,memory,0,VK_WHOLE_SIZE,0,&(p));
    memmove( cpubuffer.data(), p, dlayout.size );
    vkUnmapMemory(this->dev,memory);
    vkDestroyImage(this->dev,dimg,nullptr);
    vkFreeMemory(this->dev,memory,nullptr);
    
    //Assuming it's bgra format...
    //swap to rgba
    for(int i=0;i<(int)cpubuffer.size();i+=4){
        std::swap(cpubuffer[i], cpubuffer[i+2] );
    }
    
    std::vector<char> pitched;
    for(std::size_t i=dlayout.offset;i<cpubuffer.size();i+=dlayout.rowPitch){
        pitched.insert(pitched.end(),
            cpubuffer.begin()+i,
            cpubuffer.begin()+i+this->width*4
        );
    }
      
    return std::tuple<int,int,std::string,std::vector<char> >{
        this->width, 
        this->height, 
        "RGBA8", 
        pitched
    };

    //FIXME: Look at swapchain color formats and swizzle
    //No need to swizzle if R8G8B8A8 format
    // VK_FORMAT_B8G8R8A8_SRGB, 
    // VK_FORMAT_B8G8R8A8_UNORM,
    // VK_FORMAT_B8G8R8A8_SNORM
    // others? 
    
}

     
void VulkanContext::setObjectName(void* obj, VkObjectType typ, const std::string& name){

    if(!this->haveDebugUtils){
        return;
    }
    VkDebugUtilsObjectNameInfoEXT info{
        .sType=VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
        .pNext = nullptr,
        .objectType=typ,
        .objectHandle=(std::uint64_t)obj,
        .pObjectName=name.c_str()
    };
    vkSetDebugUtilsObjectNameEXT(
        this->dev,
        &info
    );
}

void VulkanContext::setObjectName(VkInstance                obj, std::string name){this->setObjectName(obj,VK_OBJECT_TYPE_INSTANCE,name);}
void VulkanContext::setObjectName(VkPhysicalDevice          obj, std::string name){this->setObjectName(obj,VK_OBJECT_TYPE_PHYSICAL_DEVICE,name);}
void VulkanContext::setObjectName(VkDevice                  obj, std::string name){this->setObjectName(obj,VK_OBJECT_TYPE_DEVICE,name);}
void VulkanContext::setObjectName(VkQueue                   obj, std::string name){this->setObjectName(obj,VK_OBJECT_TYPE_QUEUE,name);}
void VulkanContext::setObjectName(VkSemaphore               obj, std::string name){this->setObjectName(obj,VK_OBJECT_TYPE_SEMAPHORE,name);}
void VulkanContext::setObjectName(VkCommandBuffer           obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_COMMAND_BUFFER  , name); }
void VulkanContext::setObjectName(VkFence                   obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_FENCE  , name); }
void VulkanContext::setObjectName(VkDeviceMemory            obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_DEVICE_MEMORY  , name); }
void VulkanContext::setObjectName(VkBuffer                  obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_BUFFER  , name); }
void VulkanContext::setObjectName(VkImage                   obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_IMAGE  , name); }
void VulkanContext::setObjectName(VkEvent                   obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_EVENT  , name); }
void VulkanContext::setObjectName(VkQueryPool               obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_QUERY_POOL  , name); }
void VulkanContext::setObjectName(VkBufferView              obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_BUFFER_VIEW  , name); }
void VulkanContext::setObjectName(VkImageView               obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_IMAGE_VIEW  , name); }
void VulkanContext::setObjectName(VkShaderModule            obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_SHADER_MODULE  , name); }
void VulkanContext::setObjectName(VkPipelineCache           obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_PIPELINE_CACHE  , name); }
void VulkanContext::setObjectName(VkPipelineLayout          obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_PIPELINE_LAYOUT  , name); }
void VulkanContext::setObjectName(VkRenderPass              obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_RENDER_PASS  , name); }
void VulkanContext::setObjectName(VkPipeline                obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_PIPELINE  , name); }
void VulkanContext::setObjectName(VkDescriptorSetLayout     obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT  , name); }
void VulkanContext::setObjectName(VkSampler                 obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_SAMPLER  , name); }
void VulkanContext::setObjectName(VkDescriptorPool          obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_DESCRIPTOR_POOL  , name); }
void VulkanContext::setObjectName(VkDescriptorSet           obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_DESCRIPTOR_SET  , name); }
void VulkanContext::setObjectName(VkFramebuffer             obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_FRAMEBUFFER  , name); }
void VulkanContext::setObjectName(VkCommandPool             obj, std::string name){this->setObjectName(obj, VK_OBJECT_TYPE_COMMAND_POOL  , name); } 
     
void VulkanContext::insertQueueLabel(std::string text)
{
    insertQueueLabel(text,this->graphicsQueue);
}
    
void VulkanContext::insertQueueLabel(std::string text, VkQueue queue)
{
    if(!this->haveDebugUtils ){
        return;
    }
    VkDebugUtilsLabelEXT lbl{
        .sType=VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
        .pNext = nullptr,
        .pLabelName=text.c_str(),
        .color={1,1,1,1}
    };
        
    vkQueueInsertDebugUtilsLabelEXT(
        queue, &lbl
    );
}

void VulkanContext::beginCmdRegion(VkCommandBuffer cmd, std::string text)
{
    if(! this->haveDebugUtils ){
        return;
    }
    VkDebugUtilsLabelEXT lbl{
        .sType=VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
        .pNext = nullptr,
        .pLabelName=text.c_str(),
        .color={1,1,1,1}
    };
    vkCmdBeginDebugUtilsLabelEXT(
        cmd, &lbl
    );
}

void VulkanContext::endCmdRegion(VkCommandBuffer cmd)
{
    if(!this->haveDebugUtils)
        return;
    vkCmdEndDebugUtilsLabelEXT(cmd);
}

void VulkanContext::insertCmdLabel(VkCommandBuffer cmd, std::string text)
{
    if(! this->haveDebugUtils ){
        return;
    }
    VkDebugUtilsLabelEXT lbl{
        .sType=VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
        .pNext = nullptr,
        .pLabelName=text.c_str(),
        .color={1,1,1,1}
    };
    vkCmdInsertDebugUtilsLabelEXT(
        cmd, &lbl
    );
    
}
      
      
static
std::array<int,2> getGraphicsAndPresentQueues(VkPhysicalDevice physdev, VkSurfaceKHR surf, 
        const std::vector<VkQueueFamilyProperties>& qfamilies,
        int& graphicsQueueIndex, int& presentQueueIndex)
{    
    graphicsQueueIndex=-1;
    presentQueueIndex=-1;
    for(unsigned i=0;i<(unsigned)qfamilies.size();++i){
        if(graphicsQueueIndex == -1 && qfamilies[i].queueCount != 0 && 0 != (VK_QUEUE_GRAPHICS_BIT & qfamilies[i].queueFlags) && 0 != (VK_QUEUE_COMPUTE_BIT & qfamilies[i].queueFlags)){
            graphicsQueueIndex = i;
        }
        if(presentQueueIndex == -1){
            VkBool32 presentIsSupported;
            check(vkGetPhysicalDeviceSurfaceSupportKHR(physdev,i,surf,&(presentIsSupported)));
            if(presentIsSupported){
                presentQueueIndex = i;
            } 
        }
        if( graphicsQueueIndex != -1 && presentQueueIndex != -1 )
            break;
    }
    return std::array<int,2>{graphicsQueueIndex, presentQueueIndex};
    
}


//internal function.
static std::tuple<       
    VkPhysicalDevice,
    VkPhysicalDeviceProperties,
    VkPhysicalDeviceFeatures,
    VkSurfaceFormatKHR,
    int,
    int
> _selectGPU(
        VkSurfaceKHR surf,
        std::vector<VkPhysicalDevice>& physdevs,
        std::string forceGPU,
        bool discreteOK,
        bool integratedOK,
        bool cpuOK)
{
    int numdevs = (int)physdevs.size();
    for(int i=0;i<numdevs;++i){
        auto physdev = physdevs[i];
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(physdev,&(props));

        std::string devname = props.deviceName;
        
        if(forceGPU != "" and devname != forceGPU){
            verbose("Skipping device",devname,"because it doesn\'t match the name",forceGPU);
            continue;
        }
        
        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceFeatures(physdev, &(features)) ;
        
        bool isDiscrete = (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU );
        bool isIntegrated = (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU );
        //bool isVirtual = (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU );
        bool isCPU = (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU);
        
        if(isDiscrete and not discreteOK){
            verbose("Skipping device",devname,"because it\'s a discrete GPU");
            continue;
        
        }
        if(isIntegrated and not integratedOK){
            verbose("Skipping device ",devname,"because it\'s an integrated GPU");
            continue;
        }
        if(isCPU and not cpuOK){
            verbose("Skipping device",devname,"because it\'s a CPU");
            continue;
        }
            
        std::uint32_t ecount;
        vkEnumerateDeviceExtensionProperties(physdev,nullptr,&(ecount),nullptr);
        std::vector<VkExtensionProperties> eprops(ecount);
        vkEnumerateDeviceExtensionProperties(physdev,nullptr,&(ecount),eprops.data());
        //print(ecount,"device extensions")
        bool hasSwapchain=false;

        std::string KSEN = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
        for(unsigned j=0;j<ecount;++j){
            //print("    ",eprops[i].extensionName)
            if(eprops[j].extensionName == KSEN ){
                hasSwapchain = true;
            }
        }

            
        if(!hasSwapchain){
            continue;
        }
         
        VkSurfaceCapabilitiesKHR surfCaps;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physdev,surf,&(surfCaps));
        
        std::uint32_t surffmtcount; 
        vkGetPhysicalDeviceSurfaceFormatsKHR(physdev,surf,&(surffmtcount),nullptr);

        if(surffmtcount == 0){
            continue;        //not suitable
        }
        std::vector<VkSurfaceFormatKHR> surffmts(surffmtcount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physdev,surf,&(surffmtcount),surffmts.data());


        //use first format; usually sufficient for our purposes
        auto surfFormat = surffmts[0];
       
        std::uint32_t surfpresentcount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physdev,surf,&(surfpresentcount),nullptr);


        if(surfpresentcount == 0){
            continue;        //not suitable
        }
        
        std::vector<VkPresentModeKHR> surfpresents(surfpresentcount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physdev,surf,
            &(surfpresentcount), surfpresents.data());
            
            
        //VK_PRESENT_MODE_FIFO_KHR is guaranteed to always be supported; syncs to vblank
        //use VK_PRESENT_MODE_MAILBOX_KHR to do triple buffering
        //or VK_PRESENT_MODE_IMMEDIATE_KHR to go as fast as possible
        if( std::find( surfpresents.begin(),surfpresents.end(), VK_PRESENT_MODE_FIFO_KHR) == surfpresents.end() ){
            throw std::runtime_error("This implementation doesn't support a required present mode");
        }

        std::uint32_t count;
        vkGetPhysicalDeviceQueueFamilyProperties(physdev,&(count),nullptr);
        std::vector<VkQueueFamilyProperties> qfamilies(count);
        vkGetPhysicalDeviceQueueFamilyProperties(physdev,&(count),qfamilies.data());
        
        //print("Physical device queue properties:")
        //~ for(int i=0;i<count;++i){
            //~ VkBool32 presentIsSupported;
            //~ check(vkGetPhysicalDeviceSurfaceSupportKHR(physdev,i,surf,&(presentIsSupported)));
            //print("Queue: graphics=",
                //VK_QUEUE_GRAPHICS_BIT & qfamilies[i].queueFlags,
                //"compute=",VK_QUEUE_GRAPHICS_BIT & qfamilies[i].queueFlags,
                //"present=",presentIsSupported)
        //~ }

        //section 5.1 of the standard:
        //If an implementation provides a graphics queue, it must provide
        //a queue family that does both graphics & compute.
        int presentQueueIndex=-1;
        int graphicsQueueIndex=-1;
        getGraphicsAndPresentQueues(physdev, surf, qfamilies, graphicsQueueIndex, presentQueueIndex);

        if( presentQueueIndex == -1 || graphicsQueueIndex == -1 ){
            continue;
        }
            
            
        std::string gpuType;
        if(isDiscrete){
            gpuType="discrete";
        } else if(isIntegrated){
            gpuType="integrated";
        } else if( isCPU){
            gpuType="emulated";
        } else{
            gpuType="unknown type of";
        }
        info("Selected",gpuType,"GPU",devname);
        
        return std::tuple<VkPhysicalDevice,
                         VkPhysicalDeviceProperties,
                         VkPhysicalDeviceFeatures,
                         VkSurfaceFormatKHR,
                         int,
                         int>(
             physdev, props, features, surfFormat, 
             graphicsQueueIndex,presentQueueIndex
        );
    }
    
    return std::tuple<VkPhysicalDevice,
                         VkPhysicalDeviceProperties,
                         VkPhysicalDeviceFeatures,
                         VkSurfaceFormatKHR,
                         int,
                         int>(
             VK_NULL_HANDLE, 
             VkPhysicalDeviceProperties(),
             VkPhysicalDeviceFeatures(),
             VkSurfaceFormatKHR(),
             -1,-1
    );
}
    
        
/**
    Return index of memory with the given types and properties.
    types -- This usually comes back from vkGetImageMemoryRequirements or vkGetBufferMemoryRequirements
    properties -- Memory properties. Ex: VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
*/
static unsigned _getMemoryByTypeAndProperties(VkPhysicalDevice physdev, std::uint32_t types, VkMemoryPropertyFlags properties);
unsigned VulkanContext::getMemoryByTypeAndProperties(std::uint32_t types, VkMemoryPropertyFlags properties){
    return _getMemoryByTypeAndProperties(
        this->physdev, 
        types, 
        properties
    );
}
       
static unsigned _getMemoryByTypeAndProperties(VkPhysicalDevice physdev, std::uint32_t types, VkMemoryPropertyFlags properties)
{
    //VK standard guarantees:
    //   If we are allocating a non-sparse buffer, it must be acceptable
    //       to allocate a HOST_VISIBLE | HOST_COHERENT memory chunk
      
    VkPhysicalDeviceMemoryProperties memprops;
    vkGetPhysicalDeviceMemoryProperties(physdev,&(memprops));
    auto numtypes = memprops.memoryTypeCount;
    for(int i=0;i<(int)numtypes;++i){
        if(0 == ( (1<<i) & types ))
            continue;        //not suitable: not of an allowable type
        if(properties != (properties & memprops.memoryTypes[i].propertyFlags))
            continue;        //not suitable: Missing some required properties
        return i;
    }
    throw std::runtime_error("No memory with desired type and properties");
}

void VulkanContext::cleanup(){
    //we also delete the instance variables to ensure
    //they cannot be accidentally re-used after the corresponding
    //vulkan object has been freed
    
    for(auto& fb : this->framebuffers){
        vkDestroyFramebuffer(this->dev,fb,nullptr);
    }
    vkDestroyRenderPass(this->dev,this->renderPass,nullptr);
    for(auto& img : this->depthbufferImages){
        vkDestroyImage(this->dev,img,nullptr);
    }
    vkFreeCommandBuffers(this->dev,this->commandPool,1,&(this->_privateCmdBuffer));
    
    for( auto& mem : this->depthbufferMemories){
        vkFreeMemory(this->dev,mem,nullptr);
    }
    for( auto&  view : this->depthbufferViews){
        vkDestroyImageView(this->dev,view,nullptr);
    }
    vkDestroySemaphore(this->dev,this->renderCompleteSemaphore,nullptr);
    vkDestroySemaphore(this->dev,this->imageAcquiredSemaphore,nullptr);
    vkDestroyCommandPool(this->dev,this->commandPool,nullptr);
    for( auto&  view : this->swapchainImageViews){
        vkDestroyImageView(this->dev,view,nullptr);
    }
    vkDestroySwapchainKHR(this->dev,this->swapchain,nullptr);
    vkDestroyDevice(this->dev,nullptr);
    vkDestroySurfaceKHR(this->instance,this->surface,nullptr);
    if(this->messenger != nullptr){
        vkDestroyDebugUtilsMessengerEXT(this->instance,this->messenger,nullptr);
    }
    vkDestroyInstance(this->instance,nullptr) ;   //also destroys physdev
}
     
/**
    Load and compile a shader. Returns the compiled bytecode.
        filename -- Filename of shader
        stage -- Identifies shader stage (string). One of: vert, tesc, tese, geom, frag, comp
*/
//~ std::vector<char> VulkanContext::loadShader(std::string filename, std::string stage)
//~ {
    //~ return loadShaderHelper(filename,true,stage);
//~ }

//~ std::vector<char> VulkanContext::loadShaderFromString(std::string data, std::string stage)
//~ {
    //~ return loadShaderHelper(data,false,stage);
//~ }

/*
std::vector<char> VulkanContext::loadShaderHelper(std::string s, bool fromFile, std::string stage)
{
    std::set<std::string> stages{ "vert","tesc","tese","geom","frag","comp"};
    if( stages.find(stage) == stages.end() )
        throw std::runtime_error("Shader stage is not valid");
        
    //~ std::ifstream in(filename,std::ios::binary);
    //~ if(!in.good()){
        //~ throw std::runtime_error("Cannot read file "+filename);
    //~ }
    //~ in.seekg(0,std::ios::end);
    //~ auto size = in.tellg();
    //~ in.seekg(0);
    //~ std::vector<std::uint8_t> indata(size);
    //~ in.read( (char*)indata.data(), size);
    //~ if(in.fail()){
        //~ throw std::runtime_error("Unable to read file "+filename);
    //~ }
    //~ in.close();
    
    std::string outfile = this->config.get("shaderoutput","out.spv");
    std::string compiler = this->config.get("shadercompiler","glslangValidator");
    std::string args = this->config.get("shadercompilerargs","-V -g -o out.spv");
    
    auto argv = shlex_split(args);
    std::vector<std::string> cmd;
    cmd.push_back(compiler);
    cmd.insert(cmd.end(), argv.begin(),argv.end());
    if( !fromFile )
        cmd.push_back("--stdin");
    cmd.push_back("-S");
    cmd.push_back(stage);
    
    std::tuple<bool,std::string> result;
    
    if( fromFile ){
        cmd.push_back(s);
        result = _spawn(cmd,"");
    } else {
        result = _spawn(cmd,s);
    }
    
    std::string output = std::get<1>(result);
    output = trim(output);
    bool suppressedOutput=false;
    if( output == "stdin" || output.find("\n") == std::string::npos){
        suppressedOutput=true;
    } else if(output.size()){
        if( !std::get<0>(result) ){
            error(output);
        } else {
            info(output);
        }
    }
    
    if( !std::get<0>(result) ){
        error("Problem when running",cmd);
        if(suppressedOutput){
            //if there was an error, ensure the output is printed 
            //no matter what
            error(output);
        }
        throw std::runtime_error("Shader compilation failed: "+output);
    }
    
    std::ifstream shdata(outfile,std::ios::binary);
    if(!shdata.good() ){
        throw std::runtime_error("Cannot open "+outfile);
    }
    shdata.seekg(0,std::ios::end);
    std::vector<char> shaderdata(shdata.tellg());
    shdata.seekg(0);
    shdata.read((char*)shaderdata.data(),shaderdata.size());
    if(shdata.fail()){
        throw std::runtime_error("Cannot read "+outfile);
    }
    return shaderdata;
}
*/

static std::tuple<VkInstance,bool>  _makeInstance(SDL_Window* win,
    bool useDebugUtils, bool withShaderPrintf, 
    bool useValidation)
{
    
    loadSpecialVulkanFunctions();
 
    std::uint32_t count;
    if( SDL_TRUE != SDL_Vulkan_GetInstanceExtensions(win,&(count),nullptr)){
        throw std::runtime_error("Cannot get Vulkan instance extensions");
    }
    auto requiredExtensionCount = count;
    std::vector<const char*> requiredExtensions(requiredExtensionCount);
    SDL_Vulkan_GetInstanceExtensions(win,&(count),requiredExtensions.data());

    std::vector<std::string> extensionNames;
    for(unsigned i=0;i<requiredExtensionCount;++i){
        extensionNames.push_back(requiredExtensions[i]);
    }

    
    VkApplicationInfo appInfo{
        .sType=VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext=nullptr,
        .pApplicationName="FOO",
        .applicationVersion=VK_MAKE_VERSION(1,0,0),
        .pEngineName="Nobody",
        .engineVersion=VK_MAKE_VERSION(1,0,0),
        .apiVersion=VK_API_VERSION_1_0
    };

    check(vkEnumerateInstanceLayerProperties( &(count), nullptr ) );
    auto numLayers = count;
    
    std::vector<VkLayerProperties> layerProperties(numLayers);
    check( vkEnumerateInstanceLayerProperties( &(count), layerProperties.data() ) );
    bool haveValidation=false;
    std::vector<std::string> layerNames;
    if(useValidation){
        std::string VKLV = "VK_LAYER_KHRONOS_validation";
        for(unsigned i=0;i<numLayers;++i){
            // ~ print("    Layer:",layerProperties[i].layerName)
            if(layerProperties[i].layerName == VKLV){
                layerNames.push_back( layerProperties[i].layerName );
                info("We have the validation layer. Good.");
                haveValidation=true;
                break;
            }
        }
        if(!haveValidation){
            warn("No validation layer available. Debugging will be more difficult.");
        }
    }
    
    check(vkEnumerateInstanceExtensionProperties(nullptr, &(count), nullptr));
    auto numExtensions = count;
    std::vector<VkExtensionProperties> extensionInfo(numExtensions);
    check(vkEnumerateInstanceExtensionProperties(nullptr, &(count), extensionInfo.data()));

    bool haveDebugUtils=false;
    if(useDebugUtils){
        std::string VEDU = "VK_EXT_debug_utils";
        for(unsigned i=0;i<numExtensions;++i){
            // ~ print("    Extension:",extensionInfo[i].extensionName)
            if(extensionInfo[i].extensionName == VEDU ){
                extensionNames.push_back(extensionInfo[i].extensionName);
                haveDebugUtils=true;
                info("We have the debug extension. Good.");
            }
        }
        if(!haveDebugUtils){
            warn("No debug extension. Debugging will require more effort.");
        }
    }
    
    std::vector<const char*> tmpe;
    for(auto& n : extensionNames ){
        tmpe.push_back(n.c_str());
    }
    
    std::vector<const char*> tmpl;
    for(auto& n : layerNames ){
        tmpl.push_back(n.c_str());
    }
    
    VkInstanceCreateInfo createinfo{
        .sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = nullptr,
        .flags=0,
        .pApplicationInfo=&appInfo,
        .enabledLayerCount=(unsigned)layerNames.size(),
        .ppEnabledLayerNames=(tmpl.size() ? tmpl.data() : nullptr),
        .enabledExtensionCount=(unsigned)extensionNames.size(),
        .ppEnabledExtensionNames=(tmpe.size() ? tmpe.data() : nullptr )
    };
    
    auto vfedpe = VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT;
    VkValidationFeaturesEXT feats{
        .sType=VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
        .pNext=nullptr,
        .enabledValidationFeatureCount=1,
        .pEnabledValidationFeatures=&vfedpe,
        .disabledValidationFeatureCount=0,
        .pDisabledValidationFeatures=nullptr
    };
    
    if(withShaderPrintf){
        //https://stackoverflow.com/questions/68575596/using-debugprintfext-in-vulkan
        createinfo.pNext = &feats;
    }
    
    VkInstance instance;
    check(vkCreateInstance(&(createinfo), nullptr, &instance));
    loadAllVulkanFunctions( instance );

    return std::tuple<VkInstance,bool>(instance,haveDebugUtils);
}

      

static VkDebugUtilsMessengerEXT _setupDebugPrintCallback(VkInstance instance)
{
    //debugFuncPointer = PFN_vkDebugUtilsMessengerCallbackEXT(_debugCallback)

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .pNext = nullptr,
        .flags=0,
        .messageSeverity = (
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT 
        ),
        .messageType = (
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT 
        ),
        .pfnUserCallback = _debugCallback,
        .pUserData=nullptr
    };
    VkDebugUtilsMessengerEXT    messenger;
    check(vkCreateDebugUtilsMessengerEXT(
        instance,
        &(debugCreateInfo),
        nullptr,
        &(messenger))
    );
    return messenger; //,debugFuncPointer
}

static std::tuple<       
    VkPhysicalDevice,
    VkPhysicalDeviceProperties,
    VkPhysicalDeviceFeatures,
    VkSurfaceFormatKHR,
    int,
    int
    >  _getPhysdev(VkSurfaceKHR surface,
        VkInstance instance, bool discreteOK, bool integratedOK,
        bool cpuOK, std::string forceGPU)
{
    
    uint32_t count;
    check(vkEnumeratePhysicalDevices(instance,&(count),nullptr));
    std::vector<VkPhysicalDevice> physdevs(count);
    check(vkEnumeratePhysicalDevices(instance,&(count),physdevs.data()));
      
    if(discreteOK){
        auto rv = _selectGPU(surface, physdevs,forceGPU,true,false,false);
        if( std::get<0>(rv) != VK_NULL_HANDLE )
            return rv;
    }
    
    if(integratedOK){
        auto rv = _selectGPU(surface, physdevs,forceGPU,false,true,false);
        if( std::get<0>(rv) != VK_NULL_HANDLE )
            return rv;
    }
    if(cpuOK){
        auto rv = _selectGPU(surface, physdevs,forceGPU,false,false,true);
        if( std::get<0>(rv) != VK_NULL_HANDLE )
            return rv;
    }
    
    throw std::runtime_error("No suitable GPU could be found.");
}

static VkImageView _makeSwapchainImageView(VkDevice dev, VkImage swapchainImage, VkFormat format)
{
    VkImageView view;
    check(vkCreateImageView(
        dev,
        VkImageViewCreateInfo{
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext = nullptr,
            .flags=0,
            .image = swapchainImage,
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = format,
            .components=VkComponentMapping{
                .r=VK_COMPONENT_SWIZZLE_IDENTITY,
                .g=VK_COMPONENT_SWIZZLE_IDENTITY,
                .b=VK_COMPONENT_SWIZZLE_IDENTITY,
                .a=VK_COMPONENT_SWIZZLE_IDENTITY
            },
            .subresourceRange = VkImageSubresourceRange{
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1
            }
        },
        nullptr,
        &(view)
    ));
    return view;
}

  
static std::tuple<VkImage, VkDeviceMemory, VkImageView> _makeDepthbufferImage(
        VkDevice dev, VkPhysicalDevice physdev,
        VkFormat format, int width, int height)
{
    VkImage depthbufferTexImage;
    
    check(vkCreateImage(
        dev,
        VkImageCreateInfo{
            .sType=VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .pNext = nullptr,
            .flags=0,
            .imageType=VK_IMAGE_TYPE_2D,
            .format=format,
            .extent = VkExtent3D{
                .width=(unsigned)width, 
                .height=(unsigned)height, 
                .depth=1 
            },
            .mipLevels=1,
            .arrayLayers=1,
            .samples=VK_SAMPLE_COUNT_1_BIT,
            .tiling=VK_IMAGE_TILING_OPTIMAL,
            .usage=VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
            .sharingMode=VK_SHARING_MODE_EXCLUSIVE,
            .queueFamilyIndexCount=0,
            .pQueueFamilyIndices=nullptr,
            .initialLayout=VK_IMAGE_LAYOUT_UNDEFINED
        }, 
        nullptr, 
        &(depthbufferTexImage) 
    ));
    
    
    VkMemoryRequirements memreq;
    vkGetImageMemoryRequirements(
        dev,
        depthbufferTexImage, 
        &(memreq)
    );
    
    VkDeviceMemory texMem;
    check( vkAllocateMemory(
        dev,
        VkMemoryAllocateInfo{
            .sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .pNext = nullptr,
            .allocationSize=memreq.size,
            .memoryTypeIndex = _getMemoryByTypeAndProperties(
                physdev,
                memreq.memoryTypeBits, 
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
            )
        },
        nullptr, 
        &(texMem)  
    ));
    
    vkBindImageMemory(dev,depthbufferTexImage,texMem,0 );
        
    VkImageView view;
    
    check(vkCreateImageView(
        dev,
        VkImageViewCreateInfo{
            .sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext = nullptr,
            .flags=0,
            .image=depthbufferTexImage,
            .viewType=VK_IMAGE_VIEW_TYPE_2D,
            .format=format,
            .components=VkComponentMapping{
                .r=VK_COMPONENT_SWIZZLE_IDENTITY,
                .g=VK_COMPONENT_SWIZZLE_IDENTITY,
                .b=VK_COMPONENT_SWIZZLE_IDENTITY,
                .a=VK_COMPONENT_SWIZZLE_IDENTITY
            },
            .subresourceRange= VkImageSubresourceRange{
                .aspectMask=VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT,
                .baseMipLevel=0,
                .levelCount=1,
                .baseArrayLayer=0,
                .layerCount=1
            },
        },
        nullptr,
        &(view)
    ));
    
    return std::tuple<VkImage, VkDeviceMemory, VkImageView>(
        depthbufferTexImage,texMem,view
    );
}

void VulkanContext::screenshot(int imageIndex,std::string filename)
{
    screenshot(this->swapchainImages[imageIndex], filename);
}

void VulkanContext::screenshot(VkImage img,std::string filename)
{
    auto tmp = this->screenshot(img);
    int w = std::get<0>(tmp);
    int h = std::get<1>(tmp);
    std::string fmt = std::get<2>(tmp);
    auto& pix = std::get<3>(tmp);
    auto data = imageencode::encodePNG(w,h,fmt,pix);
    std::ofstream out(filename,std::ios::binary);
    if(!out.good())
        throw std::runtime_error("Cannot open "+filename);
    out.write( data.data(), data.size() );
    out.close();
}

//~ void VulkanContext::forEachSwapchainImage( std::function<void(int)> callback)
//~ {
    //~ for(int i=0;i<this->numSwapchainImages;++i){
        //~ callback(i);
    //~ }
//~ }

//for debugging and troubleshooting
//FIXME: Implement this
//~ def printDeviceInfo(self,fp):
    
    //~ omit=set(["pipelineCacheUUID"])
    //~ def pp(obj,indent):
        //~ for q in sorted(obj._fields_):
            //~ name=q[0]
            //~ if name in omit:
                //~ continue
            //~ typ = q[1]
            //~ attr = obj.__getattribute__(q[0])
            //~ if isinstance(attr,ctypes.Structure):
                //~ print(f"{' '*indent}{name}:",file=fp)
                //~ pp(attr,indent+4)
            //~ elif isinstance(attr,bytes):
                //~ print(f"{' '*indent}{name}: {attr}",file=fp)
            //~ elif "__len__" in dir(attr):
                //~ tmp=[q for q in attr]
                //~ print(f"{' '*indent}{name}: {tmp}",file=fp)
            //~ else:
                //~ print(f"{' '*indent}{name}: {attr}",file=fp)
    
    //~ //gpu properties and limits
    //~ props = VkPhysicalDeviceProperties()
    //~ vkGetPhysicalDeviceProperties(this->physdev,&(props))
    
    //~ features = VkPhysicalDeviceFeatures()
    //~ vkGetPhysicalDeviceFeatures(this->physdev, &(features))
        
    //~ if props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
        //~ typ = "(discrete)"
    //~ if props.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
        //~ typ = "(integrated)"
    //~ if props.deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
        //~ typ="(virtual)"
    //~ if props.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU:
        //~ typ="(cpu)"
        
    //~ print("Device:",props.deviceName.decode(),typ,file=fp)
    //~ print("Properties:",file=fp)

    //~ pp(props,4)
    
    //~ print("Features:",file=fp)
    
    //~ pp(features,4)
    
    
    //~ ecount = ctypes.std::uint32_t32()
    //~ vkEnumerateDeviceExtensionProperties(this->physdev,nullptr,&(ecount),nullptr)
    //~ eprops = makeArray(VkExtensionProperties,ecount)
    //~ vkEnumerateDeviceExtensionProperties(this->physdev,nullptr,&(ecount),eprops)
    //~ ecount=ecount.value
    //~ print("Device extensions:",file=fp)
    //~ for i in range(ecount):
        //~ print("    "+eprops[i].extensionName.decode(),file=fp )
    
    
    //~ count = ctypes.std::uint32_t32()
    //~ check(vkEnumerateInstanceLayerProperties( &(count), nullptr ) )
    //~ numLayers = count.value
    
    //~ layerProperties = makeArray(VkLayerProperties , numLayers)
    //~ check( vkEnumerateInstanceLayerProperties( &(count), layerProperties ) )
    //~ print("Layers:",file=fp)
    //~ for i in range(numLayers):
        //~ print("    "+layerProperties[i].layerName.decode(),file=fp)


    // ~ print("Limits:",file=fp)
    // ~ print("    max 2D image size:",props.limits.maxImageDimension2D,file=fp)
    // ~ print("    max push constants:",props.limits.maxPushConstantsSize,file=fp)
    // ~ print("    max allocations:",props.limits.maxMemoryAllocationCount,file=fp)
    // ~ print("    max samplers:",props.limits.maxSamplerAllocationCount,file=fp)
    // ~ print("    max descriptor sets:",props.limits.maxBoundDescriptorSets,file=fp)
    // ~ print("    max color attachments:",props.limits.maxColorAttachments,file=fp)
    
    //memory properties
    //~ def yesno(x):
        //~ return "yes" if x else "no"
        
    //~ props = VkPhysicalDeviceMemoryProperties()
    //~ vkGetPhysicalDeviceMemoryProperties(this->physdev,&(props))
    
    //~ for hi in range(props.memoryHeapCount):
        //~ hinfo = props.memoryHeaps[hi]
        //~ print(f"Heap {hi}: Size: {hinfo.size>>20}MB Device local: {yesno(hinfo.flags&VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)}",file=fp)
        
        //~ for i in range(props.memoryTypeCount):
            //~ mtype = props.memoryTypes[i]
            //~ if mtype.heapIndex != hi:
                //~ continue
            //~ print(f"    Type {i}:",
                  //~ f"Local: {yesno(mtype.propertyFlags&VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)}",
                  //~ f"HostVisible: {yesno(mtype.propertyFlags&VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)}",
                  //~ f"HostCoherent: {yesno(mtype.propertyFlags&VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)}",
                  //~ f"HostCached: {yesno(mtype.propertyFlags&VK_MEMORY_PROPERTY_HOST_CACHED_BIT)}",
                  //~ f"LazyAlloc: {yesno(mtype.propertyFlags&VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)}",
                  //~ file=fp
            //~ )
