#include "sphere.h"

Sphere::Sphere(int num_of_subdivision) {
    this->sphere_from_subdivision(num_of_subdivision);
}

unsigned int Sphere::get_num_of_vertices() const {
    return this->vertices.size();
}

const float *Sphere::get_vertices() const {
    return this->vertices.data();
}

unsigned int Sphere::get_num_of_normals() const {
    return this->normals.size();
}

const float *Sphere::get_normals() const {
    return this->normals.data();
}

void Sphere::sphere_from_subdivision(int num_of_subdivision) {
    glm::vec3 a(0.0f, 0.0f, -1.0f);
    glm::vec3 b(0.0f, 0.942809f, 0.333333f);
    glm::vec3 c(-0.816497f, -0.471405f, 0.333333f);
    glm::vec3 d(0.816497f, -0.471405f, 0.333333f);

    this->divide_triangle(a, b, c, num_of_subdivision);
    this->divide_triangle(d, c, b, num_of_subdivision);
    this->divide_triangle(a, d, b, num_of_subdivision);
    this->divide_triangle(a, c, d, num_of_subdivision);
}

void Sphere::divide_triangle(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, int num_of_subdivision) {
    if (num_of_subdivision > 0) {
        glm::vec3 ab = glm::normalize(glm::mix(a, b, 0.5f));

        glm::vec3 ac = glm::normalize(glm::mix(a, c, 0.5f));

        glm::vec3 bc = glm::normalize(glm::mix(b, c, 0.5f));

        this->divide_triangle(a, ab, ac, num_of_subdivision - 1);
        this->divide_triangle(ab, b, bc, num_of_subdivision - 1);
        this->divide_triangle(bc, c, ac, num_of_subdivision - 1);
        this->divide_triangle(ab, bc, ac, num_of_subdivision - 1);
    } else {
        // Add 3 vertices to the array
        this->push_vertex(a);
        this->push_vertex(b);
        this->push_vertex(c);

        // Normals are the same as the vertices for a sphere
        this->push_normal(a);
        this->push_normal(b);
        this->push_normal(c);
    }
}

void Sphere::push_vertex(glm::vec3 &vertex) {
    this->vertices.push_back(vertex.x);
    this->vertices.push_back(vertex.y);
    this->vertices.push_back(vertex.z);
}

void Sphere::push_normal(glm::vec3 &normal) {
    this->normals.push_back(normal.x);
    this->normals.push_back(normal.y);
    this->normals.push_back(normal.z);
}