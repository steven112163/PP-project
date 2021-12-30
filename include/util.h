#include "shader.h"
#include "sphere.h"
#include "surface.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void bind_sphere(Sphere *sphere,
                 unsigned int &vertex_attribute_object,
                 unsigned int &vertex_buffer_object,
                 unsigned int &normal_buffer_object);

void bind_surface(Surface *surface,
                  unsigned int &vertex_attribute_object,
                  unsigned int &vertex_buffer_object,
                  unsigned int &element_buffer_object,
                  unsigned int &normal_buffer_object);

void bind_vertices(Object *object, unsigned int &vertex_buffer_object, int state = 0);

void bind_indices(Object *object, unsigned int &element_buffer_object);

void bind_normals(Object *object, unsigned int &normal_buffer_object);

void deallocate_and_terminate(Shader *shader,
                              unsigned int &sphere_vao,
                              unsigned int &sphere_vbo,
                              unsigned int &sphere_nbo,
                              unsigned int &surface_vao,
                              unsigned int &surface_vbo,
                              unsigned int &surface_ebo,
                              unsigned int &surface_nbo);