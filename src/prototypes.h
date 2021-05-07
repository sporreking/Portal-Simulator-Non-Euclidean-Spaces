
#pragma once

#include "components/camera.h"
#include "components/material.h"
#include "components/mesh.h"
#include "components/phongrenderer.h"
#include "entity.h"

namespace PROT {
Entity* newPlayer(double const& speed = 1.0, bool noclip = false);
Entity* newWall(glm::vec3 const& pos, glm::vec3 const& rot,
                double const& width, double const& height,
                glm::vec3 const& color = glm::vec3(1, 1, 1), double const& thickness = 0.05);
}  // namespace PROT