#include "framebuffer.h"

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, bool useDepthBuffer)
    : _width{width}, _height{height}, _useDepthBuffer{useDepthBuffer} {
    _createFrameBuffer();
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &_handle);
    glDeleteRenderbuffers(1, &_depthBuffer);
    delete _texture;
}

FrameBuffer *FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, _handle);
    glViewport(0, 0, _width, _height);
    return this;
}

void FrameBuffer::bindDefault() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void FrameBuffer::init() {
    for (size_t i{0}; i < NR_FRAME_BUFFERS; i++)
        _frameBuffers.push_back(new FrameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, true));
}

void FrameBuffer::free() {
    for (size_t i{0}; i < NR_FRAME_BUFFERS; i++)
        delete _frameBuffers[i];
    _frameBuffers.clear();
}

void FrameBuffer::_createFrameBuffer() {
    // Generate frame buffer
    glGenFramebuffers(1, &_handle);
    glBindFramebuffer(GL_FRAMEBUFFER, _handle);

    // Allocate texture memory
    _texture = new Texture;
    _texture->bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, 0);
    _texture->setMinMagFilter(GL_NEAREST);

    // Generate and bind depth buffer if applicable
    if (_useDepthBuffer) {
        glGenRenderbuffers(1, &_depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    }

    // Bind texture to frame buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _texture->getHandle(), 0);

    // Map shader output to texture
    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);

    // Validity check
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Invalid framebuffer configuration!" << std::endl;
        throw -1;
    }

    // Unbind frame buffer
    bindDefault();
}

std::vector<FrameBuffer *> FrameBuffer::_frameBuffers;