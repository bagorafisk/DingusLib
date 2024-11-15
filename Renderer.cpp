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
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
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

void Renderer::drawRectangle(float x, float y, float width, float height, Color color, Shader& shader) {
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

void Renderer::drawCircle(float x, float y, float radius, Color color, Shader& shader, int segments) {
    // Convert color to normalized float values (0.0 to 1.0)
    float r = color.r / 255.0f;
    float g = color.g / 255.0f;
    float b = color.b / 255.0f;

    // Vertices for a circle: Center + perimeter points
    std::vector<float> vertices;

    // Center vertex (x, y, z, r, g, b)
    vertices.push_back(0.0f);  // x
    vertices.push_back(0.0f);  // y
    vertices.push_back(0.0f);  // z
    vertices.push_back(r);     // red
    vertices.push_back(g);     // green
    vertices.push_back(b);     // blue

    // Perimeter vertices
    for (int i = 0; i <= segments; ++i) {
        float angle = (2.0f * PI * i) / segments;  // Angle for this segment
        float px = cos(angle);
        float py = sin(angle);

        vertices.push_back(px);    // x
        vertices.push_back(py);    // y
        vertices.push_back(0.0f);  // z
        vertices.push_back(r);     // red
        vertices.push_back(g);     // green
        vertices.push_back(b);     // blue
    }

    // Create transform for the circle
    Transform transform;
    transform.position = glm::vec2(x, y);
    transform.scale = glm::vec2(radius, radius);

    // Set shader uniforms including transform
    shader.use();  // Use the shader
    setShaderUniforms(transform);

    // Update buffers
    glBindVertexArray(VAO);

    // Buffer vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Draw the circle as a triangle fan
    glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);

    // Clean up
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


bool Renderer::windowShouldClose() {
    return glfwWindowShouldClose(this->window);
}

void Renderer::clear(Color color) {
    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::beginDrawing() {
    this->frameStartTime = std::chrono::high_resolution_clock::now();
    glm::mat4 projection = glm::ortho(0.0f, (float)this->WIDTH, (float)-this->HEIGHT, 0.0f);
    defaultShader.use();
    defaultShader.setMat4("projection", projection);
}

void Renderer::endDrawing() {
    auto frameStartTime = std::chrono::high_resolution_clock::now();

    glfwSwapBuffers(this->window);
    glfwPollEvents();

    auto frameEndTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = frameEndTime - frameStartTime;
    double elapsedSeconds = elapsed.count();

    // Sleep to maintain target FPS
    if (elapsedSeconds < frameDuration) {
        std::this_thread::sleep_for(std::chrono::duration<double>(frameDuration - elapsedSeconds));
    }
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

void Renderer::setTargetFPS(int fps) {

}