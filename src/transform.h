#pragma once

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Transform {
   public:
    glm::mat4 matrix();

    Transform* setEulerRot(glm::vec3 const& radians);
    glm::vec3 getEulerRot();

    /* -- Members -- */
    glm::vec3 pos{0.0};
    glm::quat rot{1.0, 0.0, 0.0, 0.0};
    glm::vec3 scale{1.0};
};
