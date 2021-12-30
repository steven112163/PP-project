#include "../include/util.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void bind_sphere(Sphere *sphere,
                 unsigned int &vertex_attribute_object,
                 unsigned int &vertex_buffer_object,
                 unsigned int &normal_buffer_object) {
    glGenVertexArrays(1, &vertex_attribute_object);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &normal_buffer_object);

    // Bind attribute
    glBindVertexArray(vertex_attribute_object);

    // Bind vertices
    bind_vertices(sphere, vertex_buffer_object);

    // Link attribute and vertex buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Bind normals
    bind_normals(sphere, normal_buffer_object);

    // Link attribute and normal buffer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
}

void bind_surface(Surface *surface,
                  unsigned int &vertex_attribute_object,
                  unsigned int &vertex_buffer_object,
                  unsigned int &element_buffer_object,
                  unsigned int &normal_buffer_object) {
    glGenVertexArrays(1, &vertex_attribute_object);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &element_buffer_object);
    glGenBuffers(1, &normal_buffer_object);

    // Bind attribute
    glBindVertexArray(vertex_attribute_object);

    // Bind vertices
    bind_vertices(surface, vertex_buffer_object);

    // Bind indices
    bind_indices(surface, element_buffer_object);

    // Link attribute and vertex buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Bind normals
    bind_normals(surface, normal_buffer_object);

    // Link attribute and normal buffer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
}

void bind_vertices(Object *object, unsigned int &vertex_buffer_object, int state) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * object->get_num_of_vertices(state), object->get_vertices(state),
                 GL_DYNAMIC_DRAW);
}

void bind_indices(Object *object, unsigned int &element_buffer_object) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * object->get_num_of_indices(), object->get_indices(),
                 GL_DYNAMIC_DRAW);
}

void bind_normals(Object *object, unsigned int &normal_buffer_object) {
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * object->get_num_of_normals(), object->get_normals(),
                 GL_DYNAMIC_DRAW);
}

void deallocate_and_terminate(Shader *shader,
                              unsigned int &sphere_vao,
                              unsigned int &sphere_vbo,
                              unsigned int &sphere_nbo,
                              unsigned int &surface_vao,
                              unsigned int &surface_vbo,
                              unsigned int &surface_ebo,
                              unsigned int &surface_nbo) {
    // De-allocate all resources
    glDeleteVertexArrays(1, &sphere_vao);
    glDeleteBuffers(1, &sphere_vbo);
    glDeleteBuffers(1, &sphere_nbo);
    glDeleteVertexArrays(1, &surface_vao);
    glDeleteBuffers(1, &surface_vbo);
    glDeleteBuffers(1, &surface_ebo);
    glDeleteBuffers(1, &surface_nbo);
    shader->destroy();

    // Terminate process
    glfwTerminate();
}