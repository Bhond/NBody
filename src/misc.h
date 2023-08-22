#pragma once

#include <iostream>
#include <vector>

struct Color
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;
    double stop = 0;
};

static const std::vector<Color> Colors = {
    {127, 0, 255, 255, 0},
    {255, 0, 0, 255  , 0.25},
    {0, 255, 0, 255  , 0.75},
    {255, 255, 255, 255, 1 }

    //{5, 241, 218},
    //{255, 80, 0},
    //{213, 183, 122},
    //{189, 183, 107},
    //{66, 100, 127},
    //{237, 203, 98},
    //{237, 237, 237}
};

static Color colorLerp(Color col0, Color col1, double c)
{
    return {
             (uint8_t)(col0.r + (col1.r - col0.r) * c),
             (uint8_t)(col0.g + (col1.g - col0.g) * c),
             (uint8_t)(col0.b + (col1.b - col0.b) * c),
             255
           };
}

static Color linearGradient(double c)
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
