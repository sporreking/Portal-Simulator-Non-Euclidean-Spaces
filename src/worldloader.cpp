#include "worldloader.h"

/* -- Argument Class -- */

double Argument::asDouble() const {
    try {
        return std::stod(_RAW);
    } catch (std::invalid_argument const& e) {
        throw std::invalid_argument(std::string("Invalid double: ") + _RAW);
    }
}

int Argument::asInt() const {
    try {
        return std::stoi(_RAW);
    } catch (std::invalid_argument const& e) {
        throw std::invalid_argument(std::string("Invalid integer: ") + _RAW);
    }
}

bool Argument::asBool() const {
    std::string data{asString(true)};

    if (data == "true" || data == "1")
        return true;
    else if (data == "false" || data == "0")
        return false;
    else
        throw std::invalid_argument(std::string("Invalid boolean: ") + _RAW);
}

std::string Argument::asString(bool lower) const {
    std::string data{_RAW};
    if (lower)
        std::transform(data.begin(), data.end(), data.begin(),
                       [](unsigned char c) { return std::tolower(c); });
    return data;
}

glm::vec3 Argument::asColor(double const& saturation) const {
    glm::vec3 color = COLOR::getColor(asString(true), saturation);
    return color.x < 0 ? asVec3() : color;
}

glm::vec2 Argument::asVec2() const {
    glm::vec2 v;
    _fillVec(2, glm::value_ptr(v));
    return v;
}

glm::vec3 Argument::asVec3() const {
    glm::vec3 v;
    _fillVec(3, glm::value_ptr(v));
    return v;
}

glm::vec4 Argument::asVec4() const {
    glm::vec4 v;
    _fillVec(4, glm::value_ptr(v));
    return v;
}

glm::quat Argument::asQuatFromEuler() const {
    return glm::quat(asVec3() / (180 / (float)M_PI));
}

void Argument::_fillVec(size_t n, float* ptr) const {
    std::string str{_RAW};
    size_t pos{0};
    std::string token;

    size_t i{0};
    do {
        pos = str.find(',');
        token = str.substr(0, pos);
        str.erase(0, pos + 1);
        if (i >= n) throw std::invalid_argument(std::string("Too many scalars in vec") +
                                                std::to_string(n) + std::string(": ") + _RAW);
        ptr[i++] = std::stod(token);
    } while (pos != std::string::npos);

    if (i < n) throw std::invalid_argument(std::string("Too few scalars in vec") +
                                           std::to_string(n) + std::string(": ") + _RAW);
}

/* -- WorldLoader Class -- */

#include "worldcommands.hcc"

World* WorldLoader::load(std::string const& filePath) {
    std::ifstream stream(filePath);

    size_t pos{0};
    std::string cmd;
    std::string key;
    std::vector<Argument> args;
    WorldContext context;
    size_t line{0};
    while (!stream.eof()) {
        std::getline(stream, cmd);
        line++;

        key.clear();
        args.clear();
        do {
            // Retrieve argument
            pos = cmd.find(' ');
            std::string arg = cmd.substr(0, pos);
            cmd.erase(0, pos + 1);

            // Check if empty
            if (arg.empty()) continue;

            // Check if comment
            if (arg[0] == '#') break;

            if (key.empty())
                key = arg;  // interpret first argument as key
            else
                args.push_back(Argument(arg));  // Add argument
        } while (pos != std::string::npos);

        // Check if line was empty
        if (key.empty()) continue;

        // Retrieve command function and number of arguments
        std::pair<CommandFunc, size_t> func;
        try {
            func = _commands.at(key);
        } catch (std::out_of_range const& e) {
            std::cerr << "ERROR in " << filePath << "(" << line << ")"
                      << ": Unrecognized command \"" << key << "\"" << std::endl;
            exit(-1);
        }

        // Check number of arguments
        if (func.second > args.size()) {
            std::cerr << "ERROR in " << filePath << "(" << line << ")"
                      << ": Invalid number of arguments (expected a minimum of "
                      << func.second << " but got " << args.size() << ")." << std::endl;
            exit(-1);
        }

        // Evoke command function
        try {
            func.first(&context, args);
        } catch (std::domain_error const& e) {
            std::cerr << "ERROR in " << filePath << "(" << line << ")"
                      << ": Internal state error: " << e.what() << std::endl;
            exit(-1);
        } catch (std::invalid_argument const& e) {
            std::cerr << "ERROR in " << filePath << "(" << line << ")"
                      << ": " << e.what() << std::endl;
            exit(-1);
        }
    }

    // Create world from context
    Transform pt;
    pt.pos = context.player.pos;
    pt.rot = context.player.rot;
    World* world = new World(context.name, context.rooms, context.player.room, pt);
    COMP::PlayerController* ctrl = world->getPlayer()->getComponent<COMP::PlayerController>();
    ctrl->speed = context.player.speed;
    ctrl->noclip = context.player.noclip;

    // Connect links
    for (auto&& l : context.links) {
        // Get link component from link entity in our room
        COMP::LinkRenderer* link = l.first->getComponent<COMP::LinkRenderer>();
        LinkConnection& ref = l.second;

        Room* targetRoom = world->getRoom(ref.targetRoom);

        // Check link validity
        if (!targetRoom || targetRoom->getEntity(TAG_LINKS)->nrChildren() <= ref.targetID) {
            std::cerr << "Invalid link: room ID: " << ref.targetRoom << ", link ID: " << ref.targetID << std::endl;
            throw -1;
        }
        // Connect our link to target link
        link->connect(targetRoom->getEntity(TAG_LINKS)
                          ->getChild(ref.targetID)
                          ->getComponent<COMP::LinkRenderer>());
    }

    return world;
}

// Static instantiation
std::map<std::string, std::pair<CommandFunc, size_t>> WorldLoader::_commands;