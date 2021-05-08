#include "fileloader.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::string FileLoader::loadText(std::string const& path) {
    std::ifstream stream(path);
    std::string str;

    if (!stream) {
        std::cerr << "Could not open file: \"" << path << "\"" << std::endl;
        throw -1;
    }

    stream.seekg(0, std::ios::end);
    str.reserve(stream.tellg());
    stream.seekg(0, std::ios::beg);

    str.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());

    return str;
}

unsigned char* FileLoader::loadTexture(std::string const& path, uint32_t* width,
                                       uint32_t* height, uint32_t* nrChannels) {
    return stbi_load(path.c_str(), (int*)width, (int*)height, (int*)nrChannels, 4);
}

void FileLoader::freeTextureData(unsigned char* data) {
    stbi_image_free(data);
}