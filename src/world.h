#pragma once

#include <map>

#include "room.h"

// Constants
#define TAG_LIGHTS "lights"
#define TAG_LINKS "links"
#define TAG_OBJECTS "objects"
#define TAG_PLAYER "player"
#define TAG_SKYBOX "skybox"
#define TAG_WALLS "walls"

class World {
   public:
    World(std::string const& name, std::vector<Room*> rooms,
          RoomID startingRoom, Transform const& startingTransform);

    ~World();
    /* -- Core -- */

    void update(double const& dt);
    void render();

    void changeRoom(RoomID newRoom, Transform const& newTransform);

    /* -- Getters -- */

    inline Room* getCurrentRoom() { return _current; }
    inline Room* getRoom(RoomID id) { return _rooms.count(id) ? _rooms.at(id) : nullptr; }
    inline size_t nrRooms() { return _rooms.size(); }
    inline Entity* getPlayer() { return _player; }

    inline RoomID getStartingRoom() { return _startingRoom; }
    inline Transform getStartingTransform() { return _startingTransform; }

    std::string const NAME;

   private:
    /* -- Members -- */

    std::map<RoomID, Room*> _rooms;
    Room* _current{nullptr};
    Entity* _player{nullptr};
    RoomID _startingRoom;
    Transform _startingTransform;

    bool _shouldChangeRoom{false};
    RoomID _newRoom;
    Transform _newTransform;

    /* -- Functions -- */

    // Sets the current room, and returns the previous.
    Room* _setCurrentRoom(RoomID id);
};