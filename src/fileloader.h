#pragma once

#include <fstream>
#include <iostream>

class FileLoader {
   public:
    // Load ascii text from file
    static std::string loadText(std::string const& path);

    // Load texture from file
    static unsigned char* loadTexture(std::string const& path, uint32_t* width, uint32_t* height, uint32_t* nrChannels);
};