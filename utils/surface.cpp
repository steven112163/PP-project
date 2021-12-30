#include "../include/surface.h"

Surface::Surface(int surface_size) {
    this->state = 0;

    // For state = 0
    this->vertices.push_back(std::vector<float>());
    // For state = 1
    this->vertices.push_back(std::vector<float>());

    this->setup_surface(surface_size);
}

unsigned int Surface::get_num_of_vertices() const {
    return this->vertices[this->state].size();
}

const float *Surface::get_vertices() const {
    return this->vertices[this->state].data();
}

float Surface::get_vertex(int index) {
    return this->vertices[this->state][index];
}

void Surface::set_vertex(int index, float value) {
    this->vertices[this->state][index] = value;
}

void Surface::flip_state() {
    this->state = 1 - this->state;
}

void Surface::push_vertex(glm::vec3 &vertex) {
    this->vertices[0].push_back(vertex.x);
    this->vertices[0].push_back(vertex.y);
    this->vertices[0].push_back(vertex.z);
    this->vertices[1].push_back(vertex.x);
    this->vertices[1].push_back(vertex.y);
    this->vertices[1].push_back(vertex.z);
}

void Surface::setup_surface(int surface_size) {
    float step = 2.0f / (surface_size - 1);
    glm::vec3 vertex(0.0f, 0.0f, 0.0f), normal(0.0f, 1.0f, 0.0f);
    for (int row = 0; row < surface_size; row++) {
        vertex.z = -1 + row * step;
        for (int col = 0; col < surface_size; col++) {
            vertex.x = -1 + col * step;
            this->push_vertex(vertex);
            this->push_normal(normal);
        }
    }

    for (int row = 0; row < surface_size - 1; row++)
        for (int col = 0; col < surface_size - 1; col++)
            this->push_index(row * surface_size + col,
                             (row + 1) * surface_size + col,
                             row * surface_size + col + 1);

    for (int row = 1; row < surface_size; row++)
        for (int col = 0; col < surface_size - 1; col++)
            this->push_index(row * surface_size + col,
                             row * surface_size + col + 1,
                             (row - 1) * surface_size + col + 1);
}