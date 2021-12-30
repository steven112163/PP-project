#include "../include/surface.h"

Surface::Surface(int surface_size) {
    this->surface_size = surface_size;

    this->setup_surface();
}

unsigned int Surface::get_num_of_vertices(int state) const {
    return this->vertices[state].size();
}

const float *Surface::get_vertices(int state) const {
    return this->vertices[state].data();
}

float Surface::get_vertex(int index, int state) {
    return this->vertices[state][index];
}

void Surface::set_vertex(int index, float value, int state) {
    this->vertices[state][index] = value;
}

int Surface::get_surface_size() const {
    return this->surface_size;
}

void Surface::push_vertex(glm::vec3 &vertex) {
    this->vertices[0].push_back(vertex.x);
    this->vertices[0].push_back(vertex.y);
    this->vertices[0].push_back(vertex.z);
    this->vertices[1].push_back(vertex.x);
    this->vertices[1].push_back(vertex.y);
    this->vertices[1].push_back(vertex.z);
}

void Surface::setup_surface() {
    float step = 2.0f / (this->surface_size - 1);
    glm::vec3 vertex(0.0f, 0.0f, 0.0f), normal(0.0f, 1.0f, 0.0f);
    for (int row = 0; row < this->surface_size; row++) {
        vertex.z = -1 + row * step;
        for (int col = 0; col < this->surface_size; col++) {
            vertex.x = -1 + col * step;
            this->push_vertex(vertex);
            this->push_normal(normal);
        }
    }

    for (int row = 0; row < this->surface_size - 1; row++)
        for (int col = 0; col < this->surface_size - 1; col++)
            this->push_index(row * this->surface_size + col,
                             (row + 1) * this->surface_size + col,
                             row * this->surface_size + col + 1);

    for (int row = 1; row < this->surface_size; row++)
        for (int col = 0; col < this->surface_size - 1; col++)
            this->push_index(row * this->surface_size + col,
                             row * this->surface_size + col + 1,
                             (row - 1) * this->surface_size + col + 1);
}