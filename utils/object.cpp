#include "../include/object.h"

Object::Object() = default;

unsigned int Object::get_num_of_indices() const {
    return this->indices.size();
}

const int *Object::get_indices() const {
    return this->indices.data();
}

void Object::push_index(int a, int b, int c) {
    this->indices.push_back(a);
    this->indices.push_back(b);
    this->indices.push_back(c);
}