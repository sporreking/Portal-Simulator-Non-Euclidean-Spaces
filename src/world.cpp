#include "world.h"

#include "prototypes.h"

World::World(std::string const& name, std::vector<Room*> rooms,
             RoomID startingRoom, Transform const& startingTransform)
    : NAME{name}, _startingRoom{startingRoom}, _startingTransform{startingTransform} {
    for (Room* r : rooms) {
        r->_setWorld(this);
        _rooms.emplace(r->getID(), r);
    }

    _player = PROT::newPlayer(1.0, true);
    changeRoom(startingRoom, startingTransform);
}

World::~World() {
    for (auto&& r : _rooms)
        delete r.second;
    _rooms.clear();
}

void World::update(double const& dt) {
    _changeRoom();

    _current->update(dt);
}

void World::render() {
    // Skip render pass if room was changed in update
    if (_changeRoom()) return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _current->render(glm::mat4(1.0));
}

void World::changeRoom(RoomID newRoom, Transform const& newTransform) {
    _shouldChangeRoom = true;
    _newRoom = newRoom;
    _newTransform = newTransform;
}

bool World::_changeRoom() {
    // Change room if applicable
    if (_shouldChangeRoom) {
        _shouldChangeRoom = false;

        if (_current)
            _current->transferEntity(TAG_PLAYER, getRoom(_newRoom));
        else
            getRoom(_newRoom)->addEntity(TAG_PLAYER, _player);

        _setCurrentRoom(_newRoom);
        *_player->getTransform() = _newTransform;

        return true;
    }

    return false;
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