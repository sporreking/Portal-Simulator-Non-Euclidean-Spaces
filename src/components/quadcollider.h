#pragma once

#include "../component.h"
#include "../room.h"
#include "../time.h"

namespace COMP {

class QuadCollider;

// Collision handling function format.
// Arguments: <collider entity> <target entity> <old target position> <collision point>
typedef void (*QuadCollisionFunc)(COMP::QuadCollider *, Entity *, glm::vec3 const &, glm::vec3 const &);

class QuadCollider : public Component {
   public:
    QuadCollider(std::string targetName, QuadCollisionFunc handler)
        : _targetName{targetName}, _handler{handler} {}

    void render(glm::mat4 const &m, COMP::Camera *c = nullptr) override {}
    void enterRoom(Room *newRoom) override {}
    void exitRoom(Room *oldRoom) override {}
    void attach() override {}
    void detach() override {}

    void update(double const &dt) override {
        // Get current time to check if previous target position is obsolete
        double now = Time::current();

        // Retrieve target if non-existant or obsolete
        if (!_target || _targetPrevPosStamp < now - dt) {
            Entity *target = _parent->getRoom()->getEntity(_targetName);

            // If target was just found, skip first frame
            // to attain valid previous position
            if (target) {
                _targetPrevPos = target->getTransform()->pos;
                _target = target;
                _targetPrevPosStamp = now;
            }

            return;
        }

        _targetPrevPosStamp = now;

        // Player position
        glm::vec3 pos = _target->getTransform()->pos;

        // Transform old and new position to the quad's model-space
        glm::mat4 m = glm::inverse(_parent->getGlobalTransformMatrix());
        glm::vec3 newPos = glm::vec3(m * glm::vec4(pos, 1));
        glm::vec3 prevPos = glm::vec3(m * glm::vec4(_targetPrevPos, 1));

        // Check if we have transitioned through quad plane
        if (prevPos.z * newPos.z < 0) {
            // Collision point in model-space
            float zDist = std::abs(prevPos.z) + std::abs(newPos.z);
            glm::vec3 p = prevPos + (std::abs(prevPos.z) / zDist) * (newPos - prevPos);

            // Check if within quad bounds
            if (p.x > -.5 && p.x < .5 && p.y > -.5 && p.y < .5) {
                // Collision
                glm::vec3 colPoint = glm::vec3(_parent->getGlobalTransformMatrix() * glm::vec4(p, 1));
                _handler(this, _target, _targetPrevPos, colPoint);
            }
        }

        // Update previous position
        _targetPrevPos = pos;
    }

    // Issues a re-fetch of the target, skipping collisions for a frame.
    // Instead, the collider updates its conception of the previous target position.
    inline void resetTarget() { _target = nullptr; }

   private:
    std::string _targetName;
    Entity *_target{nullptr};
    glm::vec3 _targetPrevPos{0};
    double _targetPrevPosStamp{0};
    QuadCollisionFunc _handler;
};
}  // namespace COMP