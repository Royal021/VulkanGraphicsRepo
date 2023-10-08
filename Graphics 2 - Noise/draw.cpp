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

    globs.particleSystem->compute(cmd);
    //set skybox environmap
    globs.descriptorSet->setSlot(
        ENVMAP_TEXTURE_SLOT,
        globs.Environmap->view()
    );

    //set uniforms
    globs.camera.setUniforms(globs.uniforms);
    globs.allLights->setUniforms(globs.uniforms);
    globs.uniforms->update(cmd,globs.descriptorSet,UNIFORM_BUFFER_SLOT);

    //bind descriptor set
    globs.descriptorSet->bind(cmd);

    //begin rendering to the screen
    globs.framebuffer->beginRenderPassClearContents(cmd, 0.2f, 0.4f, 0.8f, 1.0f);

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

    globs.pipelineDrawBillboards->use(cmd);
    //can translate entire billboard system around as a unit
    //with worldMatrix
    globs.pushConstants->set(cmd, "worldMatrix",
        math2801::mat4::identity());
    globs.particleSystem->draw(cmd, globs.descriptorSet);
    //globs.billboardCollection->draw(cmd, globs.descriptorSet);
    //done rendering
    globs.framebuffer->endRenderPass(cmd);

    //submit frame to GPU
    utils::endFrame(globs.ctx);
}
