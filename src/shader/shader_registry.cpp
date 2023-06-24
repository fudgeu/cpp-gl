#include "shader_registry.h"

void ShaderRegistry::registerMeshShader(const std::string& shaderId, const MeshShader& shader) {
  registeredMeshShaders[shaderId] = shader;
}

std::optional<std::reference_wrapper<const MeshShader>> ShaderRegistry::getMeshShader(const std::string& shaderId) const {
  if (registeredMeshShaders.count(shaderId) == 0)
    return std::nullopt;

  return registeredMeshShaders.at(shaderId);
}