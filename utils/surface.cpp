#include "surface.h"

Surface::Surface(int num_of_subdivision) {
    this->surface_from_subdivision(num_of_subdivision);
}

unsigned int Surface::get_num_of_vertices() const {
    return this->vertices.size();
}

const float *Surface::get_vertices() const {
    return this->vertices.data();
}

unsigned int Surface::get_num_of_normals() const {
    return this->normals.size();
}

const float *Surface::get_normals() const {
    return this->normals.data();
}

void Surface::surface_from_subdivision(int num_of_subdivision) {
    glm::vec3 a(-1.0f, 0.0f, -1.0f);
    glm::vec3 b(-1.0f, 0.0f, 1.0f);
    glm::vec3 c(1.0f, 0.0f, 1.0f);
    glm::vec3 d(1.0f, 0.0f, -1.0f);

    this->divide_triangle(a, b, c, num_of_subdivision);
    this->divide_triangle(a, c, d, num_of_subdivision);
}

void Surface::divide_triangle(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, int num_of_subdivision) {
    if (num_of_subdivision > 0) {
        glm::vec3 ab = glm::mix(a, b, 0.5f);

        glm::vec3 ac = glm::mix(a, c, 0.5f);

        glm::vec3 bc = glm::mix(b, c, 0.5f);

        this->divide_triangle(a, ab, ac, num_of_subdivision - 1);
        this->divide_triangle(ab, b, bc, num_of_subdivision - 1);
        this->divide_triangle(bc, c, ac, num_of_subdivision - 1);
        this->divide_triangle(ab, bc, ac, num_of_subdivision - 1);
    } else {
        // Add 3 vertices to the array
        this->push_vertex(a);
        this->push_vertex(b);
        this->push_vertex(c);

        // Normals are the same
        glm::vec3 normal(0.0f, 1.0f, 0.0f);
        this->push_normal(normal);
        this->push_normal(normal);
        this->push_normal(normal);
    }
}

void Surface::push_vertex(glm::vec3 &vertex) {
    this->vertices.push_back(vertex.x);
    this->vertices.push_back(vertex.y);
    this->vertices.push_back(vertex.z);
}

void Surface::push_normal(glm::vec3 &normal) {
    this->normals.push_back(normal.x);
    this->normals.push_back(normal.y);
    this->normals.push_back(normal.z);
}