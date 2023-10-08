#include "PushConstants.h"
#include "parseMembers.h"
#include "Pipeline.h"
#include "mischelpers.h"
#include "math2801.h"
#include "consoleoutput.h"
#include <assert.h>
#include <array>

//Vk standard specifies this
#define PUSHCONSTANT_MAX 128

//~ static PushConstants::PushConstants* _default;

template<typename T>
static void doSet(PushConstants* pushc, VkCommandBuffer cmd, const std::string& name, const T& value)
{
    
    if( pushc->items.find(name) == pushc->items.end() ){
        error("No such push constant '"+name+"'");
        error("Known push constants:");
        for(auto it : pushc->items ){
            error("    ",it.second.name,"("+it.second.typeAsString+it.second.arraySizeAsString+")");
        }
        throw std::runtime_error("No such push constant '"+name+"'");
    }
    auto& tmp = pushc->items[name];
    auto converted = tmp.convert(value);
    vkCmdPushConstants(
        cmd,
        Pipeline::current()->pipelineLayout->pipelineLayout,
        VK_SHADER_STAGE_ALL,
        tmp.offset,
        tmp.byteSize,
        converted.data()
    );
}


//~ namespace PushConstants{

//~ int byteSize;


PushConstants::PushConstants(std::string filename)
{
    if( filename.empty() ){
        this->byteSize=0;
        this->items={};
        return;
    }
    
    std::tuple<int,std::map<std::string,parseMembers::Item>,std::map<std::string,int> > tmp;
    
    //auto-detect if it's an inline string
    if( filename.find("layout(") == 0 ){
        tmp = parseMembers::parseFromString(filename);
    } else {
        tmp = parseMembers::parse(filename);
    }
    
    this->byteSize=std::get<0>(tmp);
    this->items = std::get<1>(tmp);

    verbose("Discovered these push constants:");
    for(auto it : this->items ){
        verbose(it.second.typeAsString+it.second.arraySizeAsString,
            it.second.name,
            " offset=",it.second.offset,"byteSize=",it.second.byteSize);
    }

    verbose("Total size of all push constants:",byteSize);
    
    if(byteSize > PUSHCONSTANT_MAX ){
        throw std::runtime_error(
            std::string("Push constants are too large: Got ")+
            byteSize+" but max is "+PUSHCONSTANT_MAX);
    }
}
 
void PushConstants::set(VkCommandBuffer cmd, std::string name, int value)
{
    doSet(this,cmd,name,std::int32_t(value));
}

void PushConstants::set(VkCommandBuffer cmd, std::string name, unsigned value)
{
    doSet(this,cmd,name,std::uint32_t(value));
}

void PushConstants::set(VkCommandBuffer cmd, std::string name, float value)
{
    doSet(this,cmd,name,value);
}
void PushConstants::set(VkCommandBuffer cmd, std::string name, double value)
{
    doSet(this,cmd,name,float(value));
}
void PushConstants::set(VkCommandBuffer cmd, std::string name, math2801::vec2 value)
{
    doSet(this,cmd,name,value);
}

void PushConstants::set(VkCommandBuffer cmd, std::string name, math2801::ivec2 value)
{
    doSet(this,cmd,name,value);
}

void PushConstants::set(VkCommandBuffer cmd, std::string name, math2801::vec3 value)
{
    doSet(this,cmd,name,value);
}
void PushConstants::set(VkCommandBuffer cmd, std::string name, math2801::vec4 value)
{
    doSet(this,cmd,name,value);
}
void PushConstants::set(VkCommandBuffer cmd, std::string name, math2801::mat4 value)
{
    doSet(this,cmd,name,value);
}

void PushConstants::set(VkCommandBuffer cmd, std::string name, const std::vector<math2801::vec4>& value)
{
    doSet(this,cmd,name,value);
}

void PushConstants::set(VkCommandBuffer cmd, std::string name, const std::vector<math2801::uvec4>& value)
{
    doSet(this,cmd,name,value);
}

void PushConstants::set(VkCommandBuffer cmd, std::string name, const std::vector<math2801::ivec4>& value)
{
    doSet(this,cmd,name,value);
}
//~ void initialize(VulkanContext* )
//~ {
    //~ if( !initialized() ){
        //~ _default = new PushConstants("shaders/pushconstants.txt");
        //~ byteSize = _default->byteSize;
    //~ }
//~ }

//~ bool initialized(){
    //~ return _default != nullptr;
//~ }

//~ void set(VkCommandBuffer cmd, std::string name, std::int32_t value)
//~ {
    //~ _default->set(cmd,name,value);
//~ }

//~ void set(VkCommandBuffer cmd, std::string name, std::uint32_t value)
//~ {
    //~ _default->set(cmd,name,value);
//~ }
//~ void set(VkCommandBuffer cmd, std::string name, float value)
//~ {
    //~ _default->set(cmd,name,value);
//~ }
//~ void set(VkCommandBuffer cmd, std::string name, double value)
//~ {
    //~ _default->set(cmd,name,value);
//~ }
//~ void set(VkCommandBuffer cmd, std::string name, math2801::ivec2 value)
//~ {
    //~ _default->set(cmd,name,value);
//~ }
//~ void set(VkCommandBuffer cmd, std::string name, math2801::vec2 value)
//~ {
    //~ _default->set(cmd,name,value);
//~ }
//~ void set(VkCommandBuffer cmd, std::string name, math2801::vec3 value)
//~ {
    //~ _default->set(cmd,name,value);
//~ }
//~ void set(VkCommandBuffer cmd, std::string name, math2801::vec4 value)
//~ {
    //~ _default->set(cmd,name,value);
//~ }
//~ void set(VkCommandBuffer cmd, std::string name, math2801::mat4 value)
//~ {
    //~ _default->set(cmd,name,value);
//~ }
//~ void set(VkCommandBuffer cmd, std::string name, const std::vector<math2801::vec4>& value)
//~ {
    //~ _default->set(cmd,name,value);
//~ }


//~ }; //namespace
  
