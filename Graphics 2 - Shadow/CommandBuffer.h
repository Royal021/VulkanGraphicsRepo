#pragma once
#include "vkhelpers.h"

namespace CommandBuffer{
    
/// Initialize the subsystem.
/// @param ctx The context
void initialize(VulkanContext* ctx);

/// Return true if subsystem was initialized
/// @return True if initialized; false if not
bool initialized();


/// Allocate a command buffer.
/// @return The command buffer
VkCommandBuffer allocate();

/// Dispose of an existing command buffer.
/// @param cmd The command buffer to dispose of.
void dispose(VkCommandBuffer cmd);

/// Create a command buffer and prepare it to record commands.
/// This waits until the queue is idle, allocates a command buffer,
/// and begins recording into the buffer.
/// @return The command buffer.
VkCommandBuffer beginImmediateCommands();

/// Close a command buffer and submit it to the graphics queue. Then
/// wait until the queue is idle and dispose of the buffer.
/// @param cmd The command buffer.
void endImmediateCommands(VkCommandBuffer cmd);


};  //namespace

        
    
