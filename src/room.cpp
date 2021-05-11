#include "room.h"

void Room::update(double const& dt) {
    for (auto&& e : _priorities)
        e.second->update(dt);
}

void Room::render(glm::mat4 const& m, COMP::Camera* c) {
    for (auto&& e : _priorities)
        e.second->render(m, c);
}

Room* Room::addEntity(std::string const& tag, Entity* e, Priority p) {
    if (_entities.count(tag)) {
        std::cerr << "There is already an entity with tag \"" << tag << "\"" << std::endl;
        throw -1;
    }

    if (e->getRoom() != nullptr) {
        std::cerr << "The entity is already in another room" << std::endl;
        throw -1;
    }

    _entities.emplace(tag, (EntityRef){p, e});
    _priorities.emplace(p, e);
    e->_enterRoom(this);

    return this;
}

Room* Room::addEntities(std::map<std::string, Entity*> const& m, Priority p) {
    for (auto&& e : m)
        addEntity(e.first, e.second, p);
    return this;
}

Entity* Room::transferEntity(std::string const& tag, Room* target, std::string const& newTag) {
    if (!hasEntity(tag) || target->hasEntity(tag)) {
        std::cerr << "Could not transfer entity with tag \"" << tag << "\"" << std::endl;
        throw -1;
    }

    EntityRef ref = removeEntity(tag);
    target->addEntity(newTag.empty() ? tag : newTag, ref.entity, ref.priority);

    return ref.entity;
}

Entity* Room::retrieveEntity(std::string const& tag, Room* from, std::string const& newTag) {
    if (hasEntity(tag) || !from->hasEntity(tag)) {
        std::cerr << "Could not retrieve entity with tag \"" << tag << "\"" << std::endl;
        throw -1;
    }

    EntityRef ref = from->removeEntity(tag);
    addEntity(newTag.empty() ? tag : newTag, ref.entity, ref.priority);

    return ref.entity;
}

EntityRef Room::removeEntity(std::string const& tag) {
    EntityRef& ref = _entities.at(tag);
    ref.entity->_exitRoom(this);
    _entities.erase(tag);

    // Remove from priorities
    auto itpair = _priorities.equal_range(ref.priority);
    auto it = itpair.first;
    for (; it != itpair.second; it++)
        if (it->second == ref.entity) {
            _priorities.erase(it);
            break;
        }

    return ref;
}

std::string Room::getTag(Entity* e) {
    auto it = std::find_if(_entities.begin(), _entities.end(), [e](auto&& p) {
        return p.second.entity == e;
    });

    if (it == _entities.end()) {
        std::cerr << "The specified entity does not exist in this room" << std::endl;
        throw -1;
    }

    return it->first;
}

void Room::_appendCamera(COMP::Camera* c) {
    _cameras.push_back(c);
}

void Room::_removeCamera(COMP::Camera* c) {
    _cameras.erase(std::remove(_cameras.begin(), _cameras.end(), c), _cameras.end());
}

void Room::_appendLight(Component* c) {
    _lights.push_back(c);
}

void Room::_removeLight(Component* c) {
    _lights.erase(std::remove(_lights.begin(), _lights.end(), c), _lights.end());
}

Room::~Room() {
    for (auto&& e : _priorities)
        e.second->_exitRoom(this);

    for (auto&& e : _priorities)
        delete e.second;

    _priorities.clear();
    _entities.clear();
}