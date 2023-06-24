#pragma once


class BoundingBox {
public:
    BoundingBox(int top_, int bottom_, int left_, int right_) :
        top(top_), bottom(bottom_), left(left_), right(right_) {};

    int top;
    int bottom;
    int left;
    int right;
};