#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "components/material.h"
#include "components/pointlight.h"
#include "config.h"
#include "shader.h"

// Attribute locations
#define ATTLOC_POSITION 0
#define ATTLOC_NORMAL 1
#define ATTLOC_TEX_COORDS 2
#define ATTLOC_COLOR 3

// Uniform locations
#define UNILOC_MODEL_MAT 0
#define UNILOC_VIEW_MAT 1
#define UNILOC_PROJECTION_MAT 2

#define UNILOC_NR_LIGHTS 1000  // Increments according to MAX_LIGHTS
#define UNILOC_LIGHT_TYPES 1032
#define UNILOC_LIGHT_POSITIONS 1064
#define UNILOC_LIGHT_COLORS 1096
#define UNILOC_LIGHT_RANGES 1128

#define UNILOC_MATERIAL_KD 2000
#define UNILOC_MATERIAL_KS 2001
#define UNILOC_MATERIAL_ALPHA 2002
#define UNILOC_MATERIAL_COLOR 2003
#define UNILOC_MATERIAL_SAMPLER 2004

// Light types
#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1

// Constants
#define MAX_LIGHTS 32
#define FOV 90.0
#define ASPECT_RATIO (((double)WINDOW_WIDTH) / WINDOW_HEIGHT)
#define NEAR_PLANE 0.01
#define FAR_PLANE 100.0

class ShaderProgram {
   public:
    ShaderProgram(std::vector<Shader*> const& shaders);
    ~ShaderProgram();

    ShaderProgram* sendLights(std::vector<Component*> const& lights,
                              glm::mat4 const& transformMatrix = glm::mat4{1.0});

    ShaderProgram* sendMaterial(COMP::Material* const material, uint32_t sampler = 0);

    inline ShaderProgram* bind() {
        glUseProgram(_handle);
        return this;
    };

    inline GLuint getHandle() { return _handle; }
    static glm::mat4 const PROJECTION_MATRIX;

   private:
    void _linkShaders(std::vector<Shader*> const& shaders);
    GLuint _handle{0};

    /* -- Lighting -- */

    // General

    uint32_t _lightTypes[MAX_LIGHTS];
    glm::vec3 _lightPositions[MAX_LIGHTS];
    glm::vec3 _lightColors[MAX_LIGHTS];

    // Point lights

    float _lightRanges[MAX_LIGHTS];
};