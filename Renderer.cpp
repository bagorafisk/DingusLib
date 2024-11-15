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

    // Create and set up buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Load shaders
    try {
        defaultShader = Shader("Shaders/default.vert", "Shaders/default.frag");
    }
    catch (const std::exception& e) {
        std::cerr << "Shader initialization failed: " << e.what() << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

Renderer::~Renderer() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Renderer::drawRectangle(float x, float y, float width, float height, Color color) {
    // Convert color to normalized float values (0.0 to 1.0)
    float r = color.r / 255.0f;
    float g = color.g / 255.0f;
    float b = color.b / 255.0f;

    // Vertices for a rectangle centered at origin
    float vertices[] = {
        // Positions        // Colors
        -0.5f, -0.5f, 0.0f,   r, g, b,  // Bottom left
         0.5f, -0.5f, 0.0f,   r, g, b,  // Bottom right
         0.5f,  0.5f, 0.0f,   r, g, b,  // Top right
        -0.5f,  0.5f, 0.0f,   r, g, b   // Top left
    };

    unsigned int indices[] = {
        0, 1, 2,  // First triangle
        2, 3, 0   // Second triangle
    };

    // Create transform for the rectangle
    Transform transform;
    transform.position = glm::vec2(x + width / 2, y + height / 2);
    transform.scale = glm::vec2(width, height);

    // Set shader uniforms including transform
    Shader shader("Shaders/default.vert", "Shaders/default.frag");
    shader.use();  // Make sure we're using the right shader
    setShaderUniforms(transform);

    // Update buffers
    glBindVertexArray(VAO);

    // Buffer vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Buffer index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Draw the rectangle
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Clean up
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::drawCircle(const Transform& transform, float radius, const Color& color, int segments) {
    segments = std::max(segments, 3);
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Center vertex
    vertices.push_back(0.0f);  // x
    vertices.push_back(0.0f);  // y
    vertices.push_back(0.0f);  // z
    vertices.push_back(color.r / 255.0f);  // r
    vertices.push_back(color.g / 255.0f);  // g
    vertices.push_back(color.b / 255.0f);  // b

    // Generate circle vertices
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * glm::pi<float>() * i / segments;
        float x = cos(angle);
        float y = sin(angle);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
        vertices.push_back(color.r / 255.0f);
        vertices.push_back(color.g / 255.0f);
        vertices.push_back(color.b / 255.0f);

        if (i < segments) {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }
    }

    // Scale the transform to match the radius
    Transform scaledTransform = transform;
    scaledTransform.scale *= glm::vec2(radius);

    // Set uniforms and bind buffers
    setShaderUniforms(scaledTransform);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::drawLine(glm::vec2 start, glm::vec2 end, float thickness, const Color& color) {
    glm::vec2 direction = end - start;
    float length = glm::length(direction);
    float angle = atan2(direction.y, direction.x);

    Transform transform;
    transform.position = start + direction * 0.5f;
    transform.rotation = angle;
    transform.scale = glm::vec2(length, thickness);

    //drawRectangle(transform, glm::vec2(1.0f), color);
}

void Renderer::drawPolygon(const std::vector<glm::vec2>& points, const Color& color, bool filled) {
    if (points.size() < 3) return;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Generate vertices
    for (const auto& point : points) {
        vertices.push_back(point.x);
        vertices.push_back(point.y);
        vertices.push_back(0.0f);
        vertices.push_back(color.r / 255.0f);
        vertices.push_back(color.g / 255.0f);
        vertices.push_back(color.b / 255.0f);
    }

    // Generate indices
    if (filled) {
        // Triangulate the polygon (simple fan triangulation - assumes convex polygon)
        for (size_t i = 1; i < points.size() - 1; ++i) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }
    else {
        // Generate line loop indices
        for (size_t i = 0; i < points.size(); ++i) {
            indices.push_back(i);
            indices.push_back((i + 1) % points.size());
        }
    }

    Transform transform;  // Identity transform
    setShaderUniforms(transform);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

    glDrawElements(filled ? GL_TRIANGLES : GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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