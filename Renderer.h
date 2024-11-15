#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include <iostream>

struct Color {
    int r, g, b, a;
    Color(int red, int green, int blue, int alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {
    }
};

#define WHITE Color(255, 255, 255)

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

std::string glmMat4ToString(const glm::mat4& mat);

class Renderer {
public:
    GLFWwindow* window;
    unsigned int VBO, VAO, EBO;
    int WIDTH, HEIGHT;
    Shader defaultShader;

    Renderer(std::string title, int width, int height);
    ~Renderer();

    void handleFramebufferResize(int width, int height);

    void drawRectangle(float x, float y, float width, float height, Color color);

    bool windowShouldClose();

    void clear(Color color);

    void beginDrawing();

    void endDrawing();
};

#endif