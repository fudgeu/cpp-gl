#include "player.h"

#include <utility>

Player::Player():
        x(0), y(0), walkingSpeed(60) {}

Player::Player(double x_, double y_, double walkingSpeed_):
        x(x_), y(y_), walkingSpeed(walkingSpeed_) {}

const Model &Player::getModel() const {
    return model;
}

void Player::setModel(Model model_) {
    model = std::move(model_);
}

void Player::setX(double x_) {
    x = x_;
}

void Player::setY(double y_) {
    y = y_;
}

double Player::getX() const {
    return x;
}

double Player::getY() const {
    return y;
}

void Player::moveX(double amtX) {
    x += amtX;
}

void Player::moveY(double amtY) {
    y += amtY;
}

void Player::walkLeft(double modifier) {
    x -= walkingSpeed * modifier;
}

void Player::walkRight(double modifier) {
    x += walkingSpeed * modifier;
}

void Player::setGravity(bool gravity_) {
    gravity = gravity_;
}

bool Player::hasGravity() {
    return gravity;
}

void Player::setVerticalVelocity(double velocity) {
    verticalVelocity = velocity;
}

void Player::setHorizontalVelocity(double velocity) {
    horizontalVelocity = velocity;
}

double Player::getVerticalVelocity() {
    return verticalVelocity;
}

double Player::getHorizontalVelocity() {
    return horizontalVelocity;
}

double Player::addVerticalVelocity(double amt) {
    verticalVelocity += amt;
    return verticalVelocity;
}

double Player::addHorizontalVelocity(double amt) {
    horizontalVelocity += amt;
    return horizontalVelocity;
}

void Player::setJumping(bool jumping_) {
    jumping = jumping_;
}

bool Player::isJumping() {
    return jumping;
}

double Player::getWalkingSpeed() {
    return walkingSpeed;
}
