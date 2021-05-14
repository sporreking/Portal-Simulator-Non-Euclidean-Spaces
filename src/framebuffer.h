#pragma once

#include <vector>

#include "config.h"
#include "texture.h"

enum DepthBufferConfig {
    NONE = 0,
    WRITE_ONLY = 1,
    READ_WRITE = 2
};

class FrameBuffer {
   public:
    FrameBuffer(uint32_t width, uint32_t height, bool useColorBuffer, DepthBufferConfig c);
    ~FrameBuffer();

    FrameBuffer *bind();

    inline uint32_t getWidth() { return _width; }
    inline uint32_t getHeight() { return _height; }
    inline bool hasDepthBuffer() { return _depthBufferConfig != NONE; }
    inline DepthBufferConfig getDepthBufferConfig() { return _depthBufferConfig; }

    inline Texture *texture() { return _texture; }
    inline Texture *depthTexture() { return _depthTexture; }

    inline GLuint getHandle() { return _handle; }

    /* -- Static -- */

    static void bindDefault();
    static inline FrameBuffer *getColorBuffer(size_t id) { return _colorBuffers.at(id); }
    static inline FrameBuffer *getDepthBuffer(size_t id) { return _depthBuffers.at(id); }
    static void init();
    static void free();

   private:
    /* -- Parameters -- */

    uint32_t _width, _height;
    bool _useColorBuffer;
    DepthBufferConfig _depthBufferConfig;

    /* -- Core -- */

    GLuint _handle{0};
    Texture *_texture;
    GLuint _depthBuffer{0};
    Texture *_depthTexture;

    void _createFrameBuffer();

    /* -- Static -- */

    static std::vector<FrameBuffer *> _colorBuffers;
    static std::vector<FrameBuffer *> _depthBuffers;
};