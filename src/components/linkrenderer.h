#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "../component.h"
#include "../framebuffer.h"
#include "../registries.h"
#include "../room.h"

namespace COMP {
class LinkRenderer : public Component {
   public:
    LinkRenderer(FrameBuffer* frameBuffer)
        : _SHADER_PROGRAM{REG::SHADER_PROGRAMS().get(SHADER_PROGRAM_LINK)},
          _mesh{REG::MESHES().get(MESH_QUAD)},
          _FRAME_BUFFER{frameBuffer} {}

    void update(double const& dt) override {}
    void enterRoom(Room* newRoom) override {}
    void exitRoom(Room* oldRoom) override {}
    void render(glm::mat4 const& m) override {
        // Get cameras
        std::vector<COMP::Camera*> cameras = _parent->getRoom()->getCameras();

        // Skip render pass if there are no cameras
        if (cameras.empty())
            return;

        // Bind shader program
        _SHADER_PROGRAM->bind();

        // Send Matrices
        glm::mat4 modelMat = _parent->getGlobalTransformMatrix();
        glUniformMatrix4fv(UNILOC_MODEL_MAT, 1, GL_FALSE,
                           glm::value_ptr(modelMat));

        glUniformMatrix4fv(UNILOC_VIEW_MAT, 1, GL_FALSE,
                           glm::value_ptr(cameras[0]->viewMatrix()));

        glUniformMatrix4fv(UNILOC_PROJECTION_MAT, 1, GL_FALSE,
                           glm::value_ptr(cameras[0]->projectionMatrix()));

        // Render Mesh
        _mesh->bind();

        glDrawElements(GL_TRIANGLES, _mesh->getNrIndices(), GL_UNSIGNED_INT, 0);
    }

    void attach() override {}
    void detach() override {}

    void connect(LinkRenderer* target) {
        _target = target;
    }

   private:
    ShaderProgram* const _SHADER_PROGRAM;
    FrameBuffer* const _FRAME_BUFFER;
    LinkRenderer* _target;
    ::Mesh* _mesh;
};
}  // namespace COMP
