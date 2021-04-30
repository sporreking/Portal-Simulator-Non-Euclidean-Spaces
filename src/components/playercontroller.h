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
            // Movement
            double forward = Input::axis(AXIS_FORWARD);
            double strafe = Input::axis(AXIS_STRAFE);
            double ascend = Input::axis(AXIS_ASCEND);

            Transform *t = _parent->getTransform();

            double dz = -forward * std::cos(t->rot.y) + strafe * std::sin(-t->rot.y);
            double dx = forward * std::sin(-t->rot.y) + strafe * std::cos(t->rot.y);

            t->pos.z += dz * speed * dt;
            t->pos.x += dx * speed * dt;
            t->pos.y += ascend * speed * dt;

            // Camera
            t->rot.y -= Input::axis(AXIS_LOOK_HORIZONTAL);
            t->rot.x -= Input::axis(AXIS_LOOK_VERTICAL);

        } else {
            //TODO::Fix
        }
    }
    void render(glm::mat4 const &m) override {}
    void enterRoom(Room *newRoom) override {}
    void exitRoom(Room *oldRoom) override {}
    void attach() override {}
    void detach() override {}

    bool noclip{false};
    double speed{1.0};

   private:
};
}  // namespace COMP