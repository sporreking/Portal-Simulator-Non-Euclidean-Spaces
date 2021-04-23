#pragma once

#include "../component.h"
#include "../entity.h"

namespace COMP {
class PointLight : public Component {
   public:
    PointLight(glm::vec3 const& color)
        : color{color} {}

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

    glm::vec3 color;
};
}  // namespace COMP