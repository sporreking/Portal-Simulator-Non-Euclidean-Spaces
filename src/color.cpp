#include "color.h"

namespace COLOR {
glm::vec3 getColor(std::string const& name, double const& saturation) {
    if (name == COLOR_NAME_RED)
        return COLOR_RED + (1.0f - (float)saturation) * COLOR_CYAN;
    else if (name == COLOR_NAME_GREEN)
        return COLOR_GREEN + (1.0f - (float)saturation) * COLOR_PURPLE;
    else if (name == COLOR_NAME_BLUE)
        return COLOR_BLUE + (1.0f - (float)saturation) * COLOR_YELLOW;
    else if (name == COLOR_NAME_YELLOW)
        return COLOR_YELLOW + (1.0f - (float)saturation) * COLOR_BLUE;
    else if (name == COLOR_NAME_PURPLE)
        return COLOR_PURPLE + (1.0f - (float)saturation) * COLOR_GREEN;
    else if (name == COLOR_NAME_CYAN)
        return COLOR_CYAN + (1.0f - (float)saturation) * COLOR_RED;
    else if (name == COLOR_NAME_WHITE)
        return COLOR_WHITE;
    else if (name == COLOR_NAME_BLACK)
        return COLOR_BLACK;
    else
        return glm::vec3(-1);
}
}  // namespace COLOR