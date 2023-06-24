#pragma once

#include "../model/model.h"

class Entity {
public:

    virtual const Model &getModel() const = 0;

    virtual void setX(double newX) = 0;
    virtual void setY(double newY) = 0;

    virtual double getX() const = 0;
    virtual double getY() const = 0;

    virtual void moveX(double amtX) = 0;
    virtual void moveY(double amtY) = 0;

    virtual void setVerticalVelocity(double velocity) = 0;
    virtual void setHorizontalVelocity(double velocity) = 0;

    virtual double getVerticalVelocity() = 0;
    virtual double getHorizontalVelocity() = 0;

    virtual double addVerticalVelocity(double amt) = 0;
    virtual double addHorizontalVelocity(double amt) = 0;

    virtual void setGravity(bool gravity) = 0;
    virtual bool hasGravity() = 0;

    virtual void setJumping(bool jumping) = 0;
    virtual bool isJumping() = 0;

    virtual ~Entity() = default;
};