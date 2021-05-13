#pragma once

#include <fstream>

#include "color.h"
#include "components/playercontroller.h"
#include "glm/gtc/type_ptr.hpp"
#include "prototypes.h"
#include "world.h"

// Every argument in a world file is parsed to this type
class Argument {
   public:
    Argument(std::string const& arg) : _RAW{arg} {}

    double asDouble() const;
    int asInt() const;
    bool asBool() const;
    std::string asString(bool lower = false) const;
    glm::vec3 asColor(double const& saturation = 1.0) const;

    glm::vec2 asVec2() const;
    glm::vec3 asVec3() const;
    glm::vec4 asVec4() const;

   private:
    std::string const _RAW;

    void _fillVec(size_t n, float* ptr) const;
};

// Link reference
struct LinkConnection {
    RoomID targetRoom;
    LinkID targetID;
};

// Configuration used to create a world
struct WorldContext {
    std::string name;
    struct {
        RoomID room;
        glm::vec3 pos;
        glm::vec3 rot;
        double speed;
        bool noclip;
    } player;
    Room* currentRoom{nullptr};
    std::vector<Room*> rooms;
    std::map<Entity*, LinkConnection> links;
};

// Command function (world file lines are parsed to this format)
typedef void (*CommandFunc)(WorldContext*, std::vector<Argument> const&);

class WorldLoader {
   public:
    static void init();
    static World* load(std::string const& filePath);

   private:
    // Map of command names to functions and their minimum required number of arguments
    static std::map<std::string, std::pair<CommandFunc, size_t>> _commands;
};