#pragma once

#include <vector>
#include "../mesh/shaded_mesh.h"
#include "../texture/texture.h"
#include "bounding_box.h"

class Model {
public:
    void addShadedMesh(const Mesh &mesh, const MeshShader &shader, const Texture &texture);
    void addBoundingBox(BoundingBox box);
    const std::vector<ShadedMesh> &getShadedMeshes() const;
    const std::vector<BoundingBox> &getBoundingBoxes() const;
    int getWidth() const;
    int getHeight() const;

private:
    std::vector<ShadedMesh> meshes;
    std::vector<BoundingBox> boundingBoxes;
    int width  = 0;
    int height = 0;
};