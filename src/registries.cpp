#include "registries.h"

/* -- Register Shader Programs -- */

void initShaderPrograms(Registry<ShaderProgram> *reg) {
    Shader testVert = Shader(GL_VERTEX_SHADER, "./res/shader/test.vert");
    Shader testFrag = Shader(GL_FRAGMENT_SHADER, "./res/shader/test.frag");
    reg->put("test", new ShaderProgram({&testVert, &testFrag}));
}

/* -- Register Textures -- */
void initTextures(Registry<Texture> *reg) {
    reg->put("default", (new Texture("./res/texture/default.png"))
                            ->setMinMagFilter(GL_NEAREST)
                            ->setWrap(GL_REPEAT));
}

/* -- Initialization Function -- */
void REG::init() {
    _shaderPrograms.init();
    _textures.init();
}

/* -- Registry Instantiations -- */
Registry<ShaderProgram> REG::_shaderPrograms(initShaderPrograms);
Registry<Texture> REG::_textures(initTextures);