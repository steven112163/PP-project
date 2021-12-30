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

    virtual const float *get_vertices() const = 0;

    virtual float get_vertex(int index) = 0;

    virtual void set_vertex(int index, float value) = 0;

    unsigned int get_num_of_indices() const;

    const int *get_indices() const;

    unsigned int get_num_of_normals() const;

    const float *get_normals() const;

    float get_normal(int index);

    void set_normal(int index, float value);

protected:
    std::vector<int> indices;
    std::vector<float> normals;

    virtual void push_vertex(glm::vec3 &vertex) = 0;

    void push_index(int a, int b, int c);

    void push_normal(glm::vec3 &normal);
};

#endif