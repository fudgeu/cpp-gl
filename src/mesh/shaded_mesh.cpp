#include "shaded_mesh.h"

#include <utility>

ShadedMesh::ShadedMesh(const Mesh &mesh_, const MeshShader &shader_, const Texture &texture_) :
        mesh(mesh_), shader(shader_), texture(texture_) {}

const Mesh &ShadedMesh::getMesh() const {
    return mesh;
}

const MeshShader &ShadedMesh::getShader() const {
    return shader;
}

const Texture &ShadedMesh::getTexture() const {
    return texture;
}

