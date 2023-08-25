#pragma once

#include <iostream>
#include <vector>

struct Color
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;
};

static const std::vector<Color> Colors = {
    {255, 50, 0, 255},
    {0, 200, 255, 255}
};

static Color colorLerp(const Color& col0, const Color& col1, const double& c)
{
    return {
             (uint8_t)(col0.r + (col1.r - col0.r) * c),
             (uint8_t)(col0.g + (col1.g - col0.g) * c),
             (uint8_t)(col0.b + (col1.b - col0.b) * c),
             255
           };
}

static Color linearGradient(const double& c)
{
    double stopLength = 1 / ((double) Colors.size() - 1);
    double ratio = c / stopLength;
    int stopIdx = (int)(c/stopLength);
    double v = (c - stopIdx * stopLength) / stopLength;

    if (stopIdx == Colors.size() - 1)
        return Colors.back();
    else if (stopIdx < Colors.size() - 1)
        return colorLerp(Colors[stopIdx], Colors[stopIdx + 1], v);
    else
        return Color();
}
