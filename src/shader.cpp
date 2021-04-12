#include "shader.h"

Shader::Shader(GLenum type, std::string const& path)
    : _type{type} {
    // Create shader
    _handle = glCreateShader(_type);

    _compile(FileLoader::loadText(path));
}

void Shader::_compile(std::string const& source) {
    // Attach source
    const char* src = source.c_str();
    glShaderSource(_handle, 1, &src, NULL);

    // Compile shader
    glCompileShader(_handle);

    // Check status
    GLint compileStatus;
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        GLsizei logLength = 0;
        glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &logLength);

        // Get error log
        void* message = malloc(logLength * sizeof(GLchar));
        glGetShaderInfoLog(_handle, logLength, NULL, (GLchar*)message);

        // Print error log
        std::cerr << "################################" << std::endl;
        std::cerr << "### Could not compile shader ###" << std::endl;
        std::cerr << (char*)message << std::flush;
        std::cerr << "################################" << std::endl;

        free(message);

        throw -1;
    }
}

Shader::~Shader() {
    glDeleteShader(_handle);
}