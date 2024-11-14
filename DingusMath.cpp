#include "DingusMath.h"

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::length() {
    return hypotf(this->x, this->y);
}

float Vector2::angle() {
    return atan2f(this->y, this->x);
}

Vector2 Vector2::clone() {
    return Vector2(this->x, this->y);
}

void Vector2::normalize() {
    float len = this->length();
    if (len != 0) {
        this->x /= len;
        this->y /= len;
    }
}

Vector2 Vector2::toNormalized() {
    float len = this->length();
    return len != 0 ? Vector2(this->x / len, this->y / len) : Vector2(0, 0);
}

void Vector2::add(Vector2 value) {
    this->x += value.x;
    this->y += value.y;
}

Vector2 Vector2::toAdded(Vector2 value) {
    return Vector2(this->x + value.x, this->y + value.y);
}

void Vector2::subtract(Vector2 value) {
    this->x -= value.x;
    this->y -= value.y;
}

Vector2 Vector2::toSubtracted(Vector2 value) {
    return Vector2(this->x - value.x, this->y - value.y);
}

void Vector2::multiply(Vector2 value) {
    this->x *= value.x;
    this->y *= value.y;
}

Vector2 Vector2::toMultiplied(Vector2 value) {
    return Vector2(this->x * value.x, this->y * value.y);
}

void Vector2::divide(Vector2 value) {
    this->x /= value.x;
    this->y /= value.y;
}

Vector2 Vector2::toDivided(Vector2 value) {
    return Vector2(this->x / value.x, this->y / value.y);
}

void Vector2::scale(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
}

Vector2 Vector2::toScaled(float scalar) {
    return Vector2(this->x * scalar, this->y * scalar);
}

float Vector2::distanceTo(Vector2 value) {
    return hypotf(this->x - value.x, this->y - value.y);
}

Vector2 Vector2::directionTo(Vector2 value) {
    const float a = atan2f(value.y - this->y, value.x - this->x);
    return Vector2(cosf(a), sinf(a));
}

float Vector2::dot(Vector2 value) {
    return this->x * value.x + this->y * value.y;
}

std::string Vector2::toString() {
    return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
}
