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

    unsigned int get_num_of_vertices() const;

    const float *get_vertices(int state = 0) const;

    unsigned int get_num_of_normals() const;

    const float *get_normals() const;

protected:
    std::vector<float> vertices;
    std::vector<float> normals;

    void push_vertex(glm::vec3 &vertex, int idx = 0);

    void push_normal(glm::vec3 &normal, int idx = 0);

    void from_subdivision(int num_of_subdivision);

    void divide_triangle(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, int num_of_subdivision);
};

#endif