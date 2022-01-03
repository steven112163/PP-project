#include "include/util.h"
#include "include/shader.h"
#include "include/sphere.h"
#include "include/surface.h"
#include "include/ripple.h"
#include "include/CycleTimer.h"

#include <cmath>
#include <cfloat>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.1415926
#define AIR_DENSITY 1.29
#define DRAG_COEFFICIENT 0.47
#define ACCELERATION -9.8
#define SURFACE_SIZE 400
#define MAX_ITER 100


int main(int argc, char **argv) {
    int thread_count = -1;
    bool useOmp = false;

    // OpenMP thread settings
    if (argc == 2) {
        thread_count = atoi(argv[1]);
        std::cout << "----------------------------------------------------------\n";
        std::cout << "Max system threads = " << omp_get_max_threads() << " \n";
        std::cout << "Running with " << thread_count << " threads" << std::endl;
        std::cout << "----------------------------------------------------------\n";
        omp_set_num_threads(thread_count);
    }

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

    // Set translation, scalar, and velocity
    float translation = 1.5f;
    float scalar = 0.2f;
    float velocity = 0.0f;

    // Set transformations
    glm::mat4 sphere_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, translation, 0.0f));
    sphere_model = glm::scale(sphere_model, glm::vec3(scalar));

    glm::mat4 surface_model = glm::scale(glm::mat4(1.0f), glm::vec3(1.3f, 1.3f, 1.3f));

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

    // Bind vertex buffer, normal buffer and vertex attribute for sphere
    unsigned int sphere_vbo, sphere_nbo, sphere_vao;
    bind_sphere(&sphere, sphere_vao, sphere_vbo, sphere_nbo);

    // Setup surface
    Surface surface(SURFACE_SIZE);

    // Bind vertex buffer, element buffer, normal buffer and vertex attribute for surface
    unsigned int surface_vbo, surface_ebo, surface_nbo, surface_vao;
    bind_surface(&surface, surface_vao, surface_vbo, surface_ebo, surface_nbo);

    // Timing
    float delta_time = 0.0f;
    float last_frame = 0.0f;
    float reached_time = 0.0f;

    // Start rendering
    int water_state = 0;
    int iter = 0;
    double start, end, avg_time = 0.0, min_time = DBL_MAX, max_time = DBL_MIN;
    while (!glfwWindowShouldClose(window) && iter < MAX_ITER) {
        // Get delta time
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        // Clear buffer
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate sphere's location
        if (current_frame > 2 && translation > -0.3) {
            // Calculate new translation
            float drag = 0.5 * AIR_DENSITY * std::pow(velocity, 2) * DRAG_COEFFICIENT * PI * std::pow(scalar, 2);
            float current_velocity = velocity + drag * delta_time + ACCELERATION * delta_time;
            translation += (current_velocity + velocity) / 2.0f * delta_time;

            // Check if the sphere reaches the surface
            if (translation <= 0.0f && reached_time == 0.0f) {
                reached_time = current_frame;
                surface.set_vertex(3 * SURFACE_SIZE * (int) (SURFACE_SIZE / 2) + 3 * (int) (SURFACE_SIZE / 2) + 1,
                                   -0.5f,
                                   1 - water_state);
            }

            // Get new transformation
            sphere_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, translation, 0.0f));
            sphere_model = glm::scale(sphere_model, glm::vec3(scalar));

            velocity = current_velocity;
        }

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
        if (reached_time != 0.0f) {
            start = CycleTimer::currentSeconds();
            if (thread_count == -1) {
                ripple_serial(&surface, water_state);
            } else {
                ripple_omp(&surface, water_state);
            }
            end = CycleTimer::currentSeconds();
            avg_time = (avg_time * iter + end - start) / (iter + 1);
            min_time = std::min(min_time, end - start);
            max_time = std::max(max_time, end - start);

            bind_vertices(&surface, surface_vbo, water_state);
            bind_normals(&surface, surface_nbo);
            iter++;
        }
        glDrawElements(GL_TRIANGLES, surface.get_num_of_indices(), GL_UNSIGNED_INT, 0);

        // Display result buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    std::cout << "Average execution time: " << avg_time << "\n"
              << "Minimum execution time: " << min_time << "\n"
              << "Maximum execution time: " << max_time << std::endl;

    // Deallocate and terminate
    deallocate_and_terminate(&shader,
                             sphere_vao, sphere_vbo, sphere_nbo,
                             surface_vao, surface_vbo, surface_ebo, surface_nbo);

    return 0;
}