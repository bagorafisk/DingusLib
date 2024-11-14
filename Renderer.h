#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

struct Color {
    float r, g, b;
};

class Renderer {
public:
    GLFWwindow* window;

    Renderer(const char* title, int width, int height);

    void drawRectangle(float x, float y, float width, float height, Color color);
};