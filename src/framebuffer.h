#pragma once

#include "config.h"
#include "texture.h"

class FrameBuffer {
   public:
    FrameBuffer(uint32_t width, uint32_t height, bool useDepthBuffer);
    ~FrameBuffer();

    FrameBuffer *bind();

    inline uint32_t getWidth() { return _width; }
    inline uint32_t getHeight() { return _height; }
    inline bool hasDepthBuffer() { return _useDepthBuffer; }

    inline Texture *texture() { return _texture; }

    inline GLuint getHandle() { return _handle; }

    static void bindDefault();

   private:
    /* -- Parameters -- */

    uint32_t _width, _height;
    bool _useDepthBuffer;

    /* -- Core -- */

    GLuint _handle{0};
    GLuint _depthBuffer{0};
    Texture *_texture;

    void _createFrameBuffer();
};