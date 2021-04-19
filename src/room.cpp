#include "room.h"

void Room::update(double const& dt) {
    for (auto&& e : _entities)
        e.second->update(dt);
}

void Room::render(glm::mat4 const& m) {
    for (auto&& e : _entities)
        e.second->render(m);
}

Room* Room::addEntity(std::string const& tag, Entity* e) {
    if (_entities.count(tag)) {
        std::cerr << "There is already an entity with tag \"" << tag << "\"" << std::endl;
        throw -1;
    }

    if (e->getRoom() != nullptr) {
        std::cerr << "The entity is already in another room" << std::endl;
        throw -1;
    }

    e->_room = this;
    _entities.emplace(tag, e);

    return this;
}

Room* Room::addEntities(std::map<std::string, Entity*> const& m) {
    for (auto&& e : m)
        addEntity(e.first, e.second);
    return this;
}

Entity* Room::transferEntity(std::string const& tag, Room* target, std::string const& newTag) {
    if (!hasEntity(tag) || target->hasEntity(tag)) {
        std::cerr << "Could not transfer entity with tag \"" << tag << "\"" << std::endl;
        throw -1;
    }

    Entity* e = removeEntity(tag);
    target->addEntity(newTag.empty() ? tag : newTag, e);

    return e;
}

Entity* Room::retrieveEntity(std::string const& tag, Room* from, std::string const& newTag) {
    if (hasEntity(tag) || !from->hasEntity(tag)) {
        std::cerr << "Could not retrieve entity with tag \"" << tag << "\"" << std::endl;
        throw -1;
    }

    Entity* e = from->removeEntity(tag);
    addEntity(newTag.empty() ? tag : newTag, e);

    return e;
}

Entity* Room::removeEntity(std::string const& tag) {
    Entity* e = _entities.at(tag);
    _entities.erase(tag);
    e->_room = nullptr;
    return e;
}

std::string Room::getTag(Entity* e) {
    auto it = std::find_if(_entities.begin(), _entities.end(), [e](auto&& p) {
        return p.second == e;
    });

    if (it == _entities.end()) {
        std::cerr << "The specified entity does not exist in this room" << std::endl;
        throw -1;
    }

    return it->first;
}

Room::~Room() {
    for (auto&& e : _entities)
        delete e.second;

    _entities.clear();
}