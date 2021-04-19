#pragma once

#include "../component.h"
#include "../mesh.h"

namespace COMP {
class Mesh : public Component {
   public:
    Mesh() = delete;
    Mesh(::Mesh* mesh) : MESH{mesh} {}

    void update(double const& dt) override {}
    void render(glm::mat4 const& m) override {}
    void attach() override {}
    void detach() override {}

    ::Mesh* const MESH;
};
}  // namespace COMP