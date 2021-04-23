#pragma once

#include <glm/mat4x4.hpp>
#include <iostream>

class Entity;
class Room;

class Component {
   public:
    virtual ~Component() = default;

    virtual void update(double const& dt) = 0;
    virtual void render(glm::mat4 const& m) = 0;
    virtual void enterRoom(Room* newRoom) = 0;
    virtual void exitRoom(Room* oldRoom) = 0;
    virtual void attach() = 0;
    virtual void detach() = 0;

   protected:
    Entity* _parent{nullptr};
    friend class Entity;
};
