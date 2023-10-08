#include "vkhelpers.h"
#include "utils.h"
#include "Globals.h"
#include "Uniforms.h"
#include "importantConstants.h"
#include "utils.h"

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
    globs.lightCamera.setUniforms(globs.uniforms, ""); // change
    globs.lightCamera.setUniforms(globs.uniforms, "light_");
    globs.allLights->setUniforms(globs.uniforms);
    globs.uniforms->update(cmd,globs.descriptorSet,UNIFORM_BUFFER_SLOT);

    //bind descriptor set
    globs.descriptorSet->bind(cmd);


    //begin rendering to the screen
    //globs.framebuffer->beginRenderPassClearContents(cmd, 0.2f, 0.4f, 0.8f, 1.0f);


    globs.shadowBuffer->beginRenderPassClearContents(cmd, 1.0f, 1.0f, 1.0f, 1.0f);

    globs.vertexManager->bindBuffers(cmd);
    globs.shadowPipeline->use(cmd);

    //draw meshes
    for (auto& m : globs.allMeshes) {
        m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    }

    globs.shadowBuffer->endRenderPass(cmd);
   
    globs.camera.setUniforms(globs.uniforms, "");
    globs.lightCamera.setUniforms(globs.uniforms, "light_");
    globs.uniforms->update(cmd, globs.descriptorSet, UNIFORM_BUFFER_SLOT);

    globs.framebuffer->beginRenderPassClearContents(cmd, 0.2f, 0.4f, 0.8f, 1.0f);

    globs.descriptorSet->setSlot(SHADOWBUFFER_SLOT, globs.shadowBuffer->currentImage()->view());
    globs.descriptorSet->bind(cmd);
    globs.vertexManager->bindBuffers(cmd);
    globs.pipeline->use(cmd);

    //draw meshes
    for (auto& m : globs.allMeshes) {
        m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    }

    //draw the sky
    globs.skymappipeline->use(cmd);
    globs.descriptorSet->setSlot(ENVMAP_TEXTURE_SLOT, globs.skyBoxImage->view());
    globs.descriptorSet->bind(cmd);
    globs.skyboxMesh->draw(cmd, globs.descriptorSet, globs.pushConstants);

    //done rendering
    globs.framebuffer->endRenderPass(cmd);

    //submit frame to GPU
    utils::endFrame(globs.ctx);
}
