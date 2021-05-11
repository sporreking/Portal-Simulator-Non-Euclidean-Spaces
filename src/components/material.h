#pragma once

#include <glm/vec3.hpp>

#include "../component.h"
#include "../texture.h"

namespace COMP {
class Material : public Component {
   public:
    Material() = delete;
    Material(Texture *tex) : Material(tex, 1.0, 0.0, 0.0) {}
    Material(Texture *tex, double kd, double ks, double alpha)
        : Material(tex, kd, ks, alpha, {1.0, 1.0, 1.0}) {}
    Material(Texture *tex, double kd, double ks, double alpha, glm::vec3 const &color)
        : TEXTURE{tex}, kd{kd}, ks{ks}, alpha{alpha}, color{color} {}

    void update(double const &dt) override {}
    void render(glm::mat4 const &m, COMP::Camera *c = nullptr) override {}
    void enterRoom(Room *newRoom) override {}
    void exitRoom(Room *oldRoom) override {}
    void attach() override {}
    void detach() override {}

    Texture *const TEXTURE;
    double kd{1.0};
    double ks{0.0};
    double alpha{0.0};
    glm::vec3 color;
};
}  // namespace COMP