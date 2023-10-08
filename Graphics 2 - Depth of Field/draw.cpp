#include "vkhelpers.h"
#include "utils.h"
#include "Globals.h"
#include "Uniforms.h"
#include "importantConstants.h"
#include "utils.h"
#include "Samplers.h"

void draw(Globals& globs)
{
    //begin rendering the frame
    VkCommandBuffer cmd = utils::beginFrame(globs.ctx);

    //set skybox environmap
    globs.descriptorSet->setSlot(
        ENVMAP_TEXTURE_SLOT,
        globs.Environmap->view()
    );

    //set uniforms
    globs.uniforms->set("focalDistance", globs.focD);
    globs.uniforms->set("reflectionMatrix", globs.reflectionMatrix);
    globs.uniforms->set("reflectionPlane", globs.reflectionPlane);
    globs.camera.setUniforms(globs.uniforms);
    globs.allLights->setUniforms(globs.uniforms);
    globs.uniforms->update(cmd,globs.descriptorSet,UNIFORM_BUFFER_SLOT);

    //bind descriptor set
    globs.descriptorSet->bind(cmd);

    //begin rendering to the screen
    globs.offscreen->beginRenderPassClearContents(
        cmd,
        0.2f, 0.4f, 0.8f, 1.0f
    );

    //activate the pipeline
    globs.pipeline->use(cmd);

    //set source for vertex data
    globs.vertexManager->bindBuffers(cmd);

    
    //draw the meshes
    for(auto& m : globs.allMeshes){
      m->draw(cmd,globs.descriptorSet,globs.pushConstants);
    }

  

    //draw the sky
    globs.skymappipeline->use(cmd);
    globs.descriptorSet->setSlot(
        ENVMAP_TEXTURE_SLOT, globs.skyBoxImage->view());
    globs.descriptorSet->bind(cmd);
    globs.skyboxMesh->draw(cmd,
        globs.descriptorSet, globs.pushConstants);

    //done rendering
    globs.offscreen->endRenderPass(cmd);
   
    globs.offscreen->blur(15, 1, 1.0f, cmd, globs.vertexManager);

    globs.framebuffer->beginRenderPassClearContents(
        cmd, 1.0f, 0.0f, 0.0f, 1.0f
    );
    globs.blitPipe->use(cmd);
    
    globs.descriptorSet->setSlot(BASE_TEXTURE_SAMPLER_SLOT,
        Samplers::clampingMipSampler);
    globs.descriptorSet->setSlot(NEAREST_SAMPLER_SLOT,
        Samplers::nearestSampler);
    globs.descriptorSet->setSlot(BASE_TEXTURE_SLOT,
        globs.offscreen->currentImage()->view());
    globs.descriptorSet->setSlot(DEPTH_TEXTURE_SLOT,
        globs.offscreen->currentDepthBufferView());
    globs.descriptorSet->bind(cmd);

    globs.blitSquare->draw(cmd, globs.descriptorSet, nullptr);

    //globs.blitSquare->draw(cmd, globs.descriptorSet, globs.offscreen->currentImage());


    globs.framebuffer->endRenderPass(cmd);

    utils::endFrame(globs.ctx);

}