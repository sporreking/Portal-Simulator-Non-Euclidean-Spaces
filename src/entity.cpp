#include "entity.h"

Entity::Entity(Entity* parent) {
    if (parent) {
        parent->addChild(this);
    }
}

Entity::~Entity() {
    if (_room != nullptr) {
        std::cerr << "Trying to delete an entity which belongs to a room!" << std::endl;
        exit(-1);
    }

    for (auto c : _components)
        c->detach();

    for (auto c : _components)
        delete c;
    _components.clear();

    for (auto e : _children)
        delete e;
    _children.clear();
}

void Entity::update(double const& dt) {
    for (auto&& c : _components)
        c->update(dt);

    for (auto&& e : _children)
        e->update(dt);
}

void Entity::render(glm::mat4 const& m) {
    for (auto&& c : _components)
        c->render(m * _transform.matrix());

    for (auto&& e : _children)
        e->render(m * _transform.matrix());
}

Entity* Entity::addChild(Entity* e) {
    if (e->_parent) {
        std::cerr << "Entity is already attached to a parent" << std::endl;
        throw -1;
    }
    _children.push_back(e);
    e->_parent = this;
    if (_room != nullptr)
        e->_enterRoom(_room);

    return this;
}

Entity* Entity::addComponent(Component* comp) {
    if (comp->_parent) {
        std::cerr << "Component is already attached to an Entity" << std::endl;
        throw -1;
    }
    _components.push_back(comp);
    comp->_parent = this;
    comp->attach();
    if (_room != nullptr)
        comp->enterRoom(_room);
    return this;
}

Entity* Entity::addComponents(std::vector<Component*> v) {
    for (auto&& c : v)
        this->addComponent(c);
    return this;
}

Entity* Entity::getParent() {
    return _parent;
}

glm::mat4 Entity::getGlobalTransformMatrix() {
    if (_parent)
        return _parent->getGlobalTransformMatrix() * _transform.matrix();
    return glm::mat4(1.0) * _transform.matrix();
}

void Entity::_enterRoom(Room* room) {
    _room = room;

    for (auto c : _components)
        c->enterRoom(room);

    for (auto e : _children)
        e->_enterRoom(room);
}

void Entity::_exitRoom(Room* room) {
    for (auto c : _components)
        c->exitRoom(room);

    for (auto e : _children)
        e->_exitRoom(room);

    _room = nullptr;
}