#pragma once

#include <vector>

#include "shader.h"

// Attribute locations
#define ATTLOC_POSITION 0
#define ATTLOC_NORMAL 1
#define ATTLOC_TEX_COORDS 2
#define ATTLOC_COLOR 3

class ShaderProgram {
   public:
    ShaderProgram(std::vector<Shader*> const& shaders);
    ~ShaderProgram();

    inline GLuint getHandle() { return _handle; }

   private:
    void _linkShaders(std::vector<Shader*> const& shaders);
    GLuint _handle{0};
};