#pragma once
#include "math2801.h"
#include <memory>
#include <variant>
#include <vector>
#include <span>
#include <optional>
#include <map>

/// This file holds classes that represent raw GLTF data; for
/// a higher level interface, see the Mesh class.

namespace gltf {

    /// Texture sampling mode: Nearest, no mipmaps
    static const int NEAREST = 9728;

    /// Texture sampling mode: Linear, no mipmaps
    static const int LINEAR = 9729;

    /// Texture sampling mode: Linear + mipmaps
    static const int LINEAR_MIPMAP_LINEAR = 9987;

    /// Texture sampling mode: Clamp to edge (no repeat)
    static const int CLAMP_TO_EDGE = 33071;

    /// Texture sampling mode: Mirrored repeat
    static const int MIRRORED_REPEAT = 33648;

    /// Texture sampling mode: Ordinary repeat (tiled)
    static const int REPEAT = 10497;

    typedef std::variant<std::string, float, std::vector<float> > JSONType;
    typedef std::map<std::string, JSONType > ExtrasMap;

    /// Generic base class
    class GLTFObject {
    public:

        /// Holds extra data from GLTF file
        ExtrasMap extras;
    };

    ///A GLTF sampler object
    class GLTFSampler : public GLTFObject {
    public:

        ///Constructor
        GLTFSampler();

        /// Texture magnification: NEAREST or LINEAR
        int magFilter;

        /// Texture minification: NEAREST, LINEAR, or LINEAR_MIPMAP_LINEAR
        int minFilter;

        /// Horizontal (s or u axis) wrap mode: CLAMP_TO_EDGE, MIRRORED_REPEAT, or REPEAT
        int wrapS;

        /// Vertical (t or v axis) wrap mode: CLAMP_TO_EDGE, MIRRORED_REPEAT, or REPEAT
        int wrapT;
    };

    /// A GLTF buffer
    class GLTFBuffer : public GLTFObject {
    public:
        /// The data in the buffer
        std::shared_ptr<std::vector<char> > bytes;
    };

    /// A GLTF image
    class GLTFImage : public GLTFObject {
    public:
        /// name
        std::string name;

        /// Reference to range in a GLTFBuffer with image data
        std::span<const char> bytes;
    };

    /// Information about a texture
    class GLTFTexture : public GLTFObject {
    public:
        /// The texture itself
        GLTFImage source;

        /// The sampler that should be used
        GLTFSampler sampler;
    };


    /// Information about a light source
    class GLTFLight : public GLTFObject {
    public:

        /// name of the light
        std::string name;

        /// color of the light
        math2801::vec3 color;

        /// intensity of the light
        float intensity;

        /// position of the light; w=0 for directional (sun), 1 for positional
        math2801::vec4 position;

        /// spotlight direction
        math2801::vec3 direction;

        /// inner spotlight angle: Where light starts to fall-off
        float innerAngle;

        /// outer spotlight angle: Where light is zero
        float outerAngle;

        /// cosine of inner spotlight angle
        float cosInnerAngle;

        /// cosine of outer spotlight angle
        float cosOuterAngle;
    };


    /// Represents KHR_texture_transform extension data
    class GLTFTextureTransform {
    public:

        /// Constructor
        GLTFTextureTransform();

        /// offset of texture coordinate
        math2801::vec2 offset;

        /// Rotation (CCW around (0,0)
        float rotation;

        /// coordinate scale
        math2801::vec2 scale;

        /// If you support KHR_texture_transform, use
        /// this texture coordinate instead of the original texCoord
        int texCoord;

    };

    /// Texture for a material
    class GLTFMaterialTexture : public GLTFObject {
    public:

        /// Constructor: Initializes everything to default values
        GLTFMaterialTexture();

        /// index of texture coordinate: Usually 0; sometimes 1 (ex: normal maps)
        int texCoord;

        /// only used for occlusion maps
        float strength;

        /// only used for normal maps
        float scale;

        /// The texture itself
        GLTFTexture texture;

        // The KHR_texture_transform extension can
        // transform the original texture coordinates.
        GLTFTextureTransform transform;
    };

    /// PBR parameters
    class GLTFPBRMetallicRoughness : public GLTFObject {
    public:

        /// Texture that describes base object color
        GLTFMaterialTexture baseColorTexture;

        /// Factor to be multiplied by base color
        math2801::vec4 baseColorFactor;

        /// Texture that describes metallic (blue) and roughness (green) values.
        GLTFMaterialTexture metallicRoughnessTexture;

        /// Scale factor for metallicity
        float metallicFactor;

        /// Scale factor for roughness
        float roughnessFactor;
    };

    /// One GLTF material
    class GLTFMaterial : public GLTFObject {
    public:

        /// name
        std::string name;

        /// pbr parameters
        GLTFPBRMetallicRoughness pbrMetallicRoughness;

        /// bump map
        GLTFMaterialTexture normalTexture;

        /// occlusion map
        GLTFMaterialTexture occlusionTexture;

        /// emission map
        GLTFMaterialTexture emissiveTexture;

        /// scale factor for emission
        math2801::vec3 emissiveFactor;

        /// Sheen color. Default is (0,0,0)
        math2801::vec3 sheenColorFactor;

        /// Sheen roughness. Default is 0.
        float sheenRoughnessFactor;
    };

    /// A primitive is a collection of triangles with the same material
    class GLTFPrimitive : public GLTFObject {
    public:

        /// Triangle indices
        std::vector<std::uint32_t> indices;

        /// positions
        std::vector<math2801::vec3> positions;

        /// first  set of texture coordinates
        std::vector<math2801::vec2> textureCoordinates;

        /// normals
        std::vector<math2801::vec3> normals;

        /// tangents; w tells winding order
        std::vector<math2801::vec4> tangents;

        /// second set of texture coordinates
        std::vector<math2801::vec2> textureCoordinates2;

        /// material for the primitive
        GLTFMaterial material;
    };

    /// One mesh from a GLTF file
    class GLTFMesh : public GLTFObject {
    public:

        /// Name, for debugging
        std::string name;

        /// List of primitives in this mesh
        std::vector<GLTFPrimitive> primitives;

        /// Copy of owning node's matrix, for convenience.
        math2801::mat4 matrix;
    };


    /// One node from the GLTF scenegraph.
    class GLTFNode : public GLTFObject {
    public:

        /// for debugging
        std::string name;

        /// List of child nodes
        std::vector<GLTFNode> children;

        /// The transformation matrix. This does
        /// not incorporate any transformations from
        /// parent nodes.
        math2801::mat4 matrix;

        /// An optional mesh
        std::optional<GLTFMesh> mesh;

        /// An optional light
        std::optional<GLTFLight> light;
    };

    /// One scene from a GLTF file
    class GLTFScene : public GLTFObject {
    public:

        /// Buffer holding the binary data for the scene
        GLTFBuffer buffer;

        /// Root nodes
        std::vector<GLTFNode> nodes;

        /// All meshes in the scene, for convenience.
        std::vector<GLTFMesh> meshes;

        /// All lights in the scene, for convenience.
        std::vector<GLTFLight> lights;
    };

    /// Parse a GLTF file
    /// @param filename The file to parse.
    /// @return The first scene from the file.
    GLTFScene parse(std::string filename);

};  //namespace
