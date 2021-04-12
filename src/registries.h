#pragma once
#include <vector>

#include "registry.h"
#include "shaderprogram.h"

/* -- Registry Declarations -- */
class REG {
   public:
    static void init();
    static inline const Registry<ShaderProgram> SHADER_PROGRAMS() { return _shaderPrograms; }

   private:
    static Registry<ShaderProgram> _shaderPrograms;
};