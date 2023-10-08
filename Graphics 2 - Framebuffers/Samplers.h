#include "vkhelpers.h"

namespace Samplers {

/// Initialize the subsystem.
/// @param ctx The context
void initialize(VulkanContext* ctx);

/// Return true if subsystem was initialized
/// @return True if initialized; false if not
bool initialized();

/// Sampler using nearest filtering + clamping
extern VkSampler nearestSampler         ;

/// Sampler using linear filtering + repeat
extern VkSampler linearSampler          ;

/// Sampler using linear filtering + mipmaps + repeat 
extern VkSampler mipSampler             ;

/// Sampler using linear filtering + mipmaps + claping 
extern VkSampler clampingMipSampler     ;

};
