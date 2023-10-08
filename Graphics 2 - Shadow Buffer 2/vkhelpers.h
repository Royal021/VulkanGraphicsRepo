#pragma once
#include "vk.h"
#include <string>
#include <vector>
#include <functional>
#include "ConfigParser.h"
#include "consoleoutput.h"

struct SDL_Window;

void check(int result);

class VulkanContext{
  public:
    VulkanContext(const VulkanContext&) = delete;
    void operator=(const VulkanContext&) = delete;

    ConfigParser                config;                     /// Configuration parser: for config.ini
    int                         width;                      /// Window width
    int                         height;                     /// Window height
    VkFormat                    depthFormat;                /// Format of depth buffer
    VkInstance                  instance;                   /// The Vulkan instance
    bool                        haveDebugUtils;             /// True if debug utils are available
    VkSurfaceKHR                surface;                    /// The window's surface
    VkPhysicalDevice            physdev ;                   /// The Vulkan physical device
    VkPhysicalDeviceProperties  physdevProperties ;         /// properties of physical device
    VkPhysicalDeviceFeatures    physdevFeatures ;           /// features of physical device
    VkSurfaceFormatKHR          surfaceFormat;              /// The format of the window surface
    VkQueue                     graphicsQueue;              /// The graphics queue
    VkQueue                     presentQueue;               /// The present queue
    std::uint32_t               graphicsQueueIndex;         /// Index of the graphics queue
    std::uint32_t               presentQueueIndex;          /// Index of the present queue
    VkDevice                    dev;                        /// The Vulkan logical device
    VkSwapchainKHR              swapchain;                  /// The swapchain
    std::vector<VkImage>        swapchainImages;            /// The swapchain's images
    int                         numSwapchainImages;         /// length of swapchainImages (convenience variable)
    std::vector<VkImageView>    swapchainImageViews;        /// The swapchain image views
    std::vector<VkImage>        depthbufferImages;          /// The depth buffers, one per swapchain image
    std::vector<VkDeviceMemory> depthbufferMemories;        /// Memory for depth buffer images
    std::vector<VkImageView>    depthbufferViews;           /// The depth buffers, one per swapchain image
    std::vector<VkFramebuffer>  framebuffers;               /// List of framebuffers, one per swapchain image
    VkCommandPool               commandPool;                /// A command pool suitable for creating one-time command buffers
    VkSemaphore                 imageAcquiredSemaphore;     /// Semaphore for signaling when the frame's image has been acquired
    VkSemaphore                 renderCompleteSemaphore;    /// Semaphore for signaling when the frame's image has been rendered
    VkRenderPass                renderPass;                 /// Generic renderpass
    VkDebugUtilsMessengerEXT    messenger;



    /// Constructor for the VulkanContext.
    /// @param win The SDL window for display
    /// @param featuresToEnable Optional features to enable
    /// @param numSubpasses The number of subpasses for rendering. Usually set to 1.
    VulkanContext(SDL_Window* win, VkPhysicalDeviceFeatures featuresToEnable,int numSubpasses);

    /// Generate a screenshot
    /// @param imageIndex The current swapchain image that is being displayed
    /// @return A tuple: width, height, format ("RGBA"), and the pixel data.
    std::tuple<int,int,std::string,std::vector<char> > screenshot(int imageIndex);

    /// Generate a snapshot of the given VkImage
    /// @param simg The source image
    /// @return A tuple: width, height, format ("RGBA"), and the pixel data.
    std::tuple<int,int,std::string,std::vector<char> > screenshot(VkImage simg);

    /// Generate a screenshot and save to a file.
    /// @param imageIndex The current swapchain image that is being displayed
    /// @param filename The output filename.
    void screenshot(int imageIndex, std::string filename);

    /// Generate a snapshot of an image and save to a file.
    /// @param img The image to save.
    /// @param filename The output filename.
    void screenshot(VkImage img, std::string filename);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// This is an internal function; you probably want to use one of the
    /// other setObjectName functions.
    /// @param obj The object to set
    /// @param type The type of object
    /// @param name The name to be associated with the object
    void setObjectName(void* obj, VkObjectType type, const std::string& name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkInstance               obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkPhysicalDevice         obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkDevice                 obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkQueue                  obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkSemaphore              obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkCommandBuffer          obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkFence                  obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkDeviceMemory           obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkBuffer                 obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkImage                  obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkEvent                  obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkQueryPool              obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkBufferView             obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkImageView              obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkShaderModule           obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkPipelineCache          obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkPipelineLayout         obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkRenderPass             obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkPipeline               obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkDescriptorSetLayout    obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkSampler                obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkDescriptorPool         obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkDescriptorSet          obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkFramebuffer            obj, std::string name);

    /// Set name of an arbitrary object (ex: for RenderDoc debugging).
    /// @param obj The object to set
    /// @param name The name to be associated with the object
    void setObjectName(VkCommandPool            obj, std::string name);

    /// Add a label to the graphics queue (ex: for RenderDoc debugging).
    /// @param text The label to insert
    void insertQueueLabel(std::string text);

    /// Add a label to a specific queue (ex: for RenderDoc debugging).
    /// @param text The label to insert
    /// @param queue The queue to use
    void insertQueueLabel(std::string text, VkQueue queue);

    /// Add a label to a command buffer (ex: for RenderDoc debugging).
    /// @param text The label to insert
    void insertCmdLabel(VkCommandBuffer cmd, std::string text);

    /// Add a label to a command buffer (ex: for RenderDoc debugging).
    /// @param data The label to insert
    //~ template<typename T>
    //~ void insertCmdLabel(VkCommandBuffer cmd, const T& data){
        //~ std::ostringstream oss;
        //~ oss << data;
        //~ this->insertCmdLabel(cmd,oss.str());
    //~ }

    /// Add a label to a command buffer (ex: for RenderDoc debugging).
    template<typename... A>
    void insertCmdLabel(VkCommandBuffer cmd, A... args){
        std::string s = printHelper(args...);
        this->insertCmdLabel(cmd,s);
    }


    /// Add a region (ex: for RenderDoc debugging) to the command buffer.
    /// You must call endCmdRegion to close the region.
    /// @param cmd The command queue
    /// @param text The label to insert
    void beginCmdRegion(VkCommandBuffer cmd, std::string text);

    /// Close a command region that was opened by beginCmdRegion.
    /// @param cmd The command queue
    void endCmdRegion(VkCommandBuffer cmd);

    /// Helper function for memory allocation: Returns the index
    /// given a bitflag of memory types and desired properties.
    unsigned getMemoryByTypeAndProperties(std::uint32_t types, VkMemoryPropertyFlags properties);

    /// Clean up the Vulkan context.
    void cleanup();

    //~ /// Helper function to load a shader.
    //~ /// @param filename The name of the GLSL source file
    //~ /// @param stage The shader stage. Must be one of vert, frag, tesc, tese, geom, comp.
    //~ /// @return The compiled SPIR-V bytecode.
    //~ std::vector<char> loadShader(std::string filename, std::string stage);

    /// Helper function to load a shader from a C++ string.
    /// @param data The GLSL source code.
    /// @param stage The shader stage. Must be one of vert, frag, tesc, tese, geom, comp.
    /// @return The compiled SPIR-V bytecode.
    std::vector<char> loadShaderFromString(std::string data, std::string stage);

  private:
    std::vector<char> loadShaderHelper(std::string filename, bool fromFile, std::string stage);
    VkCommandBuffer             _privateCmdBuffer;          //command buffer for private use
};

