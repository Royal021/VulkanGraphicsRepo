#pragma once
#include "vkhelpers.h"
#include "math2801.h"
#include <functional>
#include <array>

namespace parseMembers {

    /// Type of an item from a uniform or push constant specification file.
    enum class ItemType {
        UNDEFINED_TYPE,       ///< Unknown or undefined type
        INT_ITEM,             ///< int (signed integer)
        UINT_ITEM,            ///< uint (unsigned integer)
        FLOAT_ITEM,           ///< float
        IVEC2_ITEM,           ///< ivec2 (integer 2D vector)
        VEC2_ITEM,            ///< vec2 (float 2D vector)
        VEC3_ITEM,            ///< vec3 (float 3D vector)
        VEC4_ITEM,            ///< vec4 (float 4D vector)
        MAT4_ITEM,            ///< mat4 (float 4x4 matrix)
        VEC4ARRAY_ITEM,       ///< Array of vec4
        IVEC4ARRAY_ITEM,      ///< Array of ivec4 (signed integer 4D vector)
        UVEC4ARRAY_ITEM,      ///< Array of uvec4 (unsigned integer 4D vector)
        MAT4ARRAY_ITEM        ///< Array of mat4 (float 4x4 matrix)

    };

    /// A single item from a push constant or uniform file
    class Item {
    public:

        //Default constructor
        Item();

        /// Create an Item.
        /// @param name The variable's name
        /// @param offset Offset of item within the uniform buffer or
        ///         push constant buffer
        /// @param byteSize Size of the item in bytes
        /// @param arraySize Size of array, or -1 if this is not an array
        /// @param type The type of the item
        Item(std::string name, int offset, int byteSize, int arraySize, ItemType type);

        /// Variable's name
        std::string name;

        /// Variable's type as a string
        std::string typeAsString;

        /// Size of array as a string, or empty string if not an array
        std::string arraySizeAsString;

        /// Offset of data within buffer
        int offset;

        /// Size of item in bytes
        int byteSize;

        /// Number of elements in array, or -1 if not an array
        int arraySize;

        /// Type of item
        ItemType type;

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const float f);

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const std::int32_t f);

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const std::uint32_t f);

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const math2801::ivec2& f);

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const math2801::vec2& f);

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const math2801::vec3& f);

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const math2801::vec4& f);

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const math2801::mat4& f);

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const std::vector<math2801::vec4>& f);

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const std::vector<math2801::mat4>& f);


        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const std::vector<math2801::uvec4>& f);

        /// Obtain byte representation of data in
        /// the correct format for this item (depending on
        /// what the 'type' field specifies).
        /// @param f The data to convert. If this cannot be
        ///     converted to the Item's type, an exception is thrown.
        /// @return Vector with raw byte data suitable for copying
        ///     into a buffer.
        std::vector<char> convert(const std::vector<math2801::ivec4>& f);
    };

    /// Parse a uniform or push constant file and return information on the items found
    /// @param filename Name of file containing specification
    /// @return Tuple: Total bytes required, map of variables (with key=variable name
    ///     and value=Item describing that variable), map of #define constants
    ///     (with key=constant name and value=the value of that constant; non-integral
    ///     constants are ignored)
    std::tuple<int, std::map<std::string, Item>, std::map<std::string, int> >parse(std::string filename);

    /// Parse uniform or push constant data and return information on the items found
    /// @param data Specification of uniforms or push constants
    /// @return Tuple: Total bytes required, map of variables (with key=variable name
    ///     and value=Item describing that variable), map of #define constants
    ///     (with key=constant name and value=the value of that constant; non-integral
    ///     constants are ignored)
    std::tuple<int, std::map<std::string, Item>, std::map<std::string, int> >parseFromString(std::string data);

}; //namespace