#include "prototypes.h"

#include "components/playercontroller.h"

namespace PROT {
Entity* newPlayer(double const& speed, bool noclip) {
    return (new Entity)->addComponents({new COMP::PlayerController(speed, noclip), (new COMP::Camera)->setPerspective(FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE)});
}

Entity* newWall(glm::vec3 const& pos, glm::vec3 const& rot,
                double const& width, double const& height,
                glm::vec3 const& color, double const& thickness) {
    Entity* e = (new Entity)->addComponents({new COMP::Mesh(REG::MESHES().get(MESH_CUBE)), new COMP::Material(REG::TEXTURES().get(TEXTURE_WALL), 1, 0, 0, color), new COMP::PhongRenderer()});
    e->getTransform()->pos = pos;
    e->getTransform()->rot = rot;
    e->getTransform()->scale = {width, height, thickness};

    return e;
}
}  // namespace PROT