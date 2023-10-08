#include "vkhelpers.h"
#include "ShaderManager.h"
#include "CleanupManager.h"
#include "consoleoutput.h"
#include "utils.h"
#include "mischelpers.h"
#include <stdexcept>
#include <vector>
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include <iostream>
#include <map>
#include <stdexcept>
#include <fstream>
#include <filesystem>

// ref: https://vulkan.lunarg.com/doc/sdk/1.3.236.0/windows/spirv_toolchain.html
// ref: https://github.com/KhronosGroup/glslang/blob/master/StandAlone/StandAlone.cpp
// ref: https://github.com/KhronosGroup/glslang/blob/master/StandAlone/ResourceLimits.cpp

static VulkanContext* ctx;
static std::vector<VkPipelineShaderStageCreateInfo> _shaders;
static std::list<std::vector<unsigned> > codes;




static std::map<std::string,EShLanguage> typeMap = {
    {"vert", EShLangVertex},
    {"frag", EShLangFragment},
    {"tesc", EShLangTessControl},
    {"tese", EShLangTessEvaluation},
    {"geom", EShLangGeometry},
    {"comp", EShLangCompute}
};
static std::map<std::string, VkShaderStageFlagBits> stages = {
    { "vert", VK_SHADER_STAGE_VERTEX_BIT },
    { "frag", VK_SHADER_STAGE_FRAGMENT_BIT },
    { "tesc", VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT },
    { "tese", VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT },
    { "geom", VK_SHADER_STAGE_GEOMETRY_BIT },
    { "comp", VK_SHADER_STAGE_COMPUTE_BIT }
};

static VkPipelineShaderStageCreateInfo makeModule(std::vector<unsigned>& code,
            const std::string type)
{
    if(!ctx)
        throw std::runtime_error("ShaderManager::initialize() has not been called yet");

    codes.push_back(code);

    VkShaderModule module;
    check(vkCreateShaderModule(
        ctx->dev,
        VkShaderModuleCreateInfo{
            .sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .pNext=nullptr,
            .flags=0,
            .codeSize = (unsigned)code.size()*4,
            .pCode = (std::uint32_t*)codes.back().data()
        },
        nullptr,
        &(module)
    ));

    assert(stages.contains(type));

    VkPipelineShaderStageCreateInfo info{
        .sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .pNext=nullptr,
        .flags=0,
        .stage=stages[type],
        .module=module,
        .pName="main",
        .pSpecializationInfo=nullptr
    };

    _shaders.push_back(info);

    return info;
}

//some limits are from the defaults at
//https://github.com/KhronosGroup/glslang/blob/master/StandAlone/ResourceLimits.cpp
const static TBuiltInResource builtins{
    .maxLights = 32,
    .maxClipPlanes = 6,
    .maxTextureUnits = 32,
    .maxTextureCoords = 32,
    .maxVertexAttribs = 64,
    .maxVertexUniformComponents = 4096,
    .maxVaryingFloats = 64,
    .maxVertexTextureImageUnits = 32,
    .maxCombinedTextureImageUnits = 80,
    .maxTextureImageUnits = 32,
    .maxFragmentUniformComponents = 4096,
    .maxDrawBuffers = 32,
    .maxVertexUniformVectors = 128,
    .maxVaryingVectors = 8,
    .maxFragmentUniformVectors = 16,
    .maxVertexOutputVectors = 16,
    .maxFragmentInputVectors = 15,
    .minProgramTexelOffset = -8,
    .maxProgramTexelOffset = 7,
    .maxClipDistances = 8,
    .maxComputeWorkGroupCountX = 65535,
    .maxComputeWorkGroupCountY = 65535,
    .maxComputeWorkGroupCountZ = 65535,
    .maxComputeWorkGroupSizeX = 1024,
    .maxComputeWorkGroupSizeY = 1024,
    .maxComputeWorkGroupSizeZ = 64,
    .maxComputeUniformComponents = 1024,
    .maxComputeTextureImageUnits = 16,
    .maxComputeImageUniforms = 8,
    .maxComputeAtomicCounters = 8,
    .maxComputeAtomicCounterBuffers = 1,
    .maxVaryingComponents = 60,
    .maxVertexOutputComponents = 64,
    .maxGeometryInputComponents = 64,
    .maxGeometryOutputComponents = 128,
    .maxFragmentInputComponents = 128,
    .maxImageUnits = 8,
    .maxCombinedImageUnitsAndFragmentOutputs = 8,
    .maxCombinedShaderOutputResources = 8,
    .maxImageSamples = 0,
    .maxVertexImageUniforms = 0,
    .maxTessControlImageUniforms = 0,
    .maxTessEvaluationImageUniforms = 0,
    .maxGeometryImageUniforms = 0,
    .maxFragmentImageUniforms = 8,
    .maxCombinedImageUniforms = 8,
    .maxGeometryTextureImageUnits = 16,
    .maxGeometryOutputVertices = 256,
    .maxGeometryTotalOutputComponents = 1024,
    .maxGeometryUniformComponents = 64,
    .maxGeometryVaryingComponents = 64,
    .maxTessControlInputComponents = 128,
    .maxTessControlOutputComponents = 128,
    .maxTessControlTextureImageUnits = 16,
    .maxTessControlUniformComponents = 1024,
    .maxTessControlTotalOutputComponents = 4096,
    .maxTessEvaluationInputComponents = 128,
    .maxTessEvaluationOutputComponents = 128,
    .maxTessEvaluationTextureImageUnits = 16,
    .maxTessEvaluationUniformComponents = 1024,
    .maxTessPatchComponents = 120,
    .maxPatchVertices = 32,
    .maxTessGenLevel = 64,
    .maxViewports = 16,
    .maxVertexAtomicCounters = 0,
    .maxTessControlAtomicCounters = 0,
    .maxTessEvaluationAtomicCounters = 0,
    .maxGeometryAtomicCounters = 0,
    .maxFragmentAtomicCounters = 8,
    .maxCombinedAtomicCounters = 8,
    .maxAtomicCounterBindings = 1,
    .maxVertexAtomicCounterBuffers = 0,
    .maxTessControlAtomicCounterBuffers = 0,
    .maxTessEvaluationAtomicCounterBuffers = 0,
    .maxGeometryAtomicCounterBuffers = 0,
    .maxFragmentAtomicCounterBuffers = 1,
    .maxCombinedAtomicCounterBuffers = 1,
    .maxAtomicCounterBufferSize = 16384,
    .maxTransformFeedbackBuffers = 4,
    .maxTransformFeedbackInterleavedComponents = 64,
    .maxCullDistances = 8,
    .maxCombinedClipAndCullDistances = 8,
    .maxSamples = 4,
    .maxMeshOutputVerticesNV = 256,
    .maxMeshOutputPrimitivesNV = 512,
    .maxMeshWorkGroupSizeX_NV = 32,
    .maxMeshWorkGroupSizeY_NV = 1,
    .maxMeshWorkGroupSizeZ_NV = 1,
    .maxTaskWorkGroupSizeX_NV = 32,
    .maxTaskWorkGroupSizeY_NV = 1,
    .maxTaskWorkGroupSizeZ_NV = 1,
    .maxMeshViewCountNV = 4,
    .maxDualSourceDrawBuffersEXT = 1,
    .limits = {
        .nonInductiveForLoops = true,
        .whileLoops = true,
        .doWhileLoops = true,
        .generalUniformIndexing = true,
        .generalAttributeMatrixVectorIndexing = true,
        .generalVaryingIndexing = true,
        .generalSamplerIndexing = true,
        .generalVariableIndexing = true,
        .generalConstantMatrixVectorIndexing = true
    }
};



class MyIncluder : public glslang::TShader::Includer {
  public:
    //~ std::string directory;     //working directory for includes
    std::list<std::string> includedData;    //list so it doesn't move in RAM

    MyIncluder(){
    }
    glslang::TShader::Includer::IncludeResult* includeSystem(
        const char* ,
        const char* ,
        std::size_t ) override {
        return nullptr;
    }
    glslang::TShader::Includer::IncludeResult* includeLocal(const char* headerName,
            const char* includerName_, std::size_t inclusionDepth) override {

        verbose(
            std::string("Including '") +
                headerName + "' from '"+
                includerName_+"' (depth "+
                std::to_string(inclusionDepth)+")"
        );

        if( inclusionDepth > 100 ){
            includedData.push_back(
                std::string(
                    "Too many nested includes"
                )
            );
            error("Too many nested includes in ",headerName);
            return new IncludeResult(
                "",
                this->includedData.back().c_str(),
                this->includedData.back().length(),
                nullptr
            );
        }


        //headerName is the path of the thing that we want to include
        //includerName is the path of the file that is including it
        std::string fullpath;
        std::string includerName = includerName_;
        auto idx = includerName.rfind('/');
        if( idx == std::string::npos ){
            fullpath = "./";
        } else {
            fullpath = includerName.substr(0,idx)+"/";
        }
        fullpath += headerName;

        std::ifstream in(fullpath);
        if(!in.good() ){
            error("Could not read file '"+fullpath+"' included from '"+includerName_+"'");
            this->includedData.push_back( std::string(
                "Could not read file "+fullpath+" included from "+includerName_)
            );
            return new IncludeResult(
                "",
                this->includedData.back().c_str(),
                this->includedData.back().length(),
                nullptr
            );
        }

        std::string shaderData;
        std::getline( in, shaderData, '\0' );
        this->includedData.push_back( shaderData );

        std::filesystem::path pp(fullpath);
        pp = std::filesystem::canonical(pp);
        std::string p = pp.generic_string();
        return new IncludeResult(
            (std::string)(p),
            this->includedData.back().c_str(),
            this->includedData.back().length(),
            nullptr
        );
    }

    void releaseInclude(IncludeResult* r){
        if(r)
            delete r;
    }
};

static
VkPipelineShaderStageCreateInfo doCompile( const std::string& src,
        const std::string& filename, const std::string& type)
{
    EShLanguage lang = typeMap[type];
    glslang::TShader shader(lang);

    const char* S[1] = { src.c_str() };
    const int L[1] = { (int)src.length() };
    const char* N[1] = { filename.c_str() };
    shader.setStringsWithLengthsAndNames(S,L,N,1);

    shader.setEnvInput( glslang::EShSourceGlsl, lang, glslang::EShClientVulkan, 100 );
    shader.setEnvClient( glslang::EShClientVulkan, glslang::EShTargetVulkan_1_0 );
    shader.setEnvTarget( glslang::EShTargetSpv, glslang::EShTargetSpv_1_0 );

    MyIncluder incl;

    bool ok = shader.parse(
            &builtins,
            450,        //default version
            ECoreProfile,
            true,       //forceDefaultVersionAndProfile
            false,      //forwardCompatible
            EShMsgEnhanced,     //EShMsgDefault
            incl
    );

    const char* tmp = shader.getInfoLog();
    std::string infoLog;
    if(tmp)
        infoLog = tmp;
    tmp = shader.getInfoDebugLog();
    if(tmp){
        if(infoLog.length())
            infoLog += "\n";
        infoLog += tmp;
    }

    infoLog = trim(infoLog);

    if( infoLog.length() ){
        if( !ok ){
            error("When compiling",type,"shader '"+filename+"':");
            error(infoLog);
        } else {
            warn("When compiling",type,"shader '"+filename+"':");
            warn(infoLog);
        }
    }

    infoLog="";

    if( !ok ){
        throw std::runtime_error("Shader compilation failed");
    }

    glslang::TProgram prog;  //must declare after shader so it gets destructed first
    prog.addShader(&shader);
    ok = prog.link(EShMsgEnhanced); //EShMsgDefault

    tmp = prog.getInfoLog();
    if(tmp){
        infoLog += tmp;
    }

    tmp = prog.getInfoDebugLog();
    if(tmp){
        infoLog += tmp;
    }

    infoLog = trim(infoLog);

    if( infoLog.length() ){
        if(!ok){
            error("When compiling",type.substr(1),"shader '"+filename+"':");
            error(infoLog);
        } else {
            warn("When compiling",type.substr(1),"shader '"+filename+"':");
            warn(infoLog);
        }
    }

    if( !ok ){
        throw std::runtime_error("Shader link failed");
    }

    glslang::TIntermediate* intermediate = prog.getIntermediate(lang);
    std::vector<unsigned int> spirv;
    glslang::GlslangToSpv( *intermediate, spirv );

    return makeModule(spirv,type);
}

namespace ShaderManager {

bool initialized()
{
    return ctx != nullptr;
}

void initialize(VulkanContext* ctx_)
{
    if(initialized())
        return;

    ctx=ctx_;
    glslang::InitializeProcess();
    CleanupManager::registerCleanupFunction([](){
        for(auto& s : _shaders ){
            vkDestroyShaderModule(ctx->dev, s.module, nullptr);
        }
        glslang::FinalizeProcess();
    });
}

VkPipelineShaderStageCreateInfo load(std::string filename)
{

    std::string suffix;

    auto dotpos = filename.rfind('.');
    if(dotpos != std::string::npos ){
        suffix = filename.substr(dotpos+1);
    }

    if( !typeMap.contains(suffix) ){
        throw std::runtime_error("Shader filename must end with one of: .vert, .frag, .tesc, .tese, .geom, .comp");
    }

    return load(filename,suffix);
}

VkPipelineShaderStageCreateInfo load(std::string filename, std::string type)
{
    if( !typeMap.contains(type) ){
        throw std::runtime_error("Type must be one of: vert, frag, tesc, tese, geom, comp");
    }

    std::ifstream in(filename);
    if(!in.good())
        throw std::runtime_error("Cannot read shader file "+filename);

    std::string src;
    std::getline( in, src, '\0');

    return doCompile(src, filename, type );
}

VkPipelineShaderStageCreateInfo loadFromString(std::string src, std::string type)
{
    if( !typeMap.contains(type) ){
        throw std::runtime_error("Shader type must be one of: vert, frag, tesc, tese, geom, comp");
    }

    return doCompile(src, "internal source", type );
}

}; //namespace
