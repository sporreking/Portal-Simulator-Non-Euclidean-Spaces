#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "../registries.h"
#include "camera.h"
#include "mesh.h"

namespace COMP {
class SkyboxRenderer : public Component {
   public:
    SkyboxRenderer()
        : _SHADER_PROGRAM{REG::SHADER_PROGRAMS().get(SHADER_PROGRAM_SKYBOX)},
          _mesh{REG::MESHES().get(MESH_SKYBOX)} {}

    void update(double const& dt) override {}
    void enterRoom(Room* newRoom) override {}
    void exitRoom(Room* oldRoom) override {}

    void render(glm::mat4 const& m, COMP::Camera* c = nullptr) override {
        COMP::Camera* camera = _getCamera(c);
        if (!camera) return;

        // Send Material
        _SHADER_PROGRAM->sendMaterial(_material);
        ((Cubemap*)_material->TEXTURE)->bind();

        // Remove translation from matrices
        glm::mat4 t = m;
        t[3][0] = 0;
        t[3][1] = 0;
        t[3][2] = 0;

        glm::mat4 camMat = camera->viewMatrix();
        camMat[3][0] = 0;
        camMat[3][1] = 0;
        camMat[3][2] = 0;

        // Send Matrices
        glUniformMatrix4fv(UNILOC_MODEL_MAT, 1, GL_FALSE,
                           glm::value_ptr(t));
        glUniformMatrix4fv(UNILOC_VIEW_MAT, 1, GL_FALSE,
                           glm::value_ptr(camMat));
        glUniformMatrix4fv(UNILOC_PROJECTION_MAT, 1, GL_FALSE,
                           glm::value_ptr(camera->projectionMatrix()));

        // Render Mesh
        _mesh->bind();

        // Skybox should have indices
        glDepthMask(GL_FALSE);
        glDrawElements(GL_TRIANGLES, _mesh->getNrIndices(), GL_UNSIGNED_INT, 0);
        glDepthMask(GL_TRUE);
    }

    void attach() override {
        _material = _parent->getComponent<Material>();
        if (_mesh == nullptr) {
            std::cerr << "Must attach Material component before adding SkyboxRenderer!" << std::endl;
            throw -1;
        }

        if (!dynamic_cast<Cubemap*>(_material->TEXTURE)) {
            std::cerr << "Attached material must contain a cube map!" << std::endl;
            throw -1;
        }
    }

    void detach() override {
        _material = nullptr;
        _mesh = nullptr;
    }

   private:
    Transform _viewTransform;
    ShaderProgram* const _SHADER_PROGRAM;
    Material* _material;
    ::Mesh* _mesh;
};
}  // namespace COMP