#ifndef SURFACE_H
#define SURFACE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Surface {
public:
    Surface(int num_of_subdivision = 6);

    unsigned int get_num_of_vertices() const;

    const float *get_vertices() const;

    unsigned int get_num_of_normals() const;

    const float *get_normals() const;

private:
    std::vector<float> vertices;
    std::vector<float> normals;

    void surface_from_subdivision(int num_of_subdivision);

    void divide_triangle(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, int num_of_subdivision);

    void push_vertex(glm::vec3 &vertex);

    void push_normal(glm::vec3 &normal);
};

#endif