#include "particleSystem.h"
#include "vkhelpers.h"
#include "math2801.h"
#include "VertexManager.h"
#include "BillboardCollection.h"
#include "Buffers.h"
#include "PushConstants.h"
#include "Pipeline.h"
#include "Descriptors.h"
#include "ComputePipeline.h"
#include "ShaderManager.h"
#include "importantConstants.h"
#include <cassert>
#include "CleanupManager.h"


using namespace math2801;

static PushConstants* computePushConstants;

static ComputePipeline* computePipeline;

static PipelineLayout* computePipelineLayout;

static DescriptorSetFactory* computeDescriptorSetFactory;

static DescriptorSetLayout* computeDescriptorSetLayout;

static DescriptorSet* computeDescriptorSet;


static void initialize(VulkanContext* ctx)
{
	computePushConstants = new PushConstants("shaders/particlePushConstants.txt");
	computeDescriptorSetLayout = new DescriptorSetLayout(
		ctx,
		{
			{.type = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, .slot = 0 },
			{.type = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, .slot = 1 }
		}
	);
	computePipelineLayout = new PipelineLayout(
		ctx,
		computePushConstants,
		{
			computeDescriptorSetLayout,
			nullptr,
			nullptr
		},
		"computePipelineLayout"
	);

	computePipeline = new ComputePipeline(
		ctx, computePipelineLayout,
		ShaderManager::load("shaders/particle.comp"),
		"computePipeline");

	computeDescriptorSetFactory = new DescriptorSetFactory(
		ctx, "particle ds factory", 0, computePipelineLayout);
	computeDescriptorSet = computeDescriptorSetFactory->make();
}


ParticleSystem::ParticleSystem(
	VulkanContext* ctx_,
	VertexManager* vertexManager,
	math2801::vec3 origin_,
	math2801::vec3 minvel_,
	math2801::vec3 maxvel_,
	unsigned numParticles_,
	Image* img_

)
{

	if (computePipeline == nullptr) {
		initialize(ctx_);
	}

	this->ctx = ctx_;
	this->origin = origin_;
	this->minvel = minvel_;
	this->maxvel = maxvel_;
	this->numParticles = numParticles_;
	this->img = img_;

	assert(numParticles % WORKGROUP_SIZE == 0);

	
	std::vector<vec4> pos(numParticles_);
	for (unsigned i = 0; i < numParticles_; ++i) {
		//new: w is not hardcoded to 1.0
		pos[i] = vec4(origin_, uniform(0.5f, 5.0f));
	}

	std::vector<vec4> vel;
	vel.reserve(numParticles_);
	for (unsigned i = 0; i < numParticles; ++i)
	{
		vel.push_back
		(
			vec4
			(
				math2801::uniform(minvel.x, maxvel.x),
				math2801::uniform(minvel.y, maxvel.y),
				math2801::uniform(minvel.z, maxvel.z),
				0.0f
			)
		);

	}

	this->velocities = new DeviceLocalBuffer(ctx, vel,
		VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT |
		VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
		"psystem vel"
	);

	this->velocityView = this->velocities->makeView(
		VK_FORMAT_R32G32B32A32_SFLOAT
	);

	this->billboardCollection = new BillboardCollection(
		ctx, vertexManager, pos, vec2(0.1f, 0.1f), img);

	this->origin = origin_;

	CleanupManager::registerCleanupFunction([this, ctx_]() {
		this->velocities->cleanup();
		vkDestroyBufferView(ctx->dev, this->velocityView, nullptr);
		});
}

void ParticleSystem::update(float elapsed)
{
	this->accumulated += elapsed;
}

void ParticleSystem::compute(VkCommandBuffer cmd)
{
	if (this->accumulated < PARTICLE_TIME_QUANTUM)
		return;

	computeDescriptorSet->setSlot(0, this->billboardCollection->positionView);
	computeDescriptorSet->setSlot(1, this->velocityView);
	computeDescriptorSet->bind(cmd);

	computePipeline->use(cmd);
	computePushConstants->set(cmd, "startingPoint", this->origin);
	computePushConstants->set(cmd, "elapsed", PARTICLE_TIME_QUANTUM);
	while (this->accumulated >= PARTICLE_TIME_QUANTUM) {
		this->accumulated -= PARTICLE_TIME_QUANTUM;
		vkCmdDispatch(cmd,
			this->numParticles / WORKGROUP_SIZE,
			1,
			1
		);
		this->billboardCollection->positions->memoryBarrier(cmd);
		this->velocities->memoryBarrier(cmd);
	}
}


void ParticleSystem::draw(VkCommandBuffer cmd,
	DescriptorSet* descriptorSet)
{
	this->billboardCollection->draw(cmd, descriptorSet);
}