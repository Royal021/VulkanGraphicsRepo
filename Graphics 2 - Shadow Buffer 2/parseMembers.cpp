#include "parseMembers.h"
#include <fstream>
#include "mischelpers.h"
#include "consoleoutput.h"
#include <cstring>
#include <assert.h>
#include <array>

using namespace math2801;

template<typename T>
static void copy(std::vector<char>& v, const T& x)
{
    v.resize(sizeof(x));
    memcpy(v.data(), &x, sizeof(x));
}


static std::map<std::string, int> alignments{
    { "float" , 4},
    { "int" , 4},
    { "uint" , 4},
    { "vec2" , 8},
    { "ivec2" , 8},
    { "vec3" , 16},
    { "vec4" , 16},
    { "uvec4" , 16},
    { "ivec4" , 16},
    { "mat4" , 16}
};

static std::map<parseMembers::ItemType, std::string> typeNames{
    { parseMembers::ItemType::INT_ITEM              , "int"},
    { parseMembers::ItemType::UINT_ITEM             , "uint"},
    { parseMembers::ItemType::FLOAT_ITEM            , "float"},
    { parseMembers::ItemType::IVEC2_ITEM            , "ivec2"},
    { parseMembers::ItemType::VEC2_ITEM             , "vec2"},
    { parseMembers::ItemType::VEC3_ITEM             , "vec3"},
    { parseMembers::ItemType::VEC4_ITEM             , "vec4"},
    { parseMembers::ItemType::MAT4_ITEM             , "mat4"},
    { parseMembers::ItemType::VEC4ARRAY_ITEM        , "vec4 array"},
    { parseMembers::ItemType::UVEC4ARRAY_ITEM       , "uvec4 array"},
    { parseMembers::ItemType::IVEC4ARRAY_ITEM       , "ivec4 array"},
    { parseMembers::ItemType::MAT4ARRAY_ITEM        , "mat4 array"}
};


namespace parseMembers {

    using math2801::vec2;
    using math2801::vec3;
    using math2801::vec4;
    using math2801::mat4;
    using math2801::ivec2;


    Item::Item()
    {
        this->name = "";
        this->typeAsString = "";
        this->arraySizeAsString = "";
        this->offset = -1;
        this->byteSize = -1;
        this->arraySize = -1;
        this->type = ItemType::UNDEFINED_TYPE;
    }

    Item::Item(std::string name_, int offset_, int byteSize_, int arraySize_, ItemType type_)
    {
        this->name = name_;
        this->offset = offset_;
        this->byteSize = byteSize_;
        this->arraySize = arraySize_;
        this->type = type_;
    }

    std::vector<char> Item::convert(const float f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::INT_ITEM:
        {
            std::int32_t tmp = int(f);
            rv.resize(4);
            memcpy(rv.data(), &tmp, sizeof(tmp));
            break;
        }
        case ItemType::UINT_ITEM:
        {
            std::uint32_t tmp = unsigned(f);
            rv.resize(4);
            memcpy(rv.data(), &tmp, sizeof(tmp));
            break;
        }
        case ItemType::FLOAT_ITEM:
        {
            rv.resize(4);
            memcpy(rv.data(), &f, sizeof(f));
            break;
        }
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got float; expected " + typeNames[this->type]);
        }
        return rv;
    }

    std::vector<char> Item::convert(const int f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::INT_ITEM:
        {
            std::int32_t tmp = int(f);
            rv.resize(4);
            memcpy(rv.data(), &tmp, sizeof(tmp));
            break;
        }
        case ItemType::UINT_ITEM:
        {
            std::uint32_t tmp = unsigned(f);
            rv.resize(4);
            memcpy(rv.data(), &tmp, sizeof(tmp));
            break;
        }
        case ItemType::FLOAT_ITEM:
        {
            float tmp = float(f);
            rv.resize(4);
            memcpy(rv.data(), &tmp, sizeof(tmp));
            break;
        }
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got int; expected " + typeNames[this->type]);
        }
        return rv;
    }

    std::vector<char> Item::convert(const unsigned f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::INT_ITEM:
        {
            std::int32_t tmp = int(f);
            rv.resize(4);
            memcpy(rv.data(), &tmp, sizeof(tmp));
            break;
        }
        case ItemType::UINT_ITEM:
        {
            std::uint32_t tmp = unsigned(f);
            rv.resize(4);
            memcpy(rv.data(), &tmp, sizeof(tmp));
            break;
        }
        case ItemType::FLOAT_ITEM:
        {
            float tmp = float(f);
            rv.resize(4);
            memcpy(rv.data(), &tmp, sizeof(tmp));
            break;
        }
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got uint; expected " + typeNames[this->type]);
        }
        return rv;
    }

    std::vector<char> Item::convert(const vec2& f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::VEC2_ITEM:
            rv.resize(sizeof(f));
            memcpy(rv.data(), &f, sizeof(f));
            break;
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got vec2; expected " + typeNames[this->type]);
        }
        return rv;
    }


    std::vector<char> Item::convert(const ivec2& f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::IVEC2_ITEM:
            rv.resize(sizeof(f));
            memcpy(rv.data(), &f, sizeof(f));
            break;
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got ivec2; expected " + typeNames[this->type]);
        }
        return rv;
    }

    std::vector<char> Item::convert(const vec3& f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::VEC3_ITEM:
            rv.resize(sizeof(f));
            memcpy(rv.data(), &f, sizeof(f));
            break;
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got vec3; expected " + typeNames[this->type]);
        }
        return rv;
    }

    std::vector<char> Item::convert(const vec4& f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::VEC4_ITEM:
            rv.resize(sizeof(f));
            memcpy(rv.data(), &f, sizeof(f));
            break;
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got vec4; expected " + typeNames[this->type]);
        }
        return rv;
    }

    std::vector<char> Item::convert(const mat4& f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::MAT4_ITEM:
            rv.resize(sizeof(f));
            memcpy(rv.data(), &f, sizeof(f));
            break;
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got mat4; expected " + typeNames[this->type]);
        }
        return rv;
    }

    std::vector<char> Item::convert(const std::vector<vec4>& f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::VEC4ARRAY_ITEM:
            if ((int)f.size() != this->arraySize)
                throw std::runtime_error("Array size mismatch for " + this->name + ": Expected " +
                    std::to_string(this->arraySize) + " but got " + std::to_string(f.size()));
            rv.resize(f.size() * sizeof(f[0]));
            memcpy(rv.data(), f.data(), rv.size());
            break;
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got array of vec4; expected " + typeNames[this->type]);
        }
        return rv;
    }


    std::vector<char> Item::convert(const std::vector<mat4>& f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::MAT4ARRAY_ITEM:
            if ((int)f.size() != this->arraySize)
                throw std::runtime_error("Array size mismatch for " + this->name + ": Expected " +
                    std::to_string(this->arraySize) + " but got " + std::to_string(f.size()));
            rv.resize(f.size() * sizeof(f[0]));
            memcpy(rv.data(), f.data(), rv.size());
            break;
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got array of mat4; expected " + typeNames[this->type]);
        }
        return rv;
    }


    std::vector<char> Item::convert(const std::vector<uvec4>& f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::UVEC4ARRAY_ITEM:
            if ((int)f.size() != this->arraySize)
                throw std::runtime_error("Array size mismatch for " + this->name + ": Expected " +
                    std::to_string(this->arraySize) + " but got " + std::to_string(f.size()));
            rv.resize(f.size() * sizeof(f[0]));
            memcpy(rv.data(), f.data(), rv.size());
            break;
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got array of uvec4; expected " + typeNames[this->type]);
        }
        return rv;
    }



    std::vector<char> Item::convert(const std::vector<ivec4>& f) {
        std::vector<char> rv;
        switch (this->type) {
        case ItemType::IVEC4ARRAY_ITEM:
            if ((int)f.size() != this->arraySize)
                throw std::runtime_error("Array size mismatch for " + this->name + ": Expected " + std::to_string(this->arraySize) +
                    " but got " + std::to_string(f.size()));
            rv.resize(f.size() * sizeof(f[0]));
            memcpy(rv.data(), f.data(), rv.size());
            break;
        default:
            throw std::runtime_error("Bad type for " + this->name + ": Got array of ivec4; expected " + typeNames[this->type]);
        }
        return rv;
    }

    static
        std::tuple<int, std::map<std::string, Item>, std::map<std::string, int> >parseHelper(std::istream& in)
    {
        int totalBytes = 0;
        std::map<std::string, Item> items;
        std::map<std::string, int> defines;

        while (true) {
            std::string line;
            getline(in, line);
            if (in.fail())
                break;

            auto idx = line.find("//");
            if (idx != std::string::npos) {
                line = line.substr(0, idx);
            }

            line = trim(line);
            if (line.length() == 0)
                continue;

            if (line.starts_with("layout"))
                continue;

            if (line.starts_with("}"))
                continue;

            if (line.starts_with("#include"))
                continue;

            if (line.starts_with("#define")) {
                auto tmp = split(line);
                auto defname = tmp[1];
                auto defval = tmp[2];
                char* endp;
                int intval = (int)strtol(defval.c_str(), &endp, 0);
                if (*endp) {
                    //ignore this #define...
                    note("parseMembers is ignoring", line);
                }
                else {
                    defines[defname] = intval;
                }
                continue;
            }


            if (!line.ends_with(";"))
                throw std::runtime_error("Line does not end with semicolon: " + line);

            line = line.substr(0, line.length() - 1);
            line = trim(line);
            auto lst = split(line);
            assert(lst.size() == 2);
            auto type = lst[0];
            auto varname = lst[1];
            int arraysize;
            if (varname.find("[") != std::string::npos) {
                auto tmp = split(varname, '[');
                varname = tmp[0];
                auto arraysizeS = tmp[1];
                assert(arraysizeS.ends_with("]"));
                arraysizeS = arraysizeS.substr(0, arraysizeS.length() - 1);
                if (defines.contains(arraysizeS)) {
                    arraysize = defines[arraysizeS];
                }
                else {
                    char* endp;
                    arraysize = (int)strtol(arraysizeS.c_str(), &endp, 0);
                    if (*endp) {
                        throw std::runtime_error("Bad size for array: " + line);
                    }
                }
            }
            else {
                arraysize = -1;
            }

            if (!alignments.contains(type)) {
                throw std::runtime_error("Type " + type + " is not supported");
            }

            int a = alignments[type];

            if (totalBytes % a != 0) {
                int extra = totalBytes % a;
                int padding = a - extra;
                totalBytes += padding;
            }

            Item item;
            if (arraysize == -1) {
                if (type == "float")           item = Item(varname, totalBytes, 4, -1, ItemType::FLOAT_ITEM);
                else if (type == "int")        item = Item(varname, totalBytes, 4, -1, ItemType::INT_ITEM);
                else if (type == "uint")       item = Item(varname, totalBytes, 4, -1, ItemType::UINT_ITEM);
                else if (type == "vec2")       item = Item(varname, totalBytes, 8, -1, ItemType::VEC2_ITEM);
                else if (type == "ivec2")      item = Item(varname, totalBytes, 8, -1, ItemType::IVEC2_ITEM);
                else if (type == "vec3")       item = Item(varname, totalBytes, 12, -1, ItemType::VEC3_ITEM);
                else if (type == "vec4")       item = Item(varname, totalBytes, 16, -1, ItemType::VEC4_ITEM);
                else if (type == "mat4")       item = Item(varname, totalBytes, 64, -1, ItemType::MAT4_ITEM);
                else throw new std::runtime_error("Bad type:" + line);
                item.arraySizeAsString = "";
            }
            else {
                if (type == "vec4")
                    item = Item(varname, totalBytes, arraysize * 16, arraysize, ItemType::VEC4ARRAY_ITEM);
                else if (type == "uvec4")
                    item = Item(varname, totalBytes, arraysize * 16, arraysize, ItemType::UVEC4ARRAY_ITEM);
                else if (type == "ivec4")
                    item = Item(varname, totalBytes, arraysize * 16, arraysize, ItemType::IVEC4ARRAY_ITEM);
                else if (type == "mat4")
                    item = Item(varname, totalBytes, arraysize * 64, arraysize, ItemType::MAT4ARRAY_ITEM);
                else
                    throw std::runtime_error("Arrays must be mat4, vec4, ivec4, or uvec4 (for variable " + varname + ")");
                item.arraySizeAsString = "[" + std::to_string(arraysize) + "]";
            }

            item.typeAsString = type;

            items[varname] = item;
            totalBytes += item.byteSize;
        }

        return std::tuple<int, std::map<std::string, Item>, std::map<std::string, int> >(totalBytes, items, defines);
    }

    std::tuple<int, std::map<std::string, Item>, std::map<std::string, int> >parse(std::string filename)
    {
        std::ifstream in(filename);
        if (!in.good())
            throw std::runtime_error("Could not open " + filename);
        return parseHelper(in);
    }

    std::tuple<int, std::map<std::string, Item>, std::map<std::string, int> >parseFromString(std::string data)
    {
        std::istringstream in(data);
        return parseHelper(in);
    }

}; //namespace
