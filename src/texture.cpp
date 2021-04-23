#include "texture.h"

Texture::Texture() {
    // Generate texture
    glGenTextures(1, &_handle);
}

Texture::Texture(std::string const& path) : Texture() {
    _loadTexture(path);
}

Texture* Texture::bind(uint32_t t) {
    glActiveTexture(GL_TEXTURE0 + t);
    glBindTexture(GL_TEXTURE_2D, _handle);
    return this;
}

Texture* Texture::setMinMagFilter(GLenum val) {
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, val);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, val);
    return this;
}
Texture* Texture::setWrap(GLenum val) {
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, val);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, val);
    return this;
}

void Texture::_loadTexture(std::string const& path) {
    // Load texture data
    unsigned char* data = FileLoader::loadTexture(path, &_width, &_height, &_nrChannels);

    // Send to GPU
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

Texture::~Texture() {
    glDeleteTextures(1, &_handle);
}