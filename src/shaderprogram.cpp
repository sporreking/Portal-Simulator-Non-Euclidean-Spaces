#include "shaderprogram.h"

ShaderProgram::ShaderProgram(std::vector<Shader*> const& shaders) {
    // Create program
    _handle = glCreateProgram();

    _linkShaders(shaders);
}

ShaderProgram* ShaderProgram::sendLights(std::vector<Component*> const& lights,
                                         glm::mat4 const& transformMatrix) {
    size_t i{0};
    for (Component* light : lights) {
        // Check light type
        if (dynamic_cast<COMP::PointLight*>(light)) {
            // Point light
            COMP::PointLight* pl = dynamic_cast<COMP::PointLight*>(light);

            _lightTypes[i] = LIGHT_TYPE_POINT;
            _lightPositions[i] = glm::vec3(transformMatrix * glm::vec4{pl->position(), 1.0});
            _lightColors[i] = pl->color;
            _lightRanges[i] = pl->range;

            i++;
        } else {
            // Unknown light
            std::cerr << "Unknown light source type!" << std::endl;
        }
    }

    // Send uniforms
    bind();
    glUniform1ui(UNILOC_NR_LIGHTS, i);

    if (i > 0) {
        glUniform1uiv(UNILOC_LIGHT_TYPES, i, _lightTypes);
        glUniform3fv(UNILOC_LIGHT_POSITIONS, i, (float*)_lightPositions);
        glUniform3fv(UNILOC_LIGHT_COLORS, i, (float*)_lightColors);
        glUniform1dv(UNILOC_LIGHT_RANGES, i, _lightRanges);
    }

    return this;
}

ShaderProgram* ShaderProgram::sendMaterial(COMP::Material* const material,
                                           uint32_t sampler) {
    bind();

    glUniform1d(UNILOC_MATERIAL_KD, material->kd);
    glUniform1d(UNILOC_MATERIAL_KS, material->ks);
    glUniform1d(UNILOC_MATERIAL_ALPHA, material->alpha);
    glUniform3fv(UNILOC_MATERIAL_COLOR, 1, (float*)&material->color);
    glUniform1ui(UNILOC_MATERIAL_SAMPLER, sampler);

    return this;
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