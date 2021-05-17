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

// Control
#define UNILOC_USE_LIGHTING 3000
#define UNILOC_USE_TEXTURE 3001
#define UNILOC_USE_MIN_DEPTH 3002
#define UNILOC_MIN_DEPTH_SAMPLER 3003

// Info
#define UNILOC_WINDOW_WIDTH 4000
#define UNILOC_WINDOW_HEIGHT 4001

// Texture locations
#define TEXLOC_MIN_DEPTH 31

// Light types
#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1

// Constants
#define MAX_LIGHTS 32

class ShaderProgram {
   public:
    ShaderProgram(std::vector<Shader*> const& shaders);
    ~ShaderProgram();

    ShaderProgram* sendLights(std::vector<Component*> const& lights,
                              glm::mat4 const& transformMatrix = glm::mat4{1.0});

    ShaderProgram* sendMaterial(COMP::Material* const material, uint32_t sampler = 0);

    ShaderProgram* bind();

    inline GLuint getHandle() { return _handle; }

    /* -- Static -- */

    // Set nullptr to disable
    static Texture* setMinDepthTexture(Texture* t);
    static inline Texture* getMinDepthTexture() { return _minDepthTexture; }
    static inline void setWindowWidth(uint32_t w) { _windowWidth = w; }
    static inline void setWindowHeight(uint32_t h) { _windowHeight = h; }

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

    /* -- Static -- */

    static Texture* _minDepthTexture;
    static uint32_t _windowWidth;
    static uint32_t _windowHeight;
};