#pragma once

#include "../object/object.h"

namespace ModelFactory {
    static std::vector<Model> modelStore;

    Model create(int width, int height, const MeshShader &shader, const Texture &texture);
}