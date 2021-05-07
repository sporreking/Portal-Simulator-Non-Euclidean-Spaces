#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "../component.h"
#include "../registries.h"
#include "../room.h"
#include "material.h"
#include "mesh.h"

namespace COMP {
class PhongRenderer : public Component {
   public:
    PhongRenderer()
        : _SHADER_PROGRAM{REG::SHADER_PROGRAMS().get(SHADER_PROGRAM_PHONG)} {}

    void update(double const& dt) override {}
    void enterRoom(Room* newRoom) override {}
    void exitRoom(Room* oldRoom) override {}

    void render(glm::mat4 const& m) override {
        // Get cameras
        std::vector<COMP::Camera*> cameras = _parent->getRoom()->getCameras();

        // Skip render pass if there are no cameras
        if (cameras.empty())
            return;

        // Send Lights
        _SHADER_PROGRAM->bind();
        _SHADER_PROGRAM->sendLights(_parent->getRoom()->getLights());

        // Send Material
        _SHADER_PROGRAM->sendMaterial(_material);
        _material->TEXTURE->bind();

        // Send Matrices
        glm::mat4 modelMat = _parent->getGlobalTransformMatrix();
        glUniformMatrix4fv(UNILOC_MODEL_MAT, 1, GL_FALSE,
                           glm::value_ptr(modelMat));

        glUniformMatrix4fv(UNILOC_VIEW_MAT, 1, GL_FALSE,
                           glm::value_ptr(cameras[0]->viewMatrix()));

        glUniformMatrix4fv(UNILOC_PROJECTION_MAT, 1, GL_FALSE,
                           glm::value_ptr(cameras[0]->projectionMatrix()));

        // Render Mesh
        _mesh->MESH->bind();

        if (_mesh->MESH->getNrIndices()) {
            glDrawElements(GL_TRIANGLES, _mesh->MESH->getNrIndices(), GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, _mesh->MESH->getNrVertices());
        }
    }

    void attach() override {
        _material = _parent->getComponent<Material>();
        _mesh = _parent->getComponent<Mesh>();
        if (_material == nullptr || _mesh == nullptr) {
            std::cerr << "Must attach Material and Mesh component before adding PhongRenderer!" << std::endl;
            throw -1;
        }
    }

    void detach() override {
        _material = nullptr;
        _mesh = nullptr;
    }

   private:
    ShaderProgram* const _SHADER_PROGRAM;
    Material* _material;
    Mesh* _mesh;
};
}  // namespace COMP
