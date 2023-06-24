#include <glm/gtc/matrix_transform.hpp>
#include <utility>

#include "camera.h"
#include "../render/render_system.h"

// This camera will remain stationary for the most part, as world objects will instead adjust their position

Camera::Camera(double x, double y, double z, double fovDeg, int screenWidth, int screenHeight) {
  degRad = glm::radians(fovDeg);
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;

  transform = glm::mat4(1.0);
  transform = glm::translate(transform, glm::vec3(x, y, z));

  createPerspectiveMatrix();
}

// Getters

const glm::mat4x4& Camera::getPerspectiveMatrix() const {
  return perspective;
}

const glm::mat4x4& Camera::getTransformMatrix() {
    if (attachedToEntity) { // may have to do tests later to see if it is just faster to build a new matrix or transform the existing one
        auto currentPos = glm::vec3(transform[3]);
        double deltaX = (-attachedEntity->getX() * RenderSystem::SCREEN_SPACE_SCALE) - currentPos.x;
        double deltaY = (-attachedEntity->getY() * RenderSystem::SCREEN_SPACE_SCALE) - currentPos.y;
        transform = glm::translate(transform, glm::vec3(deltaX, deltaY, 0));
    }
  return transform;
}

int Camera::getScreenWidth() const {
  return screenWidth;
}

int Camera::getScreenHeight() const {
  return screenHeight;
}

// Setters

void Camera::updateScreenSize(int width, int height) {
  screenWidth = width;
  screenHeight = height;
  createPerspectiveMatrix();
}

void Camera::setFOV(float deg) {
  degRad = glm::radians(deg);
  createPerspectiveMatrix();
}

// entity attachment

void Camera::attachToEntity(std::shared_ptr<Entity> entity) {
    attachedToEntity = true;
    attachedEntity = std::move(entity);
}

bool Camera::isAttachedToEntity() const {
    return attachedToEntity;
}

void Camera::unattachFromEntity() {
    attachedToEntity = false;
    attachedEntity = nullptr;
}

// Internal functions

void Camera::createPerspectiveMatrix() {
  perspective = glm::perspective(
    degRad, 
    (double) screenWidth / screenHeight,
    0.1,
    100.0
  );
}
