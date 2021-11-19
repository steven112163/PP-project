#include "util.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void bind_attribute_and_buffers(Object *object,
                                unsigned int &vertex_attribute_object,
                                unsigned int &vertex_buffer_object,
                                unsigned int &normal_buffer_object) {
    glGenVertexArrays(1, &vertex_attribute_object);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &normal_buffer_object);

    // Bind attribute
    glBindVertexArray(vertex_attribute_object);

    // Bind vertices
    bind_vertices(object, vertex_buffer_object);

    // Link attribute and vertex buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Bind normals
    bind_normals(object, normal_buffer_object);

    // Link attribute and normal buffer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
}

void bind_vertices(Object *object, unsigned int &vertex_buffer_object) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * object->get_num_of_vertices(), object->get_vertices(),
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
                              unsigned int &surface_nbo) {
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
}