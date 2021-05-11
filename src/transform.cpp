#include "transform.h"

glm::mat4 Transform::matrix() {
    glm::mat4 m = glm::translate(glm::mat4(1.0), pos);
    m = m * glm::toMat4(rot);
    return glm::scale(m, scale);
}

Transform* Transform::setEulerRot(glm::vec3 const& radians) {
    rot = glm::quat(radians);
    return this;
}

glm::vec3 Transform::getEulerRot() {
    return glm::eulerAngles(rot);
}