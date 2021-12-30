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
    Surface(int surface_size = 200);

    unsigned int get_num_of_vertices(int state = 0) const;

    const float *get_vertices(int state = 0) const;

    float get_vertex(int index, int state = 0);

    void set_vertex(int index, float value, int state = 0);

    int get_surface_size() const;

protected:
    int surface_size;
    std::vector<float> vertices[2];

    void push_vertex(glm::vec3 &vertex);

    void setup_surface();
};

#endif