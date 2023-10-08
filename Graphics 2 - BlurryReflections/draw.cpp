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
    globs.uniforms->set("reflectionMatrix", globs.reflectionMatrix);
    globs.uniforms->set("reflectionPlane", globs.reflectionPlane);
    globs.camera.setUniforms(globs.uniforms);
    globs.allLights->setUniforms(globs.uniforms);
    globs.uniforms->update(cmd,globs.descriptorSet,UNIFORM_BUFFER_SLOT);

    //bind descriptor set
    globs.descriptorSet->bind(cmd);
    globs.vertexManager->bindBuffers(cmd);
    
    ////////////////////////////////////////////////////////////
    //start offscreen render
    globs.offscreen->beginRenderPassClearContents(
        cmd,
        0.2f, 0.4f, 0.8f, 1.0f
    );

    
    globs.pipeline->use(cmd);
    //draw ordinary objects
    globs.pushConstants->set(cmd, "doingReflections", 1);
    for (auto& m : globs.allMeshes) {
        if (m->name != "floor")
            m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    }

    globs.offscreen->endRenderPass(cmd);
    globs.offscreen->blur(5, 0, 1.0f, cmd, globs.vertexManager);
    globs.offscreen->blur(15, 0, 1.0f, cmd, globs.vertexManager);
        //////////////////////////////////////////////////////////////////
    //begin rendering to the screen
    globs.framebuffer->beginRenderPassClearContents(cmd, 0.2f, 0.4f, 0.8f, 1.0f);

    //activate the pipeline
    globs.pipelineForWindow->use(cmd);
    globs.pushConstants->set(cmd, "doingReflections", 0);
    for (auto& m : globs.allMeshes) {
        if (m->name != "floor")
            m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    }
    ////set source for vertex data
    globs.vertexManager->bindBuffers(cmd);


    // draw the floor
    globs.floorPipeline1->use(cmd);
    globs.pushConstants->set(cmd, "doingReflections", 2);
    for (auto& m : globs.allMeshes) {
        if (m->name == "floor")
            m->draw(cmd, globs.descriptorSet, globs.pushConstants);
        }

    //clear and set reflected objects
    //globs.framebuffer->clear(cmd, {}, 1.0f, {});
    //globs.reflectedObjectsPipeline->use(cmd);
    ////reflected objects
    //globs.pushConstants->set(cmd, "doingReflections", 1);
    //for (auto& m : globs.allMeshes) {
    //    if (m->name != "floor")
    //        m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    //}

    globs.copyReflectionsToScreen->use(cmd);
    globs.descriptorSet->bind(cmd);
    globs.blitSquare->draw(cmd, globs.descriptorSet,  globs.offscreen->currentImage());

    //globs.blitSquare->draw(cmd, globs.descriptorSet, nullptr);
    //draw the floor
    globs.pushConstants->set(cmd, "doingReflections", 2);
    globs.floorPipeline2->use(cmd);
    for (auto& m : globs.allMeshes) {
       if (m->name == "floor")
            m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    }
    
 
    


    //draw the sky
    globs.skymappipeline->use(cmd);
    globs.descriptorSet->setSlot(
        ENVMAP_TEXTURE_SLOT, globs.skyBoxImage->view());
    globs.descriptorSet->bind(cmd);
    //globs.skyboxMesh->draw(cmd,
        //globs.descriptorSet, globs.pushConstants);

    //done rendering
    globs.framebuffer->endRenderPass(cmd);

    //submit frame to GPU
    utils::endFrame(globs.ctx);
}
