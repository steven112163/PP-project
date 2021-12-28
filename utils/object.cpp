#include "../include/object.h"

Object::Object() {}

unsigned int Object::get_num_of_vertices() const {
    return this->vertices.size();
}

const float *Object::get_vertices() const {
    return this->vertices.data();
}

float Object::get_vertex(int index) {
    return this->vertices[index];
}

void Object::set_vertex(int index, float value) {
    this->vertices[index] = value;
}

unsigned int Object::get_num_of_normals() const {
    return this->normals.size();
}

const float *Object::get_normals() const {
    return this->normals.data();
}

float Object::get_normal(int index) {
    return this->normals[index];
}

void Object::set_normal(int index, float value) {
    this->normals[index] = value;
}

void Object::from_subdivision(int num_of_subdivision) {}

void Object::divide_triangle(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, int num_of_subdivision) {}

void Object::push_vertex(glm::vec3 &vertex) {
    this->vertices.push_back(vertex.x);
    this->vertices.push_back(vertex.y);
    this->vertices.push_back(vertex.z);
}

void Object::push_normal(glm::vec3 &normal) {
    this->normals.push_back(normal.x);
    this->normals.push_back(normal.y);
    this->normals.push_back(normal.z);
}