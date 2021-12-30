#include "../include/object.h"

Object::Object() {}

unsigned int Object::get_num_of_indices() const {
    return this->indices.size();
}

const int *Object::get_indices() const {
    return this->indices.data();
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

void Object::push_index(int a, int b, int c) {
    this->indices.push_back(a);
    this->indices.push_back(b);
    this->indices.push_back(c);
}

void Object::push_normal(glm::vec3 &normal) {
    this->normals.push_back(normal.x);
    this->normals.push_back(normal.y);
    this->normals.push_back(normal.z);
}