#include "cubemap.h"

Cubemap::Cubemap(std::string const& path, std::string const& fileType) : Texture() {
    _loadCubemap(path, fileType);
}

Texture* Cubemap::bind(uint32_t t) {
    glActiveTexture(GL_TEXTURE0 + t);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
    return this;
}

Texture* Cubemap::setMinMagFilter(GLenum val) {
    bind();
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, val);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, val);
    return this;
}

Texture* Cubemap::setWrap(GLenum val) {
    bind();
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, val);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, val);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, val);
    return this;
}

void Cubemap::_loadCubemap(std::string const& path, std::string const& fileType) {
    // File suffixes
    std::string suffixes[6] = {
        CUBEMAP_SUFFIX_FRONT,
        CUBEMAP_SUFFIX_BACK,
        CUBEMAP_SUFFIX_TOP,
        CUBEMAP_SUFFIX_BOTTOM,
        CUBEMAP_SUFFIX_RIGHT,
        CUBEMAP_SUFFIX_LEFT};

    bind();

    // Load texture data
    for (uint32_t i = 0; i < 6; i++) {
        std::string absPath = path + suffixes[i] + "." + fileType;

        unsigned char* data =
            FileLoader::loadTexture(absPath, &_width, &_height, &_nrChannels);

        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
                         _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            FileLoader::freeTextureData(data);
        } else {
            std::cerr << "Unable to locate texture: \"" << absPath << "\"" << std::endl;
            FileLoader::freeTextureData(data);
            throw -1;
        }
    }

    // Set properties
    setMinMagFilter(GL_LINEAR);
    setWrap(GL_CLAMP_TO_EDGE);
}