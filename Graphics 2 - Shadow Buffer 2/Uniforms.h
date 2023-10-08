#pragma once

#include "vkhelpers.h"
#include <set>
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include "math2801.h"
#include "parseMembers.h"
#include <array>

//FIXME: Do uvec{2,3,4} and array of ivec4/uvec4

class DeviceLocalBuffer;
class DescriptorSet;

/// Class to manage collection of uniforms
class Uniforms {
public:

    /// Create uniform manager
    /// @param ctx Associated context
    /// @param uniformFilename Name of the file that holds the uniforms
    Uniforms(VulkanContext* ctx, std::string uniformFilename);

    /// Create uniform manager
    /// @param ctx Associated context
    /// @param uniformData String that holds the uniform specification
    /// @return a Uniforms object
    static Uniforms* createFromData(VulkanContext* ctx, const std::string& uniformData);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, std::int32_t value);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, std::uint32_t value);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, float value);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, double value);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, math2801::ivec2 value);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, math2801::vec2 value);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, math2801::vec3 value);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, math2801::vec4 value);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, math2801::mat4 value);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, const std::vector<math2801::vec4>& value);

    /// Set uniform value; if the name does not specify a valid
    /// uniform or the value is not the correct type,
    /// an exception is thrown.
    /// @param name The uniform name
    /// @param value The value to set
    void set(const std::string& name, const std::vector<math2801::mat4>& value);


    /// Update the uniform data visible to the the GPU. This may not be called
    /// within a renderpass. It may be called several times for
    /// a single frame as long as no renderpass is active.
    /// If this function is not called, any changes to the uniforms
    /// will not be visible to the GPU.
    /// @param cmd The command buffer
    /// @param descriptorSet The descriptor set to use
    /// @param slot The slot number in the descriptor set
    void update(VkCommandBuffer cmd, DescriptorSet* descriptorSet, int slot);

    /// Get the value of the symbol #define'd in the uniform specification.
    /// If the symbol does not exist, an exception is thrown.
    /// Only integer values are permitted.
    /// @param name The name of the symbol.
    /// @return The value of the symbol.
    int getDefine(const std::string& name);

    /// Return true if a symbol with the given name was
    /// #define'd in the uniform file.
    /// @param name The symbol name.
    /// @return True if the symbol exists; false if not.
    bool hasDefine(const std::string& name);

private:

    std::map<std::string, int> defines;
    bool updating = false;
    std::vector<char> shadowBuffer;
    std::map<std::string, parseMembers::Item> items;

    //keeps track of uniforms that haven't been set yet
    std::set<std::string> uninitialized;

    //size of all uniforms
    VkDeviceSize byteSize;

    std::vector<DeviceLocalBuffer*> availableBuffers;

    //frame identifier & active buffers
    std::map<unsigned, std::vector<DeviceLocalBuffer*> > activeBuffers;

    DeviceLocalBuffer* currentBuffer = nullptr;

    //memories. We allocate several buffers from each memory
    std::vector<VkDeviceMemory> memories;
    std::uint32_t memoryTypeBits;
    void ensureCurrentIsValid();

    void init(VulkanContext* ctx,
        std::tuple<int, std::map<std::string, parseMembers::Item>, std::map<std::string, int> > info,
        std::string inputFile);

    Uniforms();

    VulkanContext* ctx;
    Uniforms(const Uniforms&) = delete;
    void operator=(const Uniforms&) = delete;
};