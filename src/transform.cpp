#include "transform.h"

glm::mat4 Transform::matrix() {
    glm::mat4 m = glm::translate(glm::mat4(1.0), pos);
    m = glm::rotate(m, rot.y, glm::vec3(0, 1, 0));
    m = glm::rotate(m, rot.x, glm::vec3(1, 0, 0));
    m = glm::rotate(m, rot.z, glm::vec3(0, 0, 1));
    return glm::scale(m, scale);
}
