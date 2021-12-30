#ifndef SPHERE_H
#define SPHERE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "object.h"

class Sphere : public Object {
public:
    Sphere(int num_of_subdivision = 6);

    unsigned int get_num_of_vertices(int state = 0) const;

    const float *get_vertices(int state = 0) const;

    float get_vertex(int index, int state = 0);

    void set_vertex(int index, float value, int state = 0);

protected:
    std::vector<float> vertices;

    void push_vertex(glm::vec3 &vertex);

    void from_subdivision(int num_of_subdivision);

    void divide_triangle(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, int num_of_subdivision);
};

#endif