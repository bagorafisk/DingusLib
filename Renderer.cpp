#include "Renderer.h"
#include "Shader.h"

Renderer::Renderer(std::string title, int width, int height)
    : WIDTH(width), HEIGHT(height) {

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

    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glDisable(GL_DEPTH_TEST);

    try {
        defaultShader = Shader("default.vert", "default.frag");
    }
    catch (const std::exception& e) {
        std::cerr << "Shader initialization failed: " << e.what() << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Initialize buffers (only once)
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    // Configure OpenGL buffers and attributes
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO for now
}

Renderer::~Renderer() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Renderer::drawRectangle(float x, float y, float width, float height, Color color) {
    // Set up rectangle vertices and indices
    float vertices[] = {
        x, y, 1.0f, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f,
        x + width, y, 1.0f, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f,
        x + width, y + height, 1.0f, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f,
        x, y + height, 1.0f, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f
    };

    unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

    glBindVertexArray(VAO);
    // Update vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Update element buffer (indices)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //// Use shader and set projection matrix
    defaultShader.use();
    glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, 0.0f,(float)HEIGHT);
    defaultShader.setMat4("projection", projection);

    // Draw the rectangle
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);  // Unbind VAO
}

void Renderer::handleFramebufferResize(int width, int height) {
    glViewport(0, 0, width, height);
    glm::mat4 projection = glm::ortho(0.0f, (float)this->WIDTH, (float)this->HEIGHT, 0.0f);
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

void Renderer::clear(Color color) {
    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::beginDrawing() {
    glm::mat4 projection = glm::ortho(0.0f, (float)this->WIDTH, (float)-this->HEIGHT, 0.0f);
    defaultShader.use();
    defaultShader.setMat4("projection", projection);
}

void Renderer::endDrawing() {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

std::string glmMat4ToString(const glm::mat4& mat) {
    std::ostringstream oss;
    oss << "[\n";
    for (int i = 0; i < 4; ++i) {
        oss << "[ ";
        for (int j = 0; j < 4; ++j) {
            oss << mat[i][j] << " ";
        }
        oss << "]\n";
    }
    oss << "]";
    return oss.str();
}