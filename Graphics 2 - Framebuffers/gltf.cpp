#include "gltf.h"
#include "math2801.h"
#include "consoleoutput.h"
#include <fstream>
#include "json.h"
#include <vector>
#include <cstdint>
#include <span>
#include <assert.h>
#include <cstring>
#include <cmath>
#include <array>

using json11::Json;
using math2801::vec2;
using math2801::vec3;
using math2801::vec4;
using math2801::mat4;

static const unsigned char white_png[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
  0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0x15, 0xc4, 0x89, 0x00, 0x00, 0x00,
  0x0b, 0x49, 0x44, 0x41, 0x54, 0x08, 0xd7, 0x63, 0xf8, 0x0f, 0x04, 0x00,
  0x09, 0xfb, 0x03, 0xfd, 0x63, 0x26, 0xc5, 0x8f, 0x00, 0x00, 0x00, 0x00,
  0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char black_png[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
  0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0x15, 0xc4, 0x89, 0x00, 0x00, 0x00,
  0x0d, 0x49, 0x44, 0x41, 0x54, 0x08, 0xd7, 0x63, 0x60, 0x60, 0x60, 0xf8,
  0x0f, 0x00, 0x01, 0x04, 0x01, 0x00, 0xa4, 0xe0, 0xac, 0x31, 0x00, 0x00,
  0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char periwinkle_png[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
  0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0x15, 0xc4, 0x89, 0x00, 0x00, 0x00,
  0x0d, 0x49, 0x44, 0x41, 0x54, 0x08, 0xd7, 0x63, 0xa8, 0xaf, 0xff, 0xff,
  0x1f, 0x00, 0x06, 0x7b, 0x02, 0xfd, 0xb2, 0x7c, 0x7e, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

void extractExtras(const Json& gltfNode, gltf::GLTFObject* obj)
{
    if (gltfNode.hasKey("extras")) {
        const Json& tmp = gltfNode["extras"];
        if (tmp.is_object()) {
            std::map<std::string, Json> M = tmp.object_items();
            for (auto it = M.begin(); it != M.end(); it++) {
                std::string key = it->first;
                const Json& value = it->second;
                if (value.is_number()) {
                    obj->extras[key] = (float)value.number_value();
                }
                else if (value.is_string()) {
                    obj->extras[key] = value.string_value();
                }
                else if (value.is_array()) {
                    std::vector<float> A;
                    const std::vector<Json>& JA = value.array_items();
                    for (unsigned i = 0; i < (unsigned)JA.size(); ++i) {
                        const Json& item = JA[i];
                        if (item.is_number()) {
                            A.push_back((float)item.number_value());
                        }
                        else {
                            warn("Ignoring non-float 'extra' value", key, "in list");
                            A.push_back(0.0f);
                        }
                    }
                    obj->extras[key] = A;
                }
                else if (value.is_object()) {
                    //silently ignore it
                }
                else {
                    warn("Ignoring 'extra' value", key, "of bad type");
                    obj->extras[key] = 0.0f;
                }
            }
        }
    }
}

template<typename T>
static void sizeCheck(unsigned expected) {
    if (sizeof(T) != expected)
        abort();
}
template<typename T>
static void loadAttribute(Json& J, int accessorIndex,
    gltf::GLTFBuffer& buffer,
    std::vector<T>& data)
{

    Json accessor = J["accessors"][accessorIndex];
    char typ;
    int expectedStride;
    if (accessor["type"] == "VEC4") {
        sizeCheck<T>(16);
        expectedStride = 16;
        typ = 'f';
    }
    else if (accessor["type"] == "VEC3") {
        sizeCheck<T>(12);
        expectedStride = 12;
        typ = 'f';
    }
    else if (accessor["type"] == "VEC2") {
        sizeCheck<T>(8);
        expectedStride = 8;
        typ = 'f';
    }
    else if (accessor["type"] == "SCALAR") {
        if (int(accessor["componentType"]) == 5123) {
            sizeCheck<T>(4);  //will convert to int later
            expectedStride = 2;
            typ = 'H';
        }
        else if (int(accessor["componentType"]) == 5125) {
            sizeCheck<T>(4);
            expectedStride = 4;
            typ = 'I';
        }
        else {
            throw std::runtime_error("Bad accessor component type: " + std::to_string(int(accessor["componentType"])));
        }
    }
    else {
        throw std::runtime_error("Bad accessor type: " + std::string(accessor["type"]));
    }

    int count = accessor["count"];
    int viewIndex = accessor["bufferView"];
    Json view = J["bufferViews"][viewIndex];
    assert(int(view["buffer"]) == 0);
    int byteStride = view.get("byteStride", expectedStride);
    assert(byteStride == expectedStride || byteStride == 0);
    int byteSize = view["byteLength"];
    int byteOffset = view.get("byteOffset", 0);
    int numElements = byteSize / expectedStride;

    assert(count == numElements);

    if (typ != 'H') {
        data.resize(numElements);
        char* dest = (char*)data.data();
        char* src = (char*)(buffer.bytes->data() + byteOffset);
        std::memcpy(dest, src, byteSize);
    }
    else {
        std::vector<std::uint16_t> sdata(numElements);
        std::memcpy(sdata.data(), buffer.bytes->data() + byteOffset, byteSize);
        data.clear();
        data.resize(numElements);
        std::uint32_t* dest = (std::uint32_t*)data.data();
        std::uint16_t* src = sdata.data();
        for (int i = 0; i < numElements; ++i)
            *dest++ = *src++;
    }
}

namespace gltf {

    GLTFMaterialTexture::GLTFMaterialTexture()
    {
        this->texCoord = 0;
        this->strength = 1.0f;  //occlusion map
        this->scale = 1.0f;     //normal map
    }

    GLTFSampler::GLTFSampler() {
        this->magFilter = gltf::LINEAR;
        this->minFilter = LINEAR_MIPMAP_LINEAR;
        this->wrapS = gltf::REPEAT;
        this->wrapT = gltf::REPEAT;
    }

    GLTFTextureTransform::GLTFTextureTransform()
    {
        this->offset = vec2(0, 0);
        this->rotation = 0.0f;
        this->scale = vec2(1.0f, 1.0f);
        this->texCoord = 0;
    }

    static GLTFMaterialTexture loadDefaultTexture(const char* defaultPng,
        unsigned defaultSize, const char* defaultName)
    {
        GLTFMaterialTexture mtex;
        mtex.texture.source.name = defaultName;
        mtex.texture.source.bytes = std::span<const char>{
                (const char*)defaultPng,defaultSize
        };
        return mtex;
    }

    static GLTFMaterialTexture loadTexture(Json& J, GLTFBuffer& buffer, const Json& Jspec)
    {
        int textureIndex = Jspec["index"];
        auto Jtex = J["textures"][textureIndex];
        int sourceIndex = Jtex["source"];
        Json image = J["images"][sourceIndex];
        std::string name = image["name"];
        int bufferViewIndex = image["bufferView"];
        Json bufferView = J["bufferViews"][bufferViewIndex];
        int start = bufferView["byteOffset"];
        int size = bufferView["byteLength"];
        int samplerIndex = Jtex["sampler"];

        GLTFMaterialTexture mtex;

        if (Jspec.hasKey("texCoord"))       mtex.texCoord = Jspec["texCoord"];
        if (Jspec.hasKey("strength"))       mtex.strength = Jspec["strength"];
        if (Jspec.hasKey("scale"))          mtex.scale = Jspec["scale"];

        mtex.texture.source.name = name;
        mtex.texture.source.bytes = std::span<char>(buffer.bytes->data() + start, size);

        Json Jsamp = J["samplers"][samplerIndex];
        if (Jsamp.hasKey("magFilter"))      mtex.texture.sampler.magFilter = Jsamp["magFilter"];
        if (Jsamp.hasKey("minFilter"))      mtex.texture.sampler.minFilter = Jsamp["minFilter"];
        if (Jsamp.hasKey("wrapS"))          mtex.texture.sampler.wrapS = Jsamp["wrapS"];
        if (Jsamp.hasKey("wrapT"))          mtex.texture.sampler.wrapT = Jsamp["wrapT"];

        //initialize it to match the default texcoord;
        //then parse the extension info if it exists
        mtex.transform.texCoord = mtex.texCoord;

        if (Jtex.hasKey("extensions")) {
            if (Jtex["extensions"].hasKey("KHR_texture_transform")) {
                const Json& tmp = Jtex["extensions"]["KHR_texture_transforms"];
                if (tmp.hasKey("offset")) {
                    mtex.transform.offset = vec2(
                        tmp["offset"][0].number_value(),
                        tmp["offset"][1].number_value()
                    );
                }
                if (tmp.hasKey("rotation"))
                    mtex.transform.rotation = (float)tmp["rotation"].number_value();

                if (tmp.hasKey("scale")) {
                    mtex.transform.scale = vec2(
                        tmp["scale"][0].number_value(),
                        tmp["scale"][1].number_value()
                    );
                }
                if (tmp.hasKey("texCoord"))
                    mtex.transform.texCoord = tmp["texCoord"].int_value();
            }
        }

        extractExtras(Jtex, &mtex);

        return mtex;
    }

    static
        GLTFMaterial getMaterialForPrimitive(Json& J, int materialIndex, GLTFBuffer& buffer)
    {
        GLTFMaterial mtl;
        Json jmaterial = J["materials"][materialIndex];
        mtl.name = jmaterial.get("name", "");

        Json jmetallicRoughness = jmaterial["pbrMetallicRoughness"];
        if (jmetallicRoughness.hasKey("baseColorFactor")) {
            Json tmp = jmetallicRoughness["baseColorFactor"];
            mtl.pbrMetallicRoughness.baseColorFactor = vec4((float)tmp[0], (float)tmp[1], (float)tmp[2], (float)tmp[3]);
        }
        else {
            mtl.pbrMetallicRoughness.baseColorFactor = vec4(1, 1, 1, 1);
        }

        if (jmetallicRoughness.hasKey("baseColorTexture")) {
            mtl.pbrMetallicRoughness.baseColorTexture = loadTexture(J, buffer,
                jmetallicRoughness["baseColorTexture"]
            );
        }
        else {
            mtl.pbrMetallicRoughness.baseColorTexture = loadDefaultTexture((const char*)white_png, sizeof(white_png), "white1x1");
        }

        if (jmaterial.hasKey("emissiveTexture")) {
            mtl.emissiveTexture = loadTexture(J, buffer,
                jmaterial["emissiveTexture"]
            );
        }
        else {
            mtl.emissiveTexture = loadDefaultTexture((const char*)white_png, sizeof(white_png), "white1x1");
        }

        Json tmp = jmaterial.get("emissiveFactor", Json());
        if (tmp.is_null())
            mtl.emissiveFactor = vec3(0, 0, 0);
        else
            mtl.emissiveFactor = vec3((float)tmp[0], (float)tmp[1], (float)tmp[2]);

        if (jmaterial.hasKey("normalTexture")) {
            mtl.normalTexture = loadTexture(J, buffer, jmaterial["normalTexture"]);
        }
        else {
            mtl.normalTexture = loadDefaultTexture((const char*)periwinkle_png, sizeof(periwinkle_png), "periwinkle1x1");
        }

        mtl.pbrMetallicRoughness.metallicFactor = jmetallicRoughness.get("metallicFactor", 1.0f);
        mtl.pbrMetallicRoughness.roughnessFactor = jmetallicRoughness.get("roughnessFactor", 1.0f);

        if (jmetallicRoughness.hasKey("metallicRoughnessTexture"))
            mtl.pbrMetallicRoughness.metallicRoughnessTexture = loadTexture(J, buffer, jmetallicRoughness["metallicRoughnessTexture"]);
        else
            mtl.pbrMetallicRoughness.metallicRoughnessTexture = loadDefaultTexture((const char*)white_png, sizeof(white_png), "white1x1");

        if (jmaterial.hasKey("occlusionTexture"))
            mtl.occlusionTexture = loadTexture(J, buffer, jmaterial["occlusionTexture"]);
        else
            mtl.occlusionTexture = loadDefaultTexture((const char*)white_png, sizeof(white_png), "white1x1");

        mtl.sheenColorFactor = vec3(0.0f, 0.0f, 0.0f);
        mtl.sheenRoughnessFactor = 1.0f;
        if (jmaterial.hasKey("extensions")) {
            auto ext = jmaterial["extensions"];
            if (ext.hasKey("KHR_materials_sheen")) {
                //FIXME: Support sheenColorTexture and sheenRoughnessTexture
                //Note: sheenRoughnessTexture uses *alpha* channel only!
                auto sheen = ext["KHR_materials_sheen"];
                mtl.sheenColorFactor.x = sheen["sheenColorFactor"][0];
                mtl.sheenColorFactor.y = sheen["sheenColorFactor"][1];
                mtl.sheenColorFactor.z = sheen["sheenColorFactor"][2];
                mtl.sheenRoughnessFactor = sheen["sheenRoughnessFactor"];
            }
        }

        extractExtras(jmaterial, &mtl);
        return mtl;
    }


    static GLTFMesh parseMesh(
        Json& J, int meshIndex,
        GLTFBuffer& buffer)
    {
        Json mesh = J["meshes"][meshIndex];
        std::string name = mesh["name"];
        auto primitives = mesh["primitives"];
        GLTFMesh gmesh;

        for (const Json& primitive : primitives.array_items()) {
            Json attributes = primitive["attributes"];
            GLTFPrimitive p;
            loadAttribute(J, attributes["POSITION"], buffer, p.positions);
            loadAttribute(J, attributes["TEXCOORD_0"], buffer, p.textureCoordinates);

            if (attributes.hasKey("TEXCOORD_1"))
                loadAttribute(J, attributes["TEXCOORD_1"], buffer, p.textureCoordinates2);
            else
                p.textureCoordinates2 = p.textureCoordinates;

            loadAttribute(J, attributes["NORMAL"], buffer, p.normals);
            if (attributes.hasKey("TANGENT"))
                loadAttribute(J, attributes["TANGENT"], buffer, p.tangents);
            else {
                p.tangents.resize(p.positions.size());
            }
            loadAttribute(J, primitive["indices"], buffer, p.indices);
            p.material = getMaterialForPrimitive(J, primitive["material"], buffer);
            gmesh.primitives.push_back(p);
        }

        extractExtras(mesh, &gmesh);
        return gmesh;
    }

    static GLTFLight parseLight(const Json& J, int lightIndex, mat4& M)
    {
        auto light = J["extensions"]["KHR_lights_punctual"]["lights"][lightIndex];
        GLTFLight glight;

        extractExtras(light, &glight);

        glight.name = light.get("name", "anonymous light");
        glight.color = vec3(1, 1, 1);
        if (light.hasKey("color")) {
            glight.color.x = light["color"][0];
            glight.color.y = light["color"][1];
            glight.color.z = light["color"][2];
        }
        glight.intensity = light.get("intensity", 1.0f);
        glight.position = (vec4(0, 0, 0, 1) * M);
        glight.direction = (vec4(0, 0, -1, 0) * M).xyz();

        std::string lightType = light["type"];
        if (lightType == "directional") {
            glight.position.x = -glight.direction.x;
            glight.position.y = -glight.direction.y;
            glight.position.z = -glight.direction.z;
            glight.position.w = 0.0f;
            glight.innerAngle = math2801::pi;
            glight.outerAngle = math2801::pi;
        }
        else if (lightType == "point") {
            glight.position.w = 1.0f;
            glight.innerAngle = math2801::pi;
            glight.outerAngle = math2801::pi;
        }
        else if (lightType == "spot") {
            glight.position.w = 1.0f;
            glight.innerAngle = (float)light["spot"].get("innerConeAngle", 0.0f);
            glight.outerAngle = (float)light["spot"].get("outerConeAngle", math2801::pi / 4.0f);
        }
        else {
            throw std::runtime_error("Bad light type: " + lightType);
        }
        glight.cosInnerAngle = std::cos(glight.innerAngle);
        glight.cosOuterAngle = std::cos(glight.outerAngle);
        return glight;
    }

    static mat4 getMatrixFromNode(Json& jnode)
    {
        if (jnode.hasKey("matrix")) {
            std::array<float, 16> f;
            for (int i = 0; i < 16; ++i) {
                f[i] = float(jnode["matrix"][i].number_value());
            }
            //GLTF defines matrix as transpose of what we use
            return mat4(f[0], f[4], f[8], f[12],
                f[1], f[5], f[9], f[13],
                f[2], f[6], f[10], f[14],
                f[3], f[7], f[11], f[15]
            );
        }
        else {
            float tx = 0, ty = 0, tz = 0;
            if (jnode.hasKey("translation")) {
                tx = float(jnode["translation"][0]);
                ty = float(jnode["translation"][1]);
                tz = float(jnode["translation"][2]);
            }
            mat4 T = math2801::translation(tx, ty, tz);
            float rx = 0, ry = 0, rz = 0, rw = 1;
            if (jnode.hasKey("rotation")) {
                rx = float(jnode["rotation"][0]);
                ry = float(jnode["rotation"][1]);
                rz = float(jnode["rotation"][2]);
                rw = float(jnode["rotation"][3]);
            }
            mat4 R = math2801::quaternionToMat4(vec4(rx, ry, rz, rw));
            float sx = 1, sy = 1, sz = 1;
            if (jnode.hasKey("scale")) {
                sx = float(jnode["scale"][0]);
                sy = float(jnode["scale"][1]);
                sz = float(jnode["scale"][2]);
            }
            mat4 S = math2801::scaling(sx, sy, sz);
            return S * R * T;
        }
    }

    static void readFile(std::ifstream& in, Json& J, std::vector<char>& buffer)
    {
        char magic[4];
        in.read(magic, 4);
        if (0 != memcmp(magic, "glTF", 4))
            throw std::runtime_error("Missing glTF magic");

        std::uint32_t version;
        in.read((char*)&version, 4);
        if (version != 2)
            throw std::runtime_error("GLTF version is not 2");

        in.seekg(4, std::ios::cur);  //skip file length field

        std::uint32_t jsonLength;
        in.read((char*)&jsonLength, 4);

        char jsonMagic[4];
        in.read(jsonMagic, 4);
        if (0 != memcmp(jsonMagic, "JSON", 4))
            throw std::runtime_error("Missing JSON magic");

        std::vector<char> jsonV(jsonLength);
        in.read(jsonV.data(), jsonLength);

        std::uint32_t binaryLength;
        in.read((char*)&binaryLength, 4);

        char binaryMagic[4];
        in.read(binaryMagic, 4);
        if (0 != memcmp(binaryMagic, "BIN", 4))
            throw std::runtime_error("Missing binary magic");

        buffer.resize(binaryLength);
        in.read(buffer.data(), binaryLength);

        std::string jsonData(jsonV.data(), jsonV.size());
        std::string err;
        J = Json::parse(jsonData, err);
        if (err.length()) {
            throw std::runtime_error(err);
        }
    }

    GLTFScene parse(std::string filename)
    {
        std::ifstream in(filename, std::ios::binary);
        if (!in.good())
            throw std::runtime_error("Cannot open " + filename);


        GLTFScene scene;
        scene.buffer.bytes = std::make_shared<std::vector<char>>();

        Json J;
        readFile(in, J, *(scene.buffer.bytes));

        Json Jscene = J["scenes"].array_items()[0];

        extractExtras(Jscene, &scene);

        for (auto& nodeIndex : Jscene["nodes"].array_items()) {

            auto jnode = J["nodes"][int(nodeIndex)];

            GLTFNode gnode;

            extractExtras(jnode, &gnode);

            gnode.name = jnode.get("name", "");
            gnode.matrix = getMatrixFromNode(jnode);

            if (jnode.hasKey("extensions")) {
                auto ext = jnode["extensions"];
                if (ext.hasKey("KHR_lights_punctual")) {
                    int lightIndex = ext["KHR_lights_punctual"]["light"];
                    GLTFLight light = parseLight(J, lightIndex, gnode.matrix);
                    //copy node extra attributes if needed...Blender
                    //seems to be exporting the data on the node, not the mesh
                    for (auto it : gnode.extras) {
                        if (!light.extras.contains(it.first))
                            light.extras[it.first] = it.second;
                    }
                    scene.lights.push_back(light);
                    gnode.light = light;
                }
            }
            if (jnode.hasKey("mesh")) {
                int meshIndex = jnode["mesh"];
                GLTFMesh mesh = parseMesh(J, meshIndex, scene.buffer);

                //copy node extra attributes if needed...Blender
                //seems to be exporting the data on the node, not the mesh
                for (auto it : gnode.extras) {
                    if (!mesh.extras.contains(it.first))
                        mesh.extras[it.first] = it.second;
                }

                mesh.matrix = gnode.matrix;
                mesh.name = gnode.name;
                scene.meshes.push_back(mesh);
                gnode.mesh = mesh;
            }

            scene.nodes.push_back(gnode);
        }

        return scene;
    }

};  //namespace