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

    unsigned int get_num_of_vertices() const;

    const float *get_vertices() const;

    float get_vertex(int index);

    void set_vertex(int index, float value);

    unsigned int get_num_of_normals() const;

    const float *get_normals() const;

    float get_normal(int index);

    void set_normal(int index, float value);

protected:
    std::vector<float> vertices;
    std::vector<float> normals;

    virtual void from_subdivision(int num_of_subdivision);

    virtual void divide_triangle(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, int num_of_subdivision);

    void push_vertex(glm::vec3 &vertex);

    void push_normal(glm::vec3 &normal);
};

#endif