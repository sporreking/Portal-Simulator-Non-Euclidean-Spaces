#pragma once

#include "../buttons.h"
#include "../component.h"
#include "../entity.h"

namespace COMP {
class PlayerController : public Component {
   public:
    PlayerController(double const &speed, bool noclip)
        : speed{speed}, noclip{noclip} {}

    void update(double const &dt) override {
        if (Input::pressed(BUTTON_TOGGLE_MOUSE)) {
            Input::grabMouse(!Input::mouseGrabbed());
        }

        if (noclip) {
            // Direction scalars
            float forward = Input::axis(AXIS_FORWARD) * dt;
            float strafe = Input::axis(AXIS_STRAFE) * dt;
            float ascend = Input::axis(AXIS_ASCEND) * dt;

            // Compute directions
            Transform *t = _parent->getTransform();
            glm::mat4 m = glm::rotate(glm::mat4(1.0), t->rot.y, glm::vec3(0, 1, 0));
            m = glm::rotate(m, t->rot.x, glm::vec3(1, 0, 0));
            m = glm::rotate(m, t->rot.z, glm::vec3(0, 0, 1));

            // Translate along scaled directions
            glm::vec3 diff = forward * glm::vec3(0, 0, -1) +
                             strafe * glm::vec3(1, 0, 0) +
                             ascend * glm::vec3(0, 1, 0);
            t->pos += glm::vec3(m * glm::vec4(diff, 1));

            // Camera
            t->rot.y -= Input::axis(AXIS_LOOK_HORIZONTAL) * dt;
            t->rot.x -= Input::axis(AXIS_LOOK_VERTICAL) * dt;

        } else {
            //TODO::Fix
        }
    }
    void render(glm::mat4 const &m, COMP::Camera *c = nullptr) override {}
    void enterRoom(Room *newRoom) override {}
    void exitRoom(Room *oldRoom) override {}
    void attach() override {}
    void detach() override {}

    bool noclip{false};
    double speed{1.0};

   private:
};
}  // namespace COMP