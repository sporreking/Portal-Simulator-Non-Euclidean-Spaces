#include "prototypes.h"

namespace PROT {
Entity* newPlayer(double const& speed, bool noclip) {
    return (new Entity)->addComponents({new COMP::PlayerController(speed, noclip), (new COMP::Camera)->setPerspective(FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE)});
}

Entity* newWall(glm::vec3 const& pos, glm::quat const& rot,
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

void linkCollisionFunc(COMP::QuadCollider* col, Entity* player, glm::vec3 const& prevPos, glm::vec3 const& collisionPoint) {
    // Get link entity from collider
    Entity* link = col->getParent();

    // Get target link
    Entity* target = link->getComponent<COMP::LinkRenderer>()->getTarget()->getParent();

    // Player position in link model-space
    glm::vec3 playerPosLocal = glm::vec3(glm::inverse(link->getGlobalTransformMatrix()) *
                                         glm::vec4(player->getTransform()->pos, 1));

    // Player position in target room's world-space
    glm::vec3 nextPos = glm::vec3(target->getGlobalTransformMatrix() * glm::vec4(playerPosLocal, 1));

    // Calculate link orientation difference
    glm::quat rotDiff = target->getTransform()->rot * glm::inverse(link->getTransform()->rot);

    // Create new transform for target room endpoint
    Transform nt;
    nt.pos = nextPos;
    nt.rot = rotDiff * player->getTransform()->rot;

    // Change room
    player->getRoom()->getWorld()->changeRoom(target->getRoom()->getID(), nt);
}

Entity* newLink(glm::vec3 const& pos, glm::quat const& rot,
                double const& width, double const& height) {
    Entity* link = new Entity;

    // Add link
    link->addComponent(new COMP::LinkRenderer());
    link->addComponent(new COMP::QuadCollider(TAG_PLAYER, linkCollisionFunc));
    link->getTransform()->pos = pos;
    link->getTransform()->rot = rot;
    link->getTransform()->scale = {width, height, 1};

    return link;
}
}  // namespace PROT