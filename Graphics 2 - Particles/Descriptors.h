#pragma once
#include "vkhelpers.h"
#include <variant>

class DescriptorSetFactory;
class PipelineLayout;

/// Description for one descriptor set entry.
struct DescriptorSetEntry{
    VkDescriptorType type;          /// Resource type (ex: VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE).
    int slot;                       /// Slot in the descriptor set; must be nonnegative.
};


/// Describes the layout of a descriptor set.
class DescriptorSetLayout{
  public:
  
    /// Create the descriptor set
    /// @param ctx The associated context
    /// @param entries List of DescriptorSetEntry objects describing the contents of the descriptor set.
    DescriptorSetLayout(VulkanContext* ctx,
                    const std::vector< DescriptorSetEntry >& entries);
    
    /// The descriptor set layout itself
    VkDescriptorSetLayout layout;
    
    /// List of the types in the descriptor set. Organized
    /// by slot (so types[i] tells the type of item in slot i).
    /// Empty slots hold VK_DESCRIPTOR_TYPE_MAX_ENUM.
    std::vector< VkDescriptorType > types;
    
    /// Copy of the entries parameter passed to the constructor. Not
    /// organized by slot number (so entries[i].slot is not necessarily
    /// equal to i). See the types field.
    std::vector< DescriptorSetEntry > entries;

  private:
    DescriptorSetLayout(const DescriptorSetLayout&) = delete;
    void operator=(const DescriptorSetLayout& ) = delete;
    VulkanContext* ctx;
};
 
 
/// Wrapper for a Vulkan VkDescriptorSet object.
/// The constructor for this class is not public; use the DescriptorSetFactory
/// to manufacture DescriptorSet objects.
class DescriptorSet{
  public:
  
    /// Placeholder structure for an empty slot.
    struct Empty{};
    
    /// Set slot of the descriptor set to  the given item.
    /// @param slot Slot number; must be valid according to the DescriptorSetLayout
    /// @param item The item to store to that slot; must match type declared in DescriptorSetLayout
    void setSlot( int slot, VkImageView item );

    /// Set slot of the descriptor set to  the given item.
    /// @param slot Slot number; must be valid according to the DescriptorSetLayout
    /// @param item The item to store to that slot; must match type declared in DescriptorSetLayout
    void setSlot( int slot, VkSampler item );

    /// Set slot of the descriptor set to  the given item.
    /// @param slot Slot number; must be valid according to the DescriptorSetLayout
    /// @param item The item to store to that slot; must match type declared in DescriptorSetLayout
    void setSlot( int slot, VkBufferView item );

    /// Set slot of the descriptor set to  the given item.
    /// @param slot Slot number; must be valid according to the DescriptorSetLayout
    /// @param item The item to store to that slot; must match type declared in DescriptorSetLayout
    void setSlot( int slot, VkBuffer item );

    /// Bind this descriptor set to the graphics and compute pipelines.
    /// This makes any setSlot() operations visible to the GPU. It is 
    /// permissible to set a DescriptorSet's contents with setSlot,
    /// bind it, draw some geometry, then change the DescriptorSet contents with setSlot,
    /// bind it again, and draw additional geometry. Internally, the DescriptorSet
    /// manages one or more VkDescriptorSet handles and ensures that handles are not changed or
    /// re-used while they are part of an active command buffer.
    /// @param cmd The command buffer in which to record the bind operation.
    void bind(VkCommandBuffer cmd);
    
    /// Bind this descriptor set to one or more pipelines (graphics or compute).
    /// See documentation for bind(VkCommandBuffer).
    /// @param bindPoints The binding points: VK_PIPELINE_BIND_POINT_GRAPHICS and/or VK_PIPELINE_BIND_POINT_COMPUTE.
    void bind(VkCommandBuffer cmd, std::initializer_list<VkPipelineBindPoint> bindPoints);
    
    /// Name, for debugging purposes
    std::string name;
    
  private:
    typedef std::variant<Empty,VkImageView, VkSampler, VkBufferView, VkBuffer > Resource;

    DescriptorSet(const DescriptorSet&) = delete;
    void operator=(const DescriptorSet&) = delete;
    DescriptorSetLayout* descriptorSetLayout;
    DescriptorSetFactory* factory;
    PipelineLayout* pipelineLayout;
    int bindingPoint;
    VulkanContext* ctx;
    
    std::vector<Resource> currentResources;
    
    ///set(i,...) marks needsBind[i] as true.
    ///bind() marks all entries as false
    std::vector<bool> needsBind;
    
    ///descriptor sets that we previously made and that
    ///are now available for re-use
    std::vector<VkDescriptorSet> availableDescriptorSets;
    
    ///descriptor sets that are in-use for one or more frames that are
    ///being rendered. key=frame number, value=list of those descriptor sets
    std::map<unsigned, std::vector<VkDescriptorSet> > activeDescriptorSets;
    
    ///the descriptor set we're currently updating.
    ///it will be moved to activeDescriptorSets when we use() it
    VkDescriptorSet currentDescriptorSet = VK_NULL_HANDLE;
    
    void ensureCurrentIsValid();
    template<typename T>
    void setSlotDoIt(int slot, const T& item);

    ///private because we use the factory to make descriptor sets
    DescriptorSet(
        VulkanContext* ctx, 
        int bindingPoint,
        DescriptorSetLayout* descriptorSetLayout, 
        PipelineLayout* pipelineLayout,
        DescriptorSetFactory* factory,
        std::string name
    );
   
    friend class DescriptorSetFactory;
};
    
/// A DescriptorSetFactory is used to manufacture DescriptorSet objects.
class DescriptorSetFactory{
  public:
  
    ///Create a DescriptorSetFactory.
    /// @param ctx The associated context
    /// @param name For debugging
    /// @param bindingPoint Binding point (typically 0, 1, or 2) for generated DescriptorSet objects
    /// @param pipelineLayout The associated pipeline layout.
    DescriptorSetFactory(VulkanContext* ctx, 
        std::string name,
        int bindingPoint,
        PipelineLayout* pipelineLayout
    );
    
    /// Create a DescriptorSet.
    /// @return A newly created DescriptorSet.
    DescriptorSet* make();
    
    /// Clean up any allocated resources and DescriptorSet's.
    void cleanup();
    
  private:
  
    //binding point for the created Descriptors
    int bindingPoint;

    //used by DescriptorSet to actually allocate a set
    VkDescriptorSet allocate();
    
    std::string name;
    DescriptorSetLayout* layout;
    PipelineLayout* pipelineLayout;
    std::vector<DescriptorSet*> sets;
    std::vector<VkDescriptorPool> pools;
    int numLeft=0;
    VulkanContext* ctx;
    DescriptorSetFactory(const DescriptorSetFactory&) = delete;
    void operator=(const DescriptorSetFactory&) = delete;
    friend class DescriptorSet;
};
 
    
