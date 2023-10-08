#pragma once

#include "vkhelpers.h"
#include <string>

namespace ShaderManager{

/// Initialize the subsystem.
/// @param ctx The context
void initialize(VulkanContext* ctx);

/// Return true if subsystem was initialized
/// @return True if initialized; false if not
bool initialized();


/// Load a shader from a file.
/// @param filename Name of file containing the shader.
/// @return Shader information.
VkPipelineShaderStageCreateInfo load(std::string filename);


/// Load a shader from a file.
/// @param filename Name of file containing the shader.
/// @param type Type of the shader
/// @return Shader information.
VkPipelineShaderStageCreateInfo load(std::string filename, std::string type);

/// Load a shader from a string.
/// @param filename Name of file containing the shader.
/// @param type The type of shader (vert, frag, comp, tesc, tese, geom).
/// @return Shader information.
VkPipelineShaderStageCreateInfo loadFromString(std::string data, std::string type);

};
