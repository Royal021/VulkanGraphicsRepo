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

    //set uniforms
    globs.uniforms->set("flattenMatrix", globs.flattenMatrix);
    globs.camera.setUniforms(globs.uniforms);
    globs.allLights->setUniforms(globs.uniforms);
    globs.uniforms->update(cmd, globs.descriptorSet, UNIFORM_BUFFER_SLOT);

    //bind descriptor set
    globs.descriptorSet->bind(cmd);

    //begin rendering to the screen
    globs.framebuffer->beginRenderPassClearContents(cmd, 0.2f, 0.4f, 0.8f, 1.0f);

    //set source for vertex data
    globs.vertexManager->bindBuffers(cmd);
    
    //og scene
    globs.pipelineNonFloor->use(cmd);
    globs.pushConstants->set(cmd, "doingShadow", 0);
    for (auto& m : globs.allMeshes) {
        if (m->name != "floor") {
            m->draw(cmd, globs.descriptorSet, globs.pushConstants);
        }
    }

    //Draw floor
    globs.pipelineFloor->use(cmd);
    for (auto& m : globs.allMeshes) {
        if (m->name == "floor") {
            m->draw(cmd, globs.descriptorSet, globs.pushConstants);
        }
    }

    //Draw flattened objects
    globs.pipelineShadow->use(cmd);
    for (Mesh* m : globs.allMeshes) {
        if (m->name != "floor" && m->name != "room") {
            m->draw(cmd, globs.descriptorSet, globs.pushConstants);
        }
    }

    //Draw floor with ambient illumination (SB==2)
    globs.pipelineFloorShadow->use(cmd);
    globs.pushConstants->set(cmd, "doingShadow", 1);
    for (Mesh* m : globs.allMeshes) {
        if (m->name == "floor") {
            m->draw(cmd, globs.descriptorSet, globs.pushConstants);
        }
    }
    //Draw the above pipeline
    for (auto& m : globs.allMeshes) {
        m->draw(cmd, globs.descriptorSet, globs.pushConstants);
    }
    
    //render
    globs.framebuffer->endRenderPass(cmd);

    utils::endFrame(globs.ctx);
}