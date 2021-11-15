#include "utils/shader.h"
#include "utils/sphere.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ripple Simulation", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Enable depth check
    glEnable(GL_DEPTH_TEST);

    // Construct shader
    Shader shader("shaders/vertex_shader.cpp", "shaders/fragment_shader.cpp");

    // Create transformations
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT,
                                            0.1f,
                                            100.0f);

    // Set transformations
    shader.set_transformations(model, view, projection);

    // Setup sphere
    Sphere sphere(6);

    // Generate vertex buffer, and vertex attribute
    unsigned int vertex_buffer_object, vertex_attribute_object;
    glGenVertexArrays(1, &vertex_attribute_object);
    glGenBuffers(1, &vertex_buffer_object);

    // Bind buffers and attributes
    glBindVertexArray(vertex_attribute_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sphere.get_num_of_vertices(), sphere.get_vertices(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Unbind vertex buffer and vertex attribute
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Timing
    float delta_time = 0.0f;
    float last_frame = 0.0f;

    // Start rendering
    while (!glfwWindowShouldClose(window)) {
        // Get delta time
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        // Clear buffer
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw
        shader.use();
        glBindVertexArray(vertex_attribute_object);
        glDrawArrays(GL_TRIANGLES, 0, sphere.get_num_of_vertices());

        // Display result buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // De-allocate all resources
    glDeleteVertexArrays(1, &vertex_attribute_object);
    glDeleteBuffers(1, &vertex_buffer_object);
    shader.destroy();

    // Terminate process
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}