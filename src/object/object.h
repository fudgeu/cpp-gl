#pragma once

#include <vector>
#include "../model/model.h"

class Object {
public:
    Object();
    explicit Object(Model model_);
    Object(Model model_, double x_, double y_);

    void setX(double x_);
    void setY(double y_);

    double getX() const;
    double getY() const;

    const Model& getModel() const;

private:
    Model model;
    double x;
    double y;
};