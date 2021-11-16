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
    glfwWindowHint(GLFW_SAMPLES, 4);

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

    // Enable multisampling
    glEnable(GL_MULTISAMPLE);

    // Construct shader
    Shader shader("shaders/vertex_shader.cpp", "shaders/fragment_shader.cpp");

    // Set transformations
    glm::mat4 model(1.0f);
    glm::vec3 camera_position(0.0f, 0.0f, 3.0f);
    glm::mat4 view = glm::lookAt(camera_position,
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT,
                                            0.1f,
                                            100.0f);
    glm::mat3 normal_matrix = glm::mat3(glm::transpose(glm::inverse(model)));
    shader.set_transformations(model, view, projection, normal_matrix);
    shader.set_camera_position(camera_position);

    // Set light
    glm::vec3 light_direction(1.0f, -1.0f, -1.0f);
    glm::vec3 ambient_light_color(0.0f, 0.0f, 0.0f);
    glm::vec3 diffuse_light_color(1.0f, 1.0f, 1.0f);
    glm::vec3 specular_light_color(1.0f, 1.0f, 1.0f);
    shader.set_light(light_direction, ambient_light_color, diffuse_light_color, specular_light_color);

    // Set material
    int red = 102, green = 194, blue = 255;
    glm::vec3 ambient_material_color(red / 255.0f, green / 255.0f, blue / 255.0f);
    glm::vec3 diffuse_material_color(red / 255.0f, green / 255.0f, blue / 255.0f);
    glm::vec3 specular_material_color(1.0f, 1.0f, 1.0f);
    glm::float32 shininess(200.0f);
    shader.set_material(ambient_material_color, diffuse_material_color, specular_material_color, shininess);

    // Setup sphere
    Sphere sphere(6);

    // Generate vertex buffer, normal buffer and vertex attribute
    unsigned int vertex_buffer_object, normal_buffer_object, vertex_attribute_object;
    glGenVertexArrays(1, &vertex_attribute_object);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &normal_buffer_object);

    // Bind attributes
    glBindVertexArray(vertex_attribute_object);

    // Bind vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sphere.get_num_of_vertices(), sphere.get_vertices(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Bind normals
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sphere.get_num_of_normals(), sphere.get_normals(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);

    // Unbind buffer and vertex attribute
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