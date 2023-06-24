#pragma once
#include <string>
#include "../mesh/mesh.h"

class Shader {
  public:
    virtual void use(const Mesh& mesh, const glm::mat4 &transformMatrix) const = 0;
};