#include "model_factory.h"

using namespace glm;

//static vec2 pos0 = vec2(0.0, 0.0);
//static vec2 pos1 = vec2(0.0, 0.1);
//static vec2 pos2 = vec2(0.1, 0.0);
//static vec2 pos3 = vec2(0.1, 0.1);

/*static float colors[] = {
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
};*/

static float uv[] ={
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
};

static float standardVertices[] = {
        0.0f, 0.0f,
        0.0f, 0.05f,
        0.05f, 0.0f,
        0.05f, 0.05f
};
static int countVertices = 4;

static unsigned int indices[] = {0, 1, 2, 2, 1, 3};
static int countIndices = 6;


Model ModelFactory::create(int width, int height, const MeshShader &shader, const Texture &texture) {
    // Create mesh of appropriate size
    float vertices[countVertices * 2];
    for (int i = 0; i < countVertices; i++) {
        float xVertex = standardVertices[i * 2];
        float yVertex = standardVertices[i * 2 + 1];
        vertices[i * 2]     = xVertex * width;
        vertices[i * 2 + 1] = yVertex * height;
    }
    Mesh mesh = Mesh::create(vertices, uv, countVertices, indices, countIndices);

    // Create a model with the mesh
    Model model = modelStore.emplace_back();
    model.addShadedMesh(mesh, shader, texture);
    model.addBoundingBox(BoundingBox(height, 0, 0, width));

    return model;
}
