#include "Renderer.h"
#include "Shader.h"

Renderer::Renderer(std::string title, int width, int height)
    : WIDTH(width), HEIGHT(height), defaultShader("default.vert", "default.frag") {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, title.c_str(), NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    // Link Renderer to the window
    glfwSetWindowUserPointer(window, this);

    // Set framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Renderer::drawRectangle(float x, float y, float width, float height, Color color) {
    float vertices[]{
        x, y, 1.0f,                  color.r / 255, color.g / 255, color.b / 255,
        x + width, y, 1.0f,          color.r / 255, color.g / 255, color.b / 255,
        x + width, y + height, 1.0f, color.r / 255, color.g / 255, color.b / 255,
        x, y + height, 1.0f,         color.r / 255, color.g / 255, color.b / 255
    };

    unsigned int indices[]{
        0, 2, 3,
        0, 1, 2
    };

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::mat4 projection = glm::ortho(0.0f, (float)this->WIDTH, 0.0f, (float)this->HEIGHT);

    this->defaultShader.use();

    this->defaultShader.setMat4("projection", projection);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void Renderer::handleFramebufferResize(int width, int height) {
    glViewport(0, 0, width, height);
    glm::mat4 projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
    defaultShader.use();
    defaultShader.setMat4("projection", projection);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    renderer->handleFramebufferResize(width, height);
}

bool Renderer::windowShouldClose() {
    return glfwWindowShouldClose(this->window);
}