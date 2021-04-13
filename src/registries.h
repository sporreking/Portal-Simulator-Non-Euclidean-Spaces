#pragma once
#include <vector>

#include "registry.h"
#include "shaderprogram.h"
#include "texture.h"

/* -- Registry Declarations -- */
class REG {
   public:
    static void init();
    static inline Registry<ShaderProgram> const& SHADER_PROGRAMS() { return _shaderPrograms; }
    static inline Registry<Texture> const& TEXTURES() { return _textures; }

   private:
    static Registry<ShaderProgram> _shaderPrograms;
    static Registry<Texture> _textures;
};