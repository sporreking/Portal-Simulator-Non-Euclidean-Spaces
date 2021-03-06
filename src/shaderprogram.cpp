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
            _lightPositions[i] = glm::vec3(transformMatrix * glm::vec4{pl->position(), 1.0f});
            _lightColors[i] = pl->color;
            _lightRanges[i] = (float)pl->range;

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
        glUniform1fv(UNILOC_LIGHT_RANGES, i, _lightRanges);
    }

    return this;
}

ShaderProgram* ShaderProgram::sendMaterial(COMP::Material* const material,
                                           uint32_t sampler) {
    bind();

    glUniform1f(UNILOC_MATERIAL_KD, (float)material->kd);
    glUniform1f(UNILOC_MATERIAL_KS, (float)material->ks);
    glUniform1f(UNILOC_MATERIAL_ALPHA, (float)material->alpha);
    glUniform3fv(UNILOC_MATERIAL_COLOR, 1, glm::value_ptr(material->color));
    glUniform1ui(UNILOC_MATERIAL_SAMPLER, sampler);

    return this;
}

ShaderProgram* ShaderProgram::bind() {
    glUseProgram(_handle);

    // Send window information
    glUniform1f(UNILOC_WINDOW_WIDTH, (float)_windowWidth);
    glUniform1f(UNILOC_WINDOW_HEIGHT, (float)_windowHeight);

    // Enforce minimum depth if applicable
    if (_minDepthTexture) {
        glUniform1i(UNILOC_USE_MIN_DEPTH, GL_TRUE);
        _minDepthTexture->bind(TEXLOC_MIN_DEPTH);
        glUniform1i(UNILOC_MIN_DEPTH_SAMPLER, TEXLOC_MIN_DEPTH);
    } else
        glUniform1i(UNILOC_USE_MIN_DEPTH, GL_FALSE);

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

Texture* ShaderProgram::setMinDepthTexture(Texture* t) {
    Texture* old = _minDepthTexture;
    _minDepthTexture = t;
    return old;
}

Texture* ShaderProgram::_minDepthTexture{nullptr};
uint32_t ShaderProgram::_windowWidth{WINDOW_WIDTH};
uint32_t ShaderProgram::_windowHeight{WINDOW_HEIGHT};