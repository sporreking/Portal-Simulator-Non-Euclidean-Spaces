#include "registries.h"

/* -- Register Shader Programs -- */

void initShaderPrograms(Registry<ShaderProgram> *reg) {
    Shader testVert = Shader(GL_VERTEX_SHADER, "./res/shader/test.vert");
    Shader testFrag = Shader(GL_FRAGMENT_SHADER, "./res/shader/test.frag");
    reg->put(SHADER_PROGRAM_TEST, new ShaderProgram({&testVert, &testFrag}));

    Shader phongVert = Shader(GL_VERTEX_SHADER, "./res/shader/phong.vert");
    Shader phongFrag = Shader(GL_FRAGMENT_SHADER, "./res/shader/phong.frag");
    reg->put(SHADER_PROGRAM_PHONG, new ShaderProgram({&phongVert, &phongFrag}));

    Shader skyboxVert = Shader(GL_VERTEX_SHADER, "./res/shader/skybox.vert");
    Shader skyboxFrag = Shader(GL_FRAGMENT_SHADER, "./res/shader/skybox.frag");
    reg->put(SHADER_PROGRAM_SKYBOX, new ShaderProgram({&skyboxVert, &skyboxFrag}));

    Shader linkVert = Shader(GL_VERTEX_SHADER, "./res/shader/link.vert");
    Shader linkFrag = Shader(GL_FRAGMENT_SHADER, "./res/shader/link.frag");
    reg->put(SHADER_PROGRAM_LINK, new ShaderProgram({&linkVert, &linkFrag}));
}

/* -- Register Textures -- */
void initTextures(Registry<Texture> *reg) {
    reg->put(TEXTURE_DEFAULT, (new Texture("./res/texture/default.png"))
                                  ->setMinMagFilter(GL_NEAREST)
                                  ->setWrap(GL_REPEAT));
    reg->put(TEXTURE_WALL, (new Texture("./res/texture/wall.png"))
                               ->setMinMagFilter(GL_NEAREST)
                               ->setWrap(GL_REPEAT));

    // Load skyboxes
    std::string skyboxNames[NR_SKYBOXES] = SKYBOX_NAMES;
    for (uint32_t i = 0; i < NR_SKYBOXES; i++)
        reg->put(std::string(CUBEMAP_SKY) + std::to_string(i),
                 new Cubemap(std::string("./res/texture/skybox/") + skyboxNames[i], "png"));
}

/* -- Register Meshes -- */
void initMeshes(Registry<Mesh> *reg) {
#include "meshprimitives.inl"
    // Primitives
    reg->put(MESH_QUAD, new Mesh(4, quadPos, quadNorm, quadTex, 6, quadInd));
    reg->put(MESH_CUBE, new Mesh(24, cubePos, cubeNorm, cubeTex, 6 * 6, cubeInd));
    reg->put(MESH_SKYBOX, new Mesh(8, skyboxPos, nullptr, nullptr, 6 * 6, skyboxInd));

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