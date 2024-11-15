#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include <iostream>

struct Color {
    float r, g, b;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Renderer {
public:
    GLFWwindow* window;
    unsigned int VBO, VAO, EBO;
    int WIDTH, HEIGHT;
    Shader defaultShader;

    Renderer(std::string title, int width, int height);

    void handleFramebufferResize(int width, int height);

    void drawRectangle(float x, float y, float width, float height, Color color);

    bool windowShouldClose();
};

#endif