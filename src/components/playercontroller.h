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

            // Translate along scaled directions
            Transform *t = _parent->getTransform();
            glm::vec3 diff = forward * glm::vec3(0, 0, -1) +
                             strafe * glm::vec3(1, 0, 0) +
                             ascend * glm::vec3(0, 1, 0);
            t->pos += glm::vec3(glm::toMat4(t->rot) * glm::vec4(diff, 1));

            // Rotate camera
            glm::vec3 euler = -glm::vec3(Input::axis(AXIS_LOOK_VERTICAL),
                                         Input::axis(AXIS_LOOK_HORIZONTAL),
                                         Input::axis(AXIS_ROTATE));
            glm::quat rotDiff = glm::quat(euler * ((float)dt));
            t->rot *= rotDiff;

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