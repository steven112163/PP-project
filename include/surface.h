#ifndef SURFACE_H
#define SURFACE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "object.h"

class Surface : public Object {
public:
    float *vertices[2];
    float *normals;

    Surface(int surface_size = 200);

    ~Surface();

    unsigned int get_num_of_vertices() const;

    const float *get_vertices(int state = 0) const;

    unsigned int get_num_of_normals() const;

    const float *get_normals() const;

    int get_surface_size() const;

protected:
    int surface_size;
    int vertices_size;

    void push_vertex(glm::vec3 &vertex, int idx = 0);

    void push_normal(glm::vec3 &normal, int idx = 0);

    void setup_surface();
};

#endif