#pragma once

#include <map>
#include <string>

#include "entity.h"

// Light forward declarations
namespace COMP {
class PointLight;
}

typedef size_t RoomID;

class Room {
   public:
    Room() = delete;
    Room(RoomID id) : _id{id} {};
    ~Room();

    void update(double const& dt);
    void render(glm::mat4 const& m);

    Room* addEntity(std::string const& tag, Entity* e);
    Room* addEntities(std::map<std::string, Entity*> const& m);

    Entity* transferEntity(std::string const& tag, Room* target, std::string const& newTag = "");
    Entity* retrieveEntity(std::string const& tag, Room* from, std::string const& newTag = "");

    // Make sure to delete the entity if it is no longer needed
    Entity* removeEntity(std::string const& tag);

    inline RoomID getID() { return _id; }

    std::string getTag(Entity* e);
    inline bool hasEntity(std::string const& tag) { return _entities.count(tag); }
    inline Entity* getEntity(std::string const& tag) { return _entities.at(tag); }
    inline std::map<std::string, Entity*> getEntities() { return _entities; }
    inline std::vector<Component*> getLights() { return _lights; }

   private:
    RoomID _id;
    std::map<std::string, Entity*> _entities;
    std::vector<Component*> _lights;

    // Appends a light to this room (only call with light components)
    void _appendLight(Component* c);
    void _removeLight(Component* c);

    // Light friends
    friend class COMP::PointLight;
};