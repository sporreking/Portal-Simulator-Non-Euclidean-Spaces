#pragma once

#include <algorithm>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <map>
#include <type_traits>
#include <typeinfo>
#include <vector>

#include "component.h"
#include "room.h"
#include "transform.h"

// Forward declaration
class Room;

class Entity {
   public:
    /* -- Core -- */
    Entity(Entity* parent = nullptr);
    ~Entity();
    void update(double const& dt);
    void render(glm::mat4 const& m, COMP::Camera* c = nullptr);
    Entity* getParent();
    Entity* addChild(Entity* e);
    inline Entity* getChild(size_t id) { return _children.at(id); }
    inline std::vector<Entity*> getChildren() { return _children; }
    inline size_t nrChildren() { return _children.size(); }

    /* -- Components -- */
    Entity* addComponent(Component* comp);
    Entity* addComponents(std::vector<Component*> v);

    template <typename T>
    size_t nrComponents();

    template <typename T>
    T* getComponent();

    template <typename T>
    std::vector<T*> getComponents();

    /* -- Room -- */

    // Returns the room of this entity (or nullptr if there is no room)
    inline Room* getRoom() { return _room; }

    /* -- Transform -- */
    inline Transform* getTransform() { return &_transform; }
    inline glm::mat4 getLocalTransformMatrix() { return _transform.matrix(); }
    glm::mat4 getGlobalTransformMatrix();

   private:
    Room* _room{nullptr};
    std::vector<Entity*> _children;
    std::vector<Component*> _components;
    Entity* _parent{nullptr};
    Transform _transform;

    void _enterRoom(Room* room);
    void _exitRoom(Room* room);

    friend class Room;
};

#include "entity.tcc"
