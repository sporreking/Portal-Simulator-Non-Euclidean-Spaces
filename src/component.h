#pragma once

#include <glm/mat4x4.hpp>
#include <iostream>
#include <vector>

class Entity;
class Room;
namespace COMP {
class Camera;
}

class Component {
   public:
    virtual ~Component() = default;

    virtual void update(double const& dt) = 0;
    virtual void render(glm::mat4 const& m, COMP::Camera* c = nullptr) = 0;
    virtual void enterRoom(Room* newRoom) = 0;
    virtual void exitRoom(Room* oldRoom) = 0;
    virtual void attach() = 0;
    virtual void detach() = 0;

    inline Entity* getParent() { return _parent; }

   protected:
    // Retrieves the first encountered camera in this component's room
    // if the given camera is nullptr. Otherwise the given camera itself is returned.
    // Returns nullptr if no cameras were found.
    COMP::Camera* _getCamera(COMP::Camera* c = nullptr);

    Entity* _parent{nullptr};
    friend class Entity;
};
