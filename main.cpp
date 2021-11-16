#include "utils/shader.h"
#include "utils/sphere.h"
#include "utils/surface.h"

#include <cmath>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.1415926

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
    glm::mat4 sphere_model(0.05f);
    sphere_model = glm::translate(sphere_model, glm::vec3(0.0f, 1.5f, 0.0f));
    glm::mat3 surface_model(1.3f);

    glm::vec3 camera_position(2.0f, 3.0f, 4.0f);
    glm::mat4 view = glm::lookAt(camera_position,
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT,
                                            0.1f,
                                            100.0f);

    glm::mat3 sphere_normal_matrix = glm::mat3(glm::transpose(glm::inverse(sphere_model)));
    glm::mat3 surface_normal_matrix = glm::mat3(glm::transpose(glm::inverse(surface_model)));

    shader.set_transformations(sphere_model, view, projection, sphere_normal_matrix);
    shader.set_camera_position(camera_position);

    // Set light
    glm::vec3 light_direction(-3.0f, -2.0f, -1.0f);
    glm::vec3 ambient_light_color(0.05f, 0.05f, 0.05f);
    glm::vec3 diffuse_light_color(1.0f, 1.0f, 1.0f);
    glm::vec3 specular_light_color(1.0f, 1.0f, 1.0f);
    shader.set_light(light_direction, ambient_light_color, diffuse_light_color, specular_light_color);

    // Set material
    int red = 102, green = 194, blue = 255;
    glm::vec3 ambient_material_color(red / 255.0f, green / 255.0f, blue / 255.0f);
    glm::vec3 diffuse_material_color(red / 255.0f, green / 255.0f, blue / 255.0f);
    glm::vec3 specular_material_color(1.0f, 1.0f, 1.0f);
    glm::float32 shininess(100.0f);
    shader.set_material(ambient_material_color, diffuse_material_color, specular_material_color, shininess);

    // Setup sphere
    Sphere sphere(6);

    // Generate vertex buffer, normal buffer and vertex attribute for sphere
    unsigned int sphere_vbo, sphere_nbo, sphere_vao;
    glGenVertexArrays(1, &sphere_vao);
    glGenBuffers(1, &sphere_vbo);
    glGenBuffers(1, &sphere_nbo);

    // Bind sphere attributes
    glBindVertexArray(sphere_vao);

    // Bind sphere vertices
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sphere.get_num_of_vertices(), sphere.get_vertices(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Bind sphere normals
    glBindBuffer(GL_ARRAY_BUFFER, sphere_nbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sphere.get_num_of_normals(), sphere.get_normals(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);

    // Setup surface
    Surface surface(6);

    // Generate vertex buffer, normal buffer and vertex attribute for surface
    unsigned int surface_vbo, surface_nbo, surface_vao;
    glGenVertexArrays(1, &surface_vao);
    glGenBuffers(1, &surface_vbo);
    glGenBuffers(1, &surface_nbo);

    // Bind surface attributes
    glBindVertexArray(surface_vao);

    // Bind surface vertices
    glBindBuffer(GL_ARRAY_BUFFER, surface_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * surface.get_num_of_vertices(), surface.get_vertices(),
                 GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Bind surface normals
    glBindBuffer(GL_ARRAY_BUFFER, surface_nbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * surface.get_num_of_normals(), surface.get_normals(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);

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

        // Draw sphere
        shader.set_model(sphere_model);
        shader.set_normal_matrix(sphere_normal_matrix);
        shader.use();
        glBindVertexArray(sphere_vao);
        glDrawArrays(GL_TRIANGLES, 0, sphere.get_num_of_vertices());

        // Draw surface
        shader.set_model(surface_model);
        shader.set_normal_matrix(surface_normal_matrix);
        shader.use();
        glBindVertexArray(surface_vao);
        for (int idx = 0; idx < surface.get_num_of_vertices(); idx += 3) {
            float x = surface.get_vertex(idx);
            float z = surface.get_vertex(idx + 2);
            float distance = std::sqrt(std::pow(x, 2) + std::pow(z, 2));
            float radian = 16 * (distance / std::sqrt(2) - current_frame / 7) * PI;
            surface.set_vertex(idx + 1, 0.05 * std::sin(radian));

            if (x == 0.0f && z == 0.0f)
                continue;

            glm::vec3 direction = glm::normalize(glm::vec3(x, 0.0f, z));
            glm::vec3 up(0.0f, 1.0f, 0.0f);
            glm::vec3 tangent = glm::normalize(glm::cross(direction, up));
            glm::vec3 derivative = glm::normalize(
                    glm::vec3(x,
                              0.05 * std::cos(radian) * distance,
                              z)
                    );
            glm::vec3 normal = glm::normalize(glm::cross(tangent, derivative));
            surface.set_normal(idx, normal.x);
            surface.set_normal(idx + 1, normal.y);
            surface.set_normal(idx + 2, normal.z);
        }
        glBindBuffer(GL_ARRAY_BUFFER, surface_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * surface.get_num_of_vertices(), surface.get_vertices(),
                     GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, surface_nbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * surface.get_num_of_normals(), surface.get_normals(),
                     GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, surface.get_num_of_vertices());

        // Display result buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // De-allocate all resources
    glDeleteVertexArrays(1, &sphere_vao);
    glDeleteBuffers(1, &sphere_vbo);
    glDeleteBuffers(1, &sphere_nbo);
    glDeleteVertexArrays(1, &surface_vao);
    glDeleteBuffers(1, &surface_vbo);
    glDeleteBuffers(1, &surface_nbo);
    shader.destroy();

    // Terminate process
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}