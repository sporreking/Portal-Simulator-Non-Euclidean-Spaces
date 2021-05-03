#pragma once

#include <map>

#include "prototypes.h"
#include "room.h"

// Constants
#define TAG_PLAYER "player"

class World {
   public:
    World(std::string const& name, std::vector<Room*> rooms,
          RoomID startingRoom, glm::vec3 const& startingPos);

    ~World();
    /* -- Core -- */

    void update(double const& dt);
    void render();

    void changeRoom(RoomID newRoom, glm::vec3 const& newPos);

    /* -- Getters -- */

    inline Room* getCurrentRoom() { return _current; }
    inline Room* getRoom(RoomID id) { return _rooms.count(id) ? _rooms.at(id) : nullptr; }
    inline size_t nrRooms() { return _rooms.size(); }
    inline Entity* getPlayer() { return _player; }

    inline RoomID getStartingRoom() { return _startingRoom; }
    inline glm::vec3 getStartingPos() { return _startingPos; }

    std::string const NAME;

   private:
    /* -- Members -- */

    std::map<RoomID, Room*> _rooms;
    Room* _current{nullptr};
    Entity* _player{nullptr};
    RoomID _startingRoom;
    glm::vec3 _startingPos;

    bool _shouldChangeRoom{false};
    RoomID _newRoom;
    glm::vec3 _newPos;

    /* -- Functions -- */

    // Sets the current room, and returns the previous.
    Room* _setCurrentRoom(RoomID id);
};