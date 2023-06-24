#pragma once

#include <GL/gl.h>

class Mesh {
public:
    static Mesh create(
            float positions[],
            float uv[],
            int countVertices,
            unsigned int indices[],
            int countIndices
    );

    Mesh(
            GLuint positionsVBOHandle,
            GLuint uvVBOHandle,
            int countVertices,
            int positionsVBOStride,
            int uvVBOStride,
            GLuint indicesIBOHandle,
            int countIndices,
            int indicesIBORawSize
    );

    GLuint positionsVBOHandle;
    GLuint uvVBOHandle;

    int countVertices;
    int positionsVBOStride;
    int uvVBOStride;

    GLuint indicesIBOHandle;

    int countIndices;
    int indicesIBORawSize;

    GLuint VAOHandle = 0;
};

