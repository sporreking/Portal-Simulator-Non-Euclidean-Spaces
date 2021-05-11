#include "component.h"

#include "entity.h"

COMP::Camera* Component::_getCamera(COMP::Camera* c) {
    if (c)
        return c;
    else {
        // Get cameras from room
        std::vector<COMP::Camera*> cameras = _parent->getRoom()->getCameras();

        // Check if there are no cameras
        if (cameras.empty())
            return nullptr;

        return cameras[0];
    }
}
