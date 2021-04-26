#pragma once

#include "../component.h"
#include "../entity.h"

namespace COMP {
class PointLight : public Component {
   public:
    PointLight(glm::vec3 const& color, double range = 5.0)
        : color{color}, range{range} {}

    void update(double const& dt) override {}
    void render(glm::mat4 const& m) override {}
    void attach() override {}
    void detach() override {}

    void enterRoom(Room* newRoom) override {
        newRoom->_appendLight(this);
    }

    void exitRoom(Room* oldRoom) override {
        oldRoom->_removeLight(this);
    }

    inline glm::vec3 position() {
        return glm::vec3(_parent->getGlobalTransformMatrix() * glm::vec4{0.0, 0.0, 0.0, 1.0});
    }

    glm::vec3 color;
    double range;
};
}  // namespace COMP