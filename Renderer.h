#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include <iostream>
#include <vector>

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

    struct Transform {
        glm::vec2 position{ 0.0f, 0.0f };
        glm::vec2 scale{ 1.0f, 1.0f };
        float rotation{ 0.0f }; // in radians

        glm::mat4 getMatrix() const {
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, glm::vec3(position, 0.0f));
            transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
            transform = glm::scale(transform, glm::vec3(scale, 1.0f));
            return transform;
        }
    };


    Renderer(std::string title, int width, int height);
    ~Renderer();

    void handleFramebufferResize(int width, int height);

    void drawRectangle(float x, float y, float width, float height, Color color);
    void drawCircle(const Transform& transform, float radius, const Color& color, int segments = 32);
    void drawLine(glm::vec2 start, glm::vec2 end, float thickness, const Color& color);
    void drawPolygon(const std::vector<glm::vec2>& points, const Color& color, bool filled = true);

    bool windowShouldClose();

    void clear(Color color);

    void beginDrawing();

    void endDrawing();

private:
    // Helper function to set common shader uniforms
    void setShaderUniforms(const Transform& transform) {
        defaultShader.use();
        glm::mat4 model = transform.getMatrix();
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WIDTH),
            static_cast<float>(HEIGHT), 0.0f, -1.0f, 1.0f);
        defaultShader.setMat4("model", model);
        defaultShader.setMat4("projection", projection);
    }
};

#endif