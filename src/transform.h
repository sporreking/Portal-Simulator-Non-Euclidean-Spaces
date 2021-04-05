#pragma once

#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Transform {
   public:
    glm::mat4 matrix();

    /* -- Members -- */
    glm::vec3 pos{0.0};
    glm::vec3 rot{0.0};
    glm::vec3 scale{1.0};
};
