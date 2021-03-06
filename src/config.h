#pragma once

#include "color.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "Non-Euclidean Spaces: Portal Simulator"
#define BACKGROUND_COLOR \
    { .0, .7, 1.0 }

#define FOV 70
#define ASPECT_RATIO ((double)WINDOW_WIDTH / WINDOW_HEIGHT)
#define NEAR_PLANE 0.01
#define FAR_PLANE 10000

#define LINK_MAX_RECURSION_DEPTH 5
#define LINK_MAX_RECURSION_DEPTH_COLOR COLOR_BLACK

// Number of static frame buffers
#define NR_COLOR_BUFFERS LINK_MAX_RECURSION_DEPTH
#define NR_DEPTH_BUFFERS LINK_MAX_RECURSION_DEPTH
#define FRAME_BUFFER_RESOLUTION_FALLOFF 1.0