#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <memory>
#include "../entity/entity.h"

class Camera {
  public:
    Camera(double x, double y, double z, double fovDeg, int screenWidth, int screenHeight);
    void updateScreenSize(int width, int height);
    void setFOV(float deg);
    const glm::mat4x4& getPerspectiveMatrix() const;
    const glm::mat4x4& getTransformMatrix();
    int getScreenWidth() const;
    int getScreenHeight() const;

    void attachToEntity(std::shared_ptr<Entity> entity);
    bool isAttachedToEntity() const;
    void unattachFromEntity();

  private:
    glm::mat4x4 perspective {};
    glm::mat4x4 transform {};

    double degRad;
    int    screenWidth;
    int    screenHeight;

    bool attachedToEntity = false;
    std::shared_ptr<Entity> attachedEntity   = nullptr;

    void createPerspectiveMatrix();
};