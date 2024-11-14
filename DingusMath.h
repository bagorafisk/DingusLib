#pragma once

#include <cmath>
#include <string>

class Vector2 {
public:
    float x, y;

    Vector2(float x, float y);

    float length();
    float angle();
    Vector2 clone();
    void normalize();
    Vector2 toNormalized();

    void add(Vector2 value);
    Vector2 toAdded(Vector2 value);

    void subtract(Vector2 value);
    Vector2 toSubtracted(Vector2 value);

    void multiply(Vector2 value);
    Vector2 toMultiplied(Vector2 value);

    void divide(Vector2 value);
    Vector2 toDivided(Vector2 value);

    void scale(float scalar);
    Vector2 toScaled(float scalar);

    float distanceTo(Vector2 value);
    Vector2 directionTo(Vector2 value);
    float dot(Vector2 value);

    std::string toString();
};