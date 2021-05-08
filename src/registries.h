#pragma once
#include <vector>

#include "cubemap.h"
#include "mesh.h"
#include "registry.h"
#include "shaderprogram.h"
#include "texture.h"

/* -- Resource Names -- */

#define SHADER_PROGRAM_PHONG "phong"
#define SHADER_PROGRAM_SKYBOX "skybox"
#define SHADER_PROGRAM_TEST "test"

#define TEXTURE_DEFAULT "default"
#define TEXTURE_WALL "wall"

// Skyboxes
#define NR_SKYBOXES 12
#define CUBEMAP_SKY "sky"
#define SKYBOX_NAMES \
    { "arch3", "cave3", "dark", "hot", "rainbow", "sh", "skyast", "skyhsky", "skype", "sp2", "sp3", "tron" }

#define MESH_QUAD "quad"
#define MESH_CUBE "cube"
#define MESH_SKYBOX "skybox"
#define MESH_BUNNY "bunny"

/* -- Registry Declarations -- */
class REG {
   public:
    static void init();
    static inline Registry<ShaderProgram> const& SHADER_PROGRAMS() { return _shaderPrograms; }
    static inline Registry<Texture> const& TEXTURES() { return _textures; }
    static inline Registry<Mesh> const& MESHES() { return _meshes; }

   private:
    static Registry<ShaderProgram> _shaderPrograms;
    static Registry<Texture> _textures;
    static Registry<Mesh> _meshes;
};