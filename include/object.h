#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Object {
public:
    Object();

    virtual unsigned int get_num_of_vertices() const = 0;

    virtual const float *get_vertices(int state = 0) const = 0;

    unsigned int get_num_of_indices() const;

    const int *get_indices() const;

    virtual unsigned int get_num_of_normals() const = 0;

    virtual const float *get_normals() const = 0;

protected:
    std::vector<int> indices;

    virtual void push_vertex(glm::vec3 &vertex, int idx = 0) = 0;

    void push_index(int a, int b, int c);

    virtual void push_normal(glm::vec3 &normal, int idx = 0) = 0;
};

#endif