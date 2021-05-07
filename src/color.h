#pragma once

#include <glm/vec3.hpp>
#include <string>

#define COLOR_NAME_RED "red"
#define COLOR_RED glm::vec3(1, 0, 0)

#define COLOR_NAME_GREEN "green"
#define COLOR_GREEN glm::vec3(0, 1, 0)

#define COLOR_NAME_BLUE "blue"
#define COLOR_BLUE glm::vec3(0, 0, 1)

#define COLOR_NAME_YELLOW "yellow"
#define COLOR_YELLOW glm::vec3(1, 1, 0)

#define COLOR_NAME_PURPLE "purple"
#define COLOR_PURPLE glm::vec3(1, 0, 1)

#define COLOR_NAME_CYAN "cyan"
#define COLOR_CYAN glm::vec3(0, 1, 1)

#define COLOR_NAME_WHITE "white"
#define COLOR_WHITE glm::vec3(1)

#define COLOR_NAME_BLACK "black"
#define COLOR_BLACK glm::vec3(0)

namespace COLOR {
// Returns a color based on a name (or (-1, -1, -1) if there was no match)
glm::vec3 getColor(std::string const& name, double const& saturation = 1.0);
}  // namespace COLOR