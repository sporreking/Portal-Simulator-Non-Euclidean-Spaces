
#pragma once

#include <glad/glad.h>

#include "shaderprogram.h"

class Mesh {
   public:
    Mesh(size_t nrVertices, GLfloat *verts,
         GLfloat *norms, GLfloat *texCoords,
         size_t nrIndices, GLuint *indices);

    Mesh(size_t nrVertices, GLfloat *verts, GLfloat *norms,
         GLfloat *texCoords);

    Mesh(std::string const &modelPath);

    ~Mesh();

    inline Mesh *bind() {
        glBindVertexArray(_vao);
        return this;
    }

    /* -- Getters -- */

    inline GLuint getHandle() { return _vao; }
    inline size_t getNrVertices() { return _nrVertices; }
    inline size_t getNrIndices() { return _nrIndices; }

   private:
    size_t _nrVertices;
    size_t _nrIndices;
    GLuint _vao;
    GLuint _ibo;
    GLuint _vboVert;
    GLuint _vboNorm;
    GLuint _vboTex;
};