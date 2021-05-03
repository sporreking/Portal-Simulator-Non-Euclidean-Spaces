#include "world.h"

World::World(std::string const& name, std::vector<Room*> rooms,
             RoomID startingRoom, glm::vec3 const& startingPos)
    : NAME{name}, _startingRoom{startingRoom}, _startingPos{startingPos} {
    for (Room* r : rooms)
        _rooms.emplace(r->getID(), r);

    _player = PROT::newPlayer(1.0, true);
    changeRoom(startingRoom, startingPos);
}

World::~World() {
    for (auto&& r : _rooms)
        delete r.second;
    _rooms.clear();
}

void World::update(double const& dt) {
    // Change room if applicable
    if (_shouldChangeRoom) {
        _shouldChangeRoom = false;

        if (_current)
            _current->transferEntity(TAG_PLAYER, getRoom(_newRoom));
        else
            getRoom(_newRoom)->addEntity(TAG_PLAYER, _player);

        _setCurrentRoom(_newRoom);
        _player->getTransform()->pos = _newPos;
    }

    _current->update(dt);
}

void World::render() {
    _current->render(glm::inverse(_player->getTransform()->matrix()));
}

void World::changeRoom(RoomID newRoom, glm::vec3 const& newPos) {
    _shouldChangeRoom = true;
    _newRoom = newRoom;
    _newPos = newPos;
}

Room* World::_setCurrentRoom(RoomID id) {
    if (!_rooms.count(id)) {
        std::cerr << "World has no room with id: " << id << std::endl;
        throw -1;
    }
    Room* old = _current;
    _current = _rooms.at(id);
    return old;
}