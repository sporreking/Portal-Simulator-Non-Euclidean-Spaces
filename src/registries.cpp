#include "registries.h"

/* -- Register Shader Programs -- */

void initShaderPrograms(Registry<ShaderProgram> *reg) {
    Shader testVert = Shader(GL_VERTEX_SHADER, "./res/shader/test.vert");
    Shader testFrag = Shader(GL_FRAGMENT_SHADER, "./res/shader/test.frag");
    reg->put("test", new ShaderProgram({&testVert, &testFrag}));
}

/* -- Initialization Function -- */
void REG::init() {
    _shaderPrograms.init();
}

/* -- Registry Instantiations -- */
Registry<ShaderProgram> REG::_shaderPrograms(initShaderPrograms);