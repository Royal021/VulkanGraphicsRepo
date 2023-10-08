#pragma once
#include "math2801.h"
#include "vkhelpers.h"
class Image;
class VulcanContext;
class VertexManager;
class BillboardCollection;
class DescriptorSet;
class Buffer;
class VKBufferView;

class ParticleSystem {
	public:	
		ParticleSystem
		(
			VulkanContext* ctx,
			VertexManager* vertexManager,
			math2801::vec3 origin,
			math2801::vec3 minvel,
			math2801::vec3 maxvel,
			unsigned numParticles,
			Image* img
		);

		void update(float elapsed);
		void draw(VkCommandBuffer cmd, DescriptorSet* descriptorSet);
		void compute(VkCommandBuffer cmd);
	VulkanContext* ctx;
		
	math2801::vec3 origin;
	math2801::vec3 minvel;
	math2801::vec3 maxvel;
	unsigned numParticles;
	Image* img;
	BillboardCollection* billboardCollection;
	VkBufferView velocityView;
	Buffer* velocities;
	float accumulated = 0.0f;


};