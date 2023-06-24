//
// Created by fudgeu on 6/17/23.
//

#include <memory>
#include "model.h"

// Copy mesh since they will likely be created and forgotten
// Maybe optimize in the future to keep a store of common meshes and refer to one that has already been created
void Model::addShadedMesh(const Mesh &mesh, const MeshShader &shader, const Texture &texture) {

    meshes.emplace_back(mesh, shader, texture);
}

void Model::addBoundingBox(BoundingBox box) {
    if (box.right > width)
        width = box.right;
    if (box.top > height)
        height = box.top;
    boundingBoxes.push_back(box);
}

const std::vector<ShadedMesh> &Model::getShadedMeshes() const {
    return meshes;
}

const std::vector<BoundingBox> &Model::getBoundingBoxes() const {
    return boundingBoxes;
}

int Model::getWidth() const {
    return width;
}

int Model::getHeight() const {
    return height;
}
