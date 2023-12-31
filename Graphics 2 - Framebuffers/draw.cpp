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

    //begin rendering to the screen
    //globs.framebuffer->beginRenderPassClearContents(cmd, 0.2f, 0.4f, 0.8f, 1.0f);
    globs.offscreen->beginRenderPassClearContents(
        cmd,
        0.2f, 0.4f, 0.8f, 1.0f
    );

    //activate the pipeline
    globs.pipeline->use(cmd);

    //set source for vertex data
    globs.vertexManager->bindBuffers(cmd);

    ////draw ordinary objects
    //globs.pushConstants->set(cmd, "doingReflections", 0);
    //for (auto& m : globs.allMeshes) {
    //    if (m->name != "floor")
    //        m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    //}
    //// draw the floor
    //globs.floorPipeline1->use(cmd);
    //for (auto& m : globs.allMeshes) {
    //    if (m->name == "floor")
    //        m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    //    }

    ////clear and set reflected objects
    //globs.framebuffer->clear(cmd, {}, 1.0f, {});
    //globs.reflectedObjectsPipeline->use(cmd);
    ////reflected objects
    //globs.pushConstants->set(cmd, "doingReflections", 1);
    //for (auto& m : globs.allMeshes) {
    //    if (m->name != "floor")
    //        m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    //}

    ////draw the floor
    //globs.pushConstants->set(cmd, "doingReflections", 2);
    //globs.floorPipeline2->use(cmd);
    //for (auto& m : globs.allMeshes) {
    //    if (m->name == "floor")
    //        m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    //}

    //draw the meshes
    for(auto& m : globs.allMeshes){
      m->draw(cmd,globs.descriptorSet,globs.pushConstants);
    }

  

    //draw the sky
    globs.skymappipeline->use(cmd);
    globs.descriptorSet->setSlot(
        ENVMAP_TEXTURE_SLOT, globs.skyBoxImage->view());
    globs.descriptorSet->bind(cmd);
    //globs.skyboxMesh->draw(cmd,
        //globs.descriptorSet, globs.pushConstants);

    //done rendering
    //globs.framebuffer->endRenderPass(cmd);
    globs.offscreen->endRenderPass(cmd);
   
    globs.framebuffer->beginRenderPassClearContents(
        cmd, 1.0f, 0.0f, 0.0f, 1.0f
    );
    globs.blitPipe->use(cmd);
    
    globs.blitSquare->draw(cmd, globs.descriptorSet,
        globs.offscreen->currentImage());


    globs.framebuffer->endRenderPass(cmd);

    utils::endFrame(globs.ctx);

}