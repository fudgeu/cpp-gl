#pragma once

#include "entity.h"

class Player : public Entity {
private:
    Model model;
    double x;
    double y;
    double horizontalVelocity = 0;
    double verticalVelocity = 0;
    double walkingSpeed;
    bool gravity = true;
    bool jumping = false;

public:
    Player();
    Player(double x_, double y_, double walkingSpeed_);

    const Model &getModel() const override;
    void setModel(Model model_);

    void setX(double posX) override;
    void setY(double posY) override;

    double getX() const override;
    double getY() const override;

    void moveX(double amtX) override;
    void moveY(double amtY) override;

    void setVerticalVelocity(double velocity) override;
    void setHorizontalVelocity(double velocity) override;

    double getVerticalVelocity() override;
    double getHorizontalVelocity() override;

    double addVerticalVelocity(double amt) override;
    double addHorizontalVelocity(double amt) override;

    void walkLeft(double modifier);
    void walkRight(double modifier);

    void setGravity(bool gravity) override;
    bool hasGravity() override;

    void setJumping(bool jumping_) override;
    bool isJumping() override;

    double getWalkingSpeed();
};