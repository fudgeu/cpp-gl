#include <GL/glew.h>
#include <memory>

#include "mesh.h"

const int POSITIONS_VERTEX_SIZE = 2;
const int UV_VERTEX_SIZE = 2;

Mesh Mesh::create(float positions[], float uv[], int countVertices, unsigned int indices[], int countIndices) {

    // Init positions buffer
    GLuint positionsVBOHandle_;
    int positionsVBOStride_ = POSITIONS_VERTEX_SIZE * sizeof(GL_FLOAT);
    glGenBuffers(1, &positionsVBOHandle_);
    glBindBuffer(GL_ARRAY_BUFFER, positionsVBOHandle_);
    glBufferData(GL_ARRAY_BUFFER, countVertices * positionsVBOStride_, positions, GL_STATIC_DRAW);

    // Init colors buffer
    GLuint uvVBOHandle_;
    int uvVBOStride_ = UV_VERTEX_SIZE * sizeof(GL_FLOAT);
    glGenBuffers(1, &uvVBOHandle_);
    glBindBuffer(GL_ARRAY_BUFFER, uvVBOHandle_);
    glBufferData(GL_ARRAY_BUFFER, countVertices * uvVBOStride_, uv, GL_STATIC_DRAW);

    // Init indices buffer
    GLuint indicesIBOHandle_;
    int indicesIBORawSize_ = countIndices * sizeof(unsigned int);
    glGenBuffers(1, &indicesIBOHandle_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesIBOHandle_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesIBORawSize_, indices, GL_STATIC_DRAW);

    return {
            positionsVBOHandle_,
            uvVBOHandle_,
            countVertices,
            positionsVBOStride_,
            uvVBOStride_,
            indicesIBOHandle_,
            countIndices,
            indicesIBORawSize_
    };
}

Mesh::Mesh(GLuint positionsVBOHandle, GLuint uvVBOHandle, int countVertices, int positionsVBOStride,
           int uvVBOStride, GLuint indicesIBOHandle, int countIndices, int indicesIBORawSize):
           positionsVBOHandle(positionsVBOHandle),
           uvVBOHandle(uvVBOHandle),
           countVertices(countVertices),
           positionsVBOStride(positionsVBOStride),
           uvVBOStride(uvVBOStride),
           indicesIBOHandle(indicesIBOHandle),
           countIndices(countIndices),
           indicesIBORawSize(indicesIBORawSize) {}
