#include "prototypes.h"

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

Entity* newSkybox(unsigned int id) {
    if (id < 0 || id >= NR_SKYBOXES)
        throw std::invalid_argument(std::string("Skybox ID must be in range {0 ... ") +
                                    std::to_string(NR_SKYBOXES - 1) + "}");

    Entity* skybox = new Entity;
    skybox->addComponent(new COMP::Material(REG::TEXTURES().get(
        std::string(CUBEMAP_SKY) + std::to_string(id))));
    skybox->addComponent(new COMP::SkyboxRenderer());
    return skybox;
}

Entity* newLink(glm::vec3 const& pos, glm::vec3 const& rot,
                double const& width, double const& height, FrameBuffer* frameBuffer) {
    Entity* link = new Entity;

    // Add link
    link->addComponent(new COMP::LinkRenderer(frameBuffer));
    link->getTransform()->pos = pos;
    link->getTransform()->rot = rot;
    link->getTransform()->scale = {width, height, 1};

    return link;
}
}  // namespace PROT