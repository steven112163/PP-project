#include "../include/surface.h"

Surface::Surface(int surface_size) {
    this->surface_size = surface_size;

    this->setup_surface();
}

unsigned int Surface::get_num_of_vertices() const {
    return this->vertices_size;
}

const float *Surface::get_vertices(int state) const {
    return this->vertices[state];
}

int Surface::get_surface_size() const {
    return this->surface_size;
}

unsigned int Surface::get_num_of_normals() const {
    return this->vertices_size;
}

const float *Surface::get_normals() const {
    return this->normals;
}

void Surface::setup_surface() {
    float step = 2.0f / static_cast<float>(this->surface_size - 1);
    this->vertices_size = surface_size * surface_size * 3;
    this->vertices[0] = new float[this->vertices_size];
    this->vertices[1] = new float[this->vertices_size];
    this->normals = new float[this->vertices_size];

    glm::vec3 vertex(0.0f, 0.0f, 0.0f), normal(0.0f, 1.0f, 0.0f);

    for (int row = 0; row < this->surface_size; row++) {
        vertex.z = -1 + static_cast<float>(row) * step;
        for (int col = 0; col < this->surface_size; col++) {
            vertex.x = -1 + static_cast<float>(col) * step;

            int idx = (row * this->surface_size + col) * 3;
            this->push_vertex(vertex, idx);
            this->push_normal(normal, idx);
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

Surface::~Surface() {
    delete[] this->vertices[0];
    delete[] this->vertices[1];
    delete[] this->normals;
}

void Surface::push_vertex(glm::vec3 &vertex, int idx) {
    this->vertices[0][idx] = vertex.x;
    this->vertices[0][idx + 1] = vertex.y;
    this->vertices[0][idx + 2] = vertex.z;
    this->vertices[1][idx] = vertex.x;
    this->vertices[1][idx + 1] = vertex.y;
    this->vertices[1][idx + 2] = vertex.z;
}

void Surface::push_normal(glm::vec3 &normal, int idx) {
    this->normals[idx] = normal.x;
    this->normals[idx + 1] = normal.y;
    this->normals[idx + 2] = normal.z;
}