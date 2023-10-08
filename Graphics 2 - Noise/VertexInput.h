#pragma once

/// Structure identifying input for the VertexManager
struct VertexInput{
    /// Format of a vertex input
    VkFormat format;
    /// Rate at which to advance the input
    VkVertexInputRate rate;
};
