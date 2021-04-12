#include "shaderprogram.h"

ShaderProgram::ShaderProgram(std::vector<Shader*> const& shaders) {
    // Create program
    _handle = glCreateProgram();

    _linkShaders(shaders);
}

void ShaderProgram::_linkShaders(std::vector<Shader*> const& shaders) {
    // Attach shaders
    for (Shader* shader : shaders)
        glAttachShader(_handle, shader->getHandle());

    // Link program
    glLinkProgram(_handle);

    // Check status
    GLint linkStatus;
    glGetProgramiv(_handle, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        GLsizei logLength = 0;
        glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &logLength);

        // Get error log
        void* message = malloc(logLength * sizeof(GLchar));
        glGetProgramInfoLog(_handle, logLength, NULL, (GLchar*)message);

        // Print error log
        std::cerr << "##############################" << std::endl;
        std::cerr << "### Could not link program ###" << std::endl;
        std::cerr << (char*)message << std::flush;
        std::cerr << "##############################" << std::endl;

        free(message);

        throw -1;
    }

    // Detach shaders
    for (Shader* shader : shaders)
        glDetachShader(_handle, shader->getHandle());
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(_handle);
}