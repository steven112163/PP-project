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

    unsigned int get_num_of_vertices() const;

    const float *get_vertices() const;

    float get_vertex(int index);

    void set_vertex(int index, float value);

    void flip_state();

protected:
    int state;
    std::vector <std::vector<float>> vertices;

    void push_vertex(glm::vec3 &vertex);

    void setup_surface(int surface_size);
};

#endif