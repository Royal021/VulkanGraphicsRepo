#pragma once
#include "vkhelpers.h"
#include "parseMembers.h"
#include "math2801.h"

//FIXME: Do uvec{2,3,4}  

/// Class to manage push constants
class PushConstants {
public:

    /// Push constant data. Key=name, value=information about it
    std::map<std::string, parseMembers::Item> items;

    /// Total size of all push constants
    int byteSize;

    /// Parse file and initialize items & byteSize.
    /// @param filename The file to parse
    PushConstants(std::string filename);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, std::int32_t value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, std::uint32_t value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, float value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, double value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, math2801::ivec2 value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, math2801::vec2 value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, math2801::vec3 value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, math2801::vec4 value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, math2801::mat4 value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, const std::vector<math2801::vec4>& value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, const std::vector<math2801::uvec4>& value);

    /// Set a push constant; if the name does not exist,
    /// an exception is raised.
    /// @param cmd The command buffer
    /// @param name Variable name
    /// @param value Value to set
    void set(VkCommandBuffer cmd, std::string name, const std::vector<math2801::ivec4>& value);
};