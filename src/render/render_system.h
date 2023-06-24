#pragma once

#include "../camera/camera.h"
#include "../mesh/mesh.h"
#include "../shader/shader_registry.h"
#include "../object/object.h"

#include <vector>

class RenderSystem {
  public:
    explicit RenderSystem(ShaderRegistry& shaderRegistry);
    void render(Camera& camera);
    void addToQueue(const Object& object);

    constexpr const static double SCREEN_SPACE_SCALE = 0.05;

  private:
    ShaderRegistry&     shaderReg;
    std::vector<Object> renderQueue;
};