#include "Uniforms.h"
#include "Descriptors.h"
#include "CleanupManager.h"
#include "Buffers.h"
#include "consoleoutput.h"
#include "utils.h"
#include <cassert>
#include <cstring>
#include <array>

template<typename T>
static void _set(
    std::map<std::string, parseMembers::Item>& items,
    std::vector<char>& shadowBuffer,
    const std::string& name, const T& value,
    std::set<std::string>& uninitialized)
{
    auto tmp = items.find(name);
    if (tmp == items.end()) {
        error("No such uniform '" + name + "'");
        error("Known uniforms:");
        for (auto it : items) {
            error(it.second.name, "(",
                it.second.typeAsString +
                it.second.arraySizeAsString,
                ") "
            );
        }
        throw std::runtime_error("No such uniform '" + name + "'");
    }
    auto& info = tmp->second;
    std::vector<char> convertedValue = info.convert(value);
    std::memcpy(shadowBuffer.data() + info.offset, convertedValue.data(), info.byteSize);
    uninitialized.erase(name);
}

//~ Uniforms::Uniforms(VulkanContext* ctx, PerFrameDescriptorSet* perFrameDescriptorSet, int slotNumber, std::string uniformFile) :
    //~ Uniforms(ctx,std::vector<PerFrameDescriptorSet*>{perFrameDescriptorSet},slotNumber,uniformFile)
//~ {}

Uniforms::Uniforms(VulkanContext* ctx_, std::string uniformFile)
{
    auto tmp = parseMembers::parse(uniformFile);
    this->init(ctx_, tmp, uniformFile);
}

//private constructor, for use in createFromData
Uniforms::Uniforms() {
}

Uniforms* Uniforms::createFromData(VulkanContext* ctx, const std::string& uniformData)
{
    Uniforms* U = new Uniforms();
    auto tmp = parseMembers::parseFromString(uniformData);
    U->init(ctx, tmp, "<string>");
    return U;
}

void Uniforms::init(VulkanContext* ctx_,
    std::tuple<int, std::map<std::string, parseMembers::Item>, std::map<std::string, int> > info,
    std::string inputFile)
{

    this->ctx = ctx_;
    this->byteSize = std::get<0>(info);
    this->items = std::get<1>(info);
    this->defines = std::get<2>(info);

    verbose("Uniforms: Discovered these uniforms in file", inputFile, ":");
    for (auto it : this->items) {
        this->uninitialized.insert(it.second.name);
        verbose(it.second.typeAsString, it.second.arraySizeAsString, it.second.name);
    }

    this->shadowBuffer.resize(byteSize);

    verbose("Uniforms: Original byteSize is", byteSize);

    //create a dummy so we can get the memory requirements
    DeviceLocalBuffer* buff = new DeviceLocalBuffer(
        this->ctx, nullptr, this->byteSize,
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        "dummy for uniforms"
    );
    this->memoryTypeBits = buff->memoryRequirements.memoryTypeBits;

    //ensure byteSize is a multiple of alignment
    std::size_t extra = this->byteSize % buff->memoryRequirements.alignment;
    this->byteSize += (buff->memoryRequirements.alignment - extra);

    verbose("Uniforms: Alignment is:", buff->memoryRequirements.alignment, "size:", buff->memoryRequirements.size);
    verbose("Uniforms: Adjusted byteSize to", byteSize);

    buff->cleanup();
    buff = nullptr;

    utils::registerFrameCompleteCallback([this](unsigned frameNumber) {
        if (this->activeBuffers.contains(frameNumber)) {

            this->availableBuffers.insert(
                this->availableBuffers.end(),
                this->activeBuffers[frameNumber].begin(),
                this->activeBuffers[frameNumber].end()
            );
            this->activeBuffers.erase(frameNumber);
        }
        });

    CleanupManager::registerCleanupFunction([this]() {
        for (DeviceLocalBuffer* abuff : this->availableBuffers) {
            abuff->cleanup();
        }
        for (auto it = this->activeBuffers.begin(); it != this->activeBuffers.end(); ++it) {
            for (DeviceLocalBuffer* b : it->second) {
                b->cleanup();
            }
        }
        if (this->currentBuffer)
            this->currentBuffer->cleanup();
        for (VkDeviceMemory mem : this->memories) {
            vkFreeMemory(this->ctx->dev, mem, nullptr);
        }
        });
}

void Uniforms::ensureCurrentIsValid()
{
    if (this->currentBuffer == nullptr) {
        if (this->availableBuffers.size() == 0) {
            VkDeviceSize numBuffers = (1 << 20) / this->byteSize;
            if (numBuffers == 0) {
                throw std::runtime_error("Size of uniforms is too large");
            }
            VkDeviceSize allBufferBytes = numBuffers * this->byteSize;

            verbose("Allocated memory for uniforms:", allBufferBytes, "; each uniform buffer is", this->byteSize, "bytes");

            VkDeviceMemory mem = DeviceLocalBuffer::allocateMemory(
                this->ctx,
                this->memoryTypeBits,
                allBufferBytes,
                "memory for uniforms");
            this->memories.push_back(mem);
            VkDeviceSize offset = 0;
            for (VkDeviceSize i = 0; i < numBuffers; ++i) {
                this->availableBuffers.push_back(new DeviceLocalBuffer(
                    this->ctx,
                    mem, offset, this->byteSize,
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                    "uniform buffer")
                );
                offset += this->byteSize;
            }
        }
        this->currentBuffer = this->availableBuffers.back();
        this->availableBuffers.pop_back();
    }
}

//~ void Uniforms::bind(VkCommandBuffer cmd, int index)
//~ {
    //~ assert(index != -1 );
    //~ this->descriptorSets[index]->bind(cmd);
//~ }

void Uniforms::set(const std::string& name, std::int32_t value) { _set(this->items, this->shadowBuffer, name, value, this->uninitialized); }
void Uniforms::set(const std::string& name, std::uint32_t value) { _set(this->items, this->shadowBuffer, name, value, this->uninitialized); }
void Uniforms::set(const std::string& name, float value) { _set(this->items, this->shadowBuffer, name, value, this->uninitialized); }
void Uniforms::set(const std::string& name, math2801::ivec2 value) { _set(this->items, this->shadowBuffer, name, value, this->uninitialized); }
void Uniforms::set(const std::string& name, math2801::vec2 value) { _set(this->items, this->shadowBuffer, name, value, this->uninitialized); }
void Uniforms::set(const std::string& name, math2801::vec3 value) { _set(this->items, this->shadowBuffer, name, value, this->uninitialized); }
void Uniforms::set(const std::string& name, math2801::vec4 value) { _set(this->items, this->shadowBuffer, name, value, this->uninitialized); }
void Uniforms::set(const std::string& name, math2801::mat4 value) { _set(this->items, this->shadowBuffer, name, value, this->uninitialized); }
void Uniforms::set(const std::string& name, const std::vector<math2801::vec4>& value) { _set(this->items, this->shadowBuffer, name, value, this->uninitialized); }
void Uniforms::set(const std::string& name, const std::vector<math2801::mat4>& value) { _set(this->items, this->shadowBuffer, name, value, this->uninitialized); }
void Uniforms::set(const std::string& name, double value) { this->set(name, (float)value); }

void Uniforms::update(VkCommandBuffer cmd, DescriptorSet* descriptorSet, int slot)
{
    ensureCurrentIsValid();
    Buffers::memoryBarrier(cmd, this->currentBuffer->buffer);
    vkCmdUpdateBuffer(cmd, this->currentBuffer->buffer,
        0, this->shadowBuffer.size(),
        this->shadowBuffer.data());
    Buffers::memoryBarrier(cmd, this->currentBuffer->buffer);
    unsigned f = utils::getCurrentFrameIdentifier();
    this->activeBuffers[f].push_back(this->currentBuffer);

    descriptorSet->setSlot(slot, this->currentBuffer->buffer);
    //~ descriptorSet->bind(cmd);       //easy to forget this if we leave it to the caller
    this->currentBuffer = nullptr;
    if (!uninitialized.empty()) {
        std::vector<std::string> v;
        for (const std::string& s : this->uninitialized) {
            v.push_back(s);
        }
        std::string txt;
        if (v.size() == 1)
            txt = "uniform:";
        else
            txt = "uniforms:";
        warn("Uninitialized", txt, v);
    }
}

int Uniforms::getDefine(const std::string& name)
{
    if (this->defines.contains(name))
        return this->defines[name];
    else
        throw std::runtime_error("No such #define constant '" + name + "' in uniforms");
}

bool Uniforms::hasDefine(const std::string& name)
{
    return this->defines.contains(name);
}
