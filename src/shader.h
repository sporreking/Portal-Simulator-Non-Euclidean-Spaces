#pragma once

#include <glad/glad.h>

#include <string>

#include "fileloader.h"

class Shader {
   public:
    Shader(GLenum type, std::string const& path);
    ~Shader();

    inline GLuint getHandle() { return _handle; }
    inline GLenum getType() { return _type; }

   private:
    void _compile(std::string const& source);
    GLuint _handle{0};
    GLenum _type;
};