#pragma once

#include <algorithm>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <map>
#include <type_traits>
#include <typeinfo>
#include <vector>

#include "component.h"
#include "transform.h"

class Entity {
   public:
    /* -- Core -- */
    Entity(Entity* parent = nullptr);
    ~Entity();
    void update(double const& dt);
    void render(glm::mat4 const& m);
    Entity* getParent();
    Entity* addChild(Entity* e);

    /* -- Components -- */
    Entity* addComponent(Component* comp);
    Entity* addComponents(std::vector<Component*> v);

    template <typename T>
    size_t numComponents();

    template <typename T>
    T* getComponent();

    template <typename T>
    std::vector<T*> getComponents();

    /* -- Room -- */
    //Room* getRoom();

    /* -- Transform -- */
    inline Transform* getTransform() { return &_transform; }
    inline glm::mat4 getLocalTransformMatrix() { return _transform.matrix(); }
    glm::mat4 getGlobalTransformMatrix();

   private:
    std::vector<Entity*> _children;
    std::vector<Component*> _components;
    Entity* _parent{nullptr};
    Transform _transform;
};

#include "entity.tcc"
