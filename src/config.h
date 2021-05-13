#pragma once

#include "color.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Non-Euclidean Spaces: Portal Simulator"
#define BACKGROUND_COLOR \
    { .0, .7, 1.0 }

#define FOV 70
#define ASPECT_RATIO ((double)WINDOW_WIDTH / WINDOW_HEIGHT)
#define NEAR_PLANE 0.01
#define FAR_PLANE 100

#define LINK_MAX_RECURSION_DEPTH 2
#define LINK_MAX_RECURSION_DEPTH_COLOR COLOR_PURPLE

#define NR_FRAME_BUFFERS LINK_MAX_RECURSION_DEPTH