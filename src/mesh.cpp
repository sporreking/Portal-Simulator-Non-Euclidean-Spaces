
#include "mesh.h"

#include <LittleOBJLoader.h>

Mesh::Mesh(size_t nrVertices, GLfloat *verts, GLfloat *norms,
           GLfloat *texCoords, size_t nrIndices, GLuint *indices)
    : _nrVertices{nrVertices}, _nrIndices{nrIndices} {
    // Bind VAO
    glGenVertexArrays(1, &_vao);
    bind();

    // Bind buffer for vertex positions
    glGenBuffers(1, &_vboVert);
    glBindBuffer(GL_ARRAY_BUFFER, _vboVert);
    glBufferData(GL_ARRAY_BUFFER, nrVertices * 3 * sizeof(GLfloat), verts, GL_STATIC_DRAW);

    // Bind attributes
    glVertexAttribPointer(ATTLOC_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(ATTLOC_POSITION);

    // Bind normals, if specified
    if (norms != nullptr) {
        glGenBuffers(1, &_vboNorm);
        glBindBuffer(GL_ARRAY_BUFFER, _vboNorm);
        glBufferData(GL_ARRAY_BUFFER, nrVertices * 3 * sizeof(GLfloat), norms, GL_STATIC_DRAW);

        // Bind attributes
        glVertexAttribPointer(ATTLOC_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(ATTLOC_NORMAL);
    }

    // Bind texture coordinates, if specified
    if (texCoords != nullptr) {
        glGenBuffers(1, &_vboTex);
        glBindBuffer(GL_ARRAY_BUFFER, _vboTex);
        glBufferData(GL_ARRAY_BUFFER, nrVertices * 2 * sizeof(GLfloat), texCoords, GL_STATIC_DRAW);

        // Bind attributes
        glVertexAttribPointer(ATTLOC_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(ATTLOC_TEX_COORDS);
    }

    // Bind index buffer, if specified
    if (nrIndices > 0) {
        glGenBuffers(1, &_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);
    }
    glBindVertexArray(0);  // Previous vertex array binding is broken
}

Mesh::Mesh(size_t nrVertices, GLfloat *verts, GLfloat *norms, GLfloat *texCoords)
    : Mesh(nrVertices, verts, norms, texCoords, 0, nullptr) {}

Mesh::Mesh(std::string const &modelPath) {
    Model *m = LoadModel(modelPath.c_str());
    _vao = m->vao;
    _vboVert = m->vb;
    _vboNorm = m->nb;
    _vboTex = m->tb;
    _ibo = m->ib;
    _nrVertices = m->numVertices;
    _nrIndices = m->numIndices;

    // Associate buffers with VAO
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, _vboVert);
    glVertexAttribPointer(ATTLOC_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(ATTLOC_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, _vboNorm);
    glVertexAttribPointer(ATTLOC_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(ATTLOC_NORMAL);

    if (m->tb > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, _vboTex);
        glVertexAttribPointer(ATTLOC_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(ATTLOC_TEX_COORDS);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBindVertexArray(0);  // Previous vertex array binding is broken
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &_vboVert);
    glDeleteBuffers(1, &_vboNorm);
    if (_vboTex > 0)
        glDeleteBuffers(1, &_vboTex);
    glDeleteBuffers(1, &_ibo);
    glDeleteVertexArrays(1, &_vao);
}