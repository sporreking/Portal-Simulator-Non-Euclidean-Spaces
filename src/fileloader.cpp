#include "fileloader.h"

std::string FileLoader::loadText(std::string path) {
    std::ifstream stream(path);
    std::string str;

    if (!stream) {
        std::cout << "Could not open file: \"" << path << "\"" << std::endl;
        throw -1;
    }

    stream.seekg(0, std::ios::end);
    str.reserve(stream.tellg());
    stream.seekg(0, std::ios::beg);

    str.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());

    return str;
}