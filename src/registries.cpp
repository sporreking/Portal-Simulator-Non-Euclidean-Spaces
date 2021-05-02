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
}

/* -- Register Meshes -- */
void initMeshes(Registry<Mesh> *reg) {
    // Quad
    GLfloat quadPos[12] = {-.5, -.5, .0, -.5, .5, .0, .5, .5, .0, .5, -.5, .0};
    GLfloat quadNorm[12] = {.0, .0, 1.0, .0, .0, 1.0, .0, .0, 1.0, .0, .0, 1.0};
    GLfloat quadTex[8] = {0, 0, 0, 1, 1, 1, 1, 0};
    GLuint quadInd[6] = {0, 1, 2, 2, 3, 0};
    reg->put(MESH_QUAD, new Mesh(4, quadPos, quadNorm, quadTex, 6, quadInd));

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