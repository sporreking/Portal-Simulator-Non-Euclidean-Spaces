#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "../entity.h"

namespace COMP {
class Camera : public Component {
   public:
    void update(double const& dt) override {}
    void render(glm::mat4 const& m, COMP::Camera* c = nullptr) override {}
    void attach() override {}
    void detach() override {}

    void enterRoom(Room* newRoom) override {
        newRoom->_appendCamera(this);
    }

    void exitRoom(Room* oldRoom) override {
        oldRoom->_removeCamera(this);
    }

    Camera* setPerspective(double const& fov, double const& aspectRatio,
                           double const& near, double const& far) {
        _projection = glm::perspective(fov, aspectRatio, near, far);
        return this;
    }

    glm::mat4 viewMatrix() {
        Transform* t = _parent->getTransform();
        glm::mat4 m = glm::scale(glm::mat4(1.0), t->scale);
        m = glm::rotate(m, -t->rot.z, glm::vec3(0, 0, 1));
        m = glm::rotate(m, -t->rot.x, glm::vec3(1, 0, 0));
        m = glm::rotate(m, -t->rot.y, glm::vec3(0, 1, 0));
        return glm::translate(m, -t->pos);
    }

    inline glm::mat4 projectionMatrix() { return _projection; }

   private:
    glm::mat4 _projection{1.0};
};
}  // namespace COMP