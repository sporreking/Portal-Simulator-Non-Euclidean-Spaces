#pragma once

#include <glad/glad.h>

#include <string>

#include "fileloader.h"

class Texture {
   public:
    Texture();
    Texture(std::string const& path);
    virtual ~Texture();

    // Binds this texture to the specified texture slot
    virtual Texture* bind(uint32_t t = 0);

    /* - Parameter Setters - */

    virtual Texture* setMinMagFilter(GLenum val);
    virtual Texture* setWrap(GLenum val);

    /* - Parameter Getters - */

    inline uint32_t getWidth() { return _width; }
    inline uint32_t getHeight() { return _height; }
    inline uint32_t getNrChannels() { return _nrChannels; }

    inline GLuint getHandle() { return _handle; }

   protected:
    uint32_t _width{0}, _height{0}, _nrChannels{0};
    GLuint _handle{0};

   private:
    void _loadTexture(std::string const& path);
};