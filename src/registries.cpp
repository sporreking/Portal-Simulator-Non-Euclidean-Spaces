#include "registries.h"

/* -- Register Shader Programs -- */

void initShaderPrograms(Registry<ShaderProgram> *reg) {
    Shader testVert = Shader(GL_VERTEX_SHADER, "./res/shader/test.vert");
    Shader testFrag = Shader(GL_FRAGMENT_SHADER, "./res/shader/test.frag");
    reg->put(SHADER_PROGRAM_TEST, new ShaderProgram({&testVert, &testFrag}));

    Shader phongVert = Shader(GL_VERTEX_SHADER, "./res/shader/phong.vert");
    Shader phongFrag = Shader(GL_FRAGMENT_SHADER, "./res/shader/phong.frag");
    reg->put(SHADER_PROGRAM_PHONG, new ShaderProgram({&phongVert, &phongFrag}));
}

/* -- Register Textures -- */
void initTextures(Registry<Texture> *reg) {
    reg->put(TEXTURE_DEFAULT, (new Texture("./res/texture/default.png"))
                                  ->setMinMagFilter(GL_NEAREST)
                                  ->setWrap(GL_REPEAT));
    reg->put(TEXTURE_WALL, (new Texture("./res/texture/wall.png"))
                               ->setMinMagFilter(GL_NEAREST)
                               ->setWrap(GL_REPEAT));
}

/* -- Register Meshes -- */
void initMeshes(Registry<Mesh> *reg) {
#include "meshprimitives.inl"
    // Primitives
    reg->put(MESH_QUAD, new Mesh(4, quadPos, quadNorm, quadTex, 6, quadInd));
    reg->put(MESH_CUBE, new Mesh(24, cubePos, cubeNorm, cubeTex, 6 * 6, cubeInd));

    // Bunny
    reg->put(MESH_BUNNY, new Mesh("./res/model/bunnyplus.obj"));
}

/* -- Initialization Function -- */
void REG::init() {
    _shaderPrograms.init();
    _textures.init();
    _meshes.init();
}

/* -- Registry Instantiations -- */
Registry<ShaderProgram> REG::_shaderPrograms(initShaderPrograms);
Registry<Texture> REG::_textures(initTextures);
Registry<Mesh> REG::_meshes(initMeshes);