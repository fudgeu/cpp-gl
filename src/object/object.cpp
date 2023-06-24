#include "object.h"

#include <utility>

Object::Object(Model model_):
    model(std::move(model_)), x(0), y(0) {};

Object::Object(Model model_, double x_, double y_) :
    model(std::move(model_)), x(x_), y(y_) {};

void Object::setX(double x_) {
    x = x_;
}

void Object::setY(double y_) {
    y = y_;
}

double Object::getX() const {
    return x;
}

double Object::getY() const {
    return y;
}

const Model& Object::getModel() const {
    return model;
}
