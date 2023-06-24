#pragma once

#include <string>
#include <optional>
#include <unordered_map>

#include "../enum/result.h"
#include "mesh_shader.h"


class ShaderRegistry {
  public:
    void registerMeshShader(const std::string& shaderId, const MeshShader& shader);
    std::optional<std::reference_wrapper<const MeshShader>> getMeshShader(const std::string& shaderId) const;

  private:
    std::unordered_map<std::string, MeshShader> registeredMeshShaders;
};