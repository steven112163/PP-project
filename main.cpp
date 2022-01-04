#include "include/util.h"
#include "include/shader.h"
#include "include/sphere.h"
#include "include/surface.h"
#include "include/ripple.h"
#include "include/CycleTimer.h"

#include <omp.h>

#include <cmath>
#include <cfloat>
#include <getopt.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.1415926
#define AIR_DENSITY 1.29
#define DRAG_COEFFICIENT 0.47
#define ACCELERATION -9.8


void usage(const char *program_name) {
    std::cout << "Usage: " << program_name << " [options]\n"
              << "Program Options:\n"
              << "  -s  --surface    <INT>    Surface size (default: 400)\n"
              << "  -i  --iter       <INT>    Max iteration (default: 100)\n"
              << "  -?  --help                This message\n";
}

int main(int argc, char **argv) {
    int surface_size = 400;
    int damp = surface_size / 5;
    int max_iter = 100;

    // Parse arguments
    int opt;
    static struct option long_options[] = {
            {"surface", 1, 0, 's'},
            {"iter",    1, 0, 'i'},
            {"help",    0, 0, 'h'},
            {0,         0, 0, 0}};
    while ((opt = getopt_long(argc, argv, "s:i:h", long_options, NULL)) != EOF) {
        switch (opt) {
            case 's': {
                surface_size = atoi(optarg);
                damp = surface_size / 5;
                break;
            }
            case 'i': {
                max_iter = atoi(optarg);
                break;
            }
            case 'h':
            default:
                usage(argv[0]);
                return 1;
        }
    }

    std::cout << "----------------------------------------------------------\n";
    std::cout << "Surface size: " << surface_size << "\n";
    std::cout << "Max iteration: " << max_iter << "\n";
    std::cout << "----------------------------------------------------------\n";

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
    Surface surface(surface_size);

    // Bind vertex buffer, element buffer, normal buffer and vertex attribute for surface
    unsigned int surface_vbo, surface_ebo, surface_nbo, surface_vao;
    bind_surface(&surface, surface_vao, surface_vbo, surface_ebo, surface_nbo);

    // Timing
    float delta_time = 0.0f;
    float last_frame = 0.0f;
    bool reached = false;

    // Start rendering
    int water_state = 0;
    int iter = 0;
    double start, end, avg_time = 0.0, min_time = DBL_MAX, max_time = DBL_MIN;
    while (!glfwWindowShouldClose(window) && iter < max_iter) {
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
            if (translation <= 0.0f && !reached) {
                reached = true;
                int surface_stride = 3 * surface_size;
                double coeff = -0.05 * 200 / surface_size;
                for (int z = 0; z < surface_size; z++) {
                    for (int x = 0; x < surface_size; x++) {
                        float x_coord = surface.vertices[water_state][surface_stride * z + 3 * x] * 1.3f;
                        float z_coord = surface.vertices[water_state][surface_stride * z + 3 * x + 2] * 1.3f;
                        float distance = std::sqrt(x_coord * x_coord + z_coord * z_coord);
                        if (distance <= 0.1f) {
                            surface.vertices[1 - water_state][surface_stride * z + 3 * x + 1] =
                                    coeff * std::cos(distance / 0.1f * 0.5 * PI) / std::sin(distance / 0.1f * 0.5 * PI);
                        }
                    }
                }
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
        if (reached) {
            start = CycleTimer::currentSeconds();
            ripple_serial(&surface, water_state, damp);
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
    std::cout << "Average execution time: " << avg_time * 1000 << " ms\n"
              << "Minimum execution time: " << min_time * 1000 << " ms\n"
              << "Maximum execution time: " << max_time * 1000 << " ms" << std::endl;

    // Deallocate and terminate
    deallocate_and_terminate(&shader,
                             sphere_vao, sphere_vbo, sphere_nbo,
                             surface_vao, surface_vbo, surface_ebo, surface_nbo);

    return 0;
}