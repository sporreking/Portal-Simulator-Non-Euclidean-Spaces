#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../color.h"
#include "../component.h"
#include "../framebuffer.h"
#include "../registries.h"
#include "../world.h"
#include "camera.h"
#include "playercontroller.h"

namespace COMP {
class LinkRenderer : public Component {
   public:
    LinkRenderer() : _SHADER_PROGRAM{REG::SHADER_PROGRAMS().get(SHADER_PROGRAM_LINK)},
                     _mesh{REG::MESHES().get(MESH_QUAD)} {}

    void update(double const& dt) override {}
    void enterRoom(Room* newRoom) override {}
    void exitRoom(Room* oldRoom) override {}
    void attach() override {}
    void detach() override {}

    void render(glm::mat4 const& m, COMP::Camera* c = nullptr) override {
        // Check if entry link
        if (_isEntryLink) {
            _isEntryLink = false;
            return;
        }

        // Fetch camera
        COMP::Camera* camera = _getCamera(c);
        if (!camera) return;

        // Bind shader program
        _SHADER_PROGRAM->bind();

        // Render target room if applicable
        if (++LinkRenderer::_depthSignal > LINK_MAX_RECURSION_DEPTH) {
            // Render opaque color
            glUniform1i(UNILOC_USE_TEXTURE, GL_FALSE);
            glUniform3fv(UNILOC_MATERIAL_COLOR, 1, glm::value_ptr(LINK_MAX_RECURSION_DEPTH_COLOR));
        } else
            _renderTargetRoom(m, camera);

        // Restore recursion depth
        LinkRenderer::_depthSignal--;

        _renderMesh(m, camera);
    }

    inline void connect(LinkRenderer* target) { _target = target; }
    inline LinkRenderer* getTarget() { return _target; }

   private:
    ShaderProgram* const _SHADER_PROGRAM;
    LinkRenderer* _target;
    ::Mesh* _mesh;

    glm::vec3 _playerPrevPos{0};

    void _renderTargetRoom(glm::mat4 const& m, COMP::Camera* camera) {
        /* -- Render target room -- */
        _target->_isEntryLink = true;

        // Calculate tranformation from next room to current room coordinates
        glm::mat4 t{1.0};
        _linkTransitionTransform(&t);

        // Render minimum depth control texture for next room
        FrameBuffer* depthBuffer = FrameBuffer::getDepthBuffer(LinkRenderer::_depthSignal - 1)->bind();
        ShaderProgram::setWindowWidth(depthBuffer->getWidth());
        ShaderProgram::setWindowHeight(depthBuffer->getHeight());
        _SHADER_PROGRAM->bind();
        glUniform1i(UNILOC_USE_TEXTURE, GL_FALSE);
        glClear(GL_DEPTH_BUFFER_BIT);
        _renderMesh(m, camera);
        Texture* oldMinDepthTexture = ShaderProgram::setMinDepthTexture(depthBuffer->depthTexture());

        // Render next room
        FrameBuffer::getColorBuffer(LinkRenderer::_depthSignal - 1)->bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _target->getParent()->getRoom()->render(t * m, camera);

        // Restore previous minimum depth control texture
        ShaderProgram::setMinDepthTexture(oldMinDepthTexture);

        // Bind previous frame buffer
        if (LinkRenderer::_depthSignal <= 1) {
            FrameBuffer::bindDefault();
            ShaderProgram::setWindowWidth(WINDOW_WIDTH);
            ShaderProgram::setWindowHeight(WINDOW_HEIGHT);
        } else {
            FrameBuffer* colorBuffer = FrameBuffer::getColorBuffer(LinkRenderer::_depthSignal - 2)->bind();
            ShaderProgram::setWindowWidth(colorBuffer->getWidth());
            ShaderProgram::setWindowHeight(colorBuffer->getHeight());
        }

        // Rebind shader program
        _SHADER_PROGRAM->bind();

        // Bind target room texture
        FrameBuffer::getColorBuffer(LinkRenderer::_depthSignal - 1)->texture()->bind();

        glUniform1i(UNILOC_USE_TEXTURE, GL_TRUE);
        glUniform3fv(UNILOC_MATERIAL_COLOR, 1, glm::value_ptr(COLOR_WHITE));
        glUniform1i(UNILOC_MATERIAL_SAMPLER, 0);
    }

    void _renderMesh(glm::mat4 const& m, COMP::Camera* camera) {
        // Send Matrices
        glm::mat4 modelMat = m * _parent->getGlobalTransformMatrix();

        glUniformMatrix4fv(UNILOC_MODEL_MAT, 1, GL_FALSE,
                           glm::value_ptr(modelMat));

        glUniformMatrix4fv(UNILOC_VIEW_MAT, 1, GL_FALSE,
                           glm::value_ptr(camera->viewMatrix()));

        glUniformMatrix4fv(UNILOC_PROJECTION_MAT, 1, GL_FALSE,
                           glm::value_ptr(camera->projectionMatrix()));

        // Render Mesh
        _mesh->bind();

        glDrawElements(GL_TRIANGLES, _mesh->getNrIndices(), GL_UNSIGNED_INT, 0);
    }

    /* -- Recursion -- */

    void _linkTransitionTransform(glm::mat4* res) {
        // Position target link at source link
        *res = glm::translate(*res, _parent->getTransform()->pos);

        // Rotate target to match source link
        glm::quat rot = glm::inverse(_target->getParent()->getTransform()->rot) * _parent->getTransform()->rot;
        *res *= glm::toMat4(rot);

        // Centralize target room around target
        *res = glm::translate(*res, -_target->getParent()->getTransform()->pos);
    }

    // Global signal for recursion depth
    inline static uint32_t _depthSignal{0};
    bool _isEntryLink{false};
};
}  // namespace COMP
