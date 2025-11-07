#pragma once
#include <string>
#include <vector>

class color {
public:
    float r, g, b, a;

    color(float red, float green, float blue, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) {}
};