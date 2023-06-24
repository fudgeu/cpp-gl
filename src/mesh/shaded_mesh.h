#pragma once

#include "mesh.h"
#include "../shader/mesh_shader.h"
#include "../texture/texture.h"

struct ShadedMesh {
public:
    ShadedMesh(const Mesh &mesh, const MeshShader &shader, const Texture &texture);

    const Mesh &getMesh() const;
    const MeshShader &getShader() const;
    const Texture &getTexture() const;

private:
    const Mesh mesh;
    const MeshShader shader;
    const Texture texture;
};