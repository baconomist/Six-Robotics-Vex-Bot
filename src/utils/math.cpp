//
// Created by Lucas on 11/15/2019.
//

#include "math.h"
#include "vector2.h"

float clamp(float a, float min, float max)
{
    if (a < min)
        return min;
    if (a > max)
        return max;
    return a;
}

float clamp01(float a)
{
    return clamp(a, 0, 1);
}

float lerp(float a, float min, float max)
{
    return clamp01((a - min) / max);
}