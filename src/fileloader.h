#pragma once

#include <fstream>
#include <iostream>

class FileLoader {
   public:
    // Load ascii text from file
    static std::string loadText(std::string const& path);
};