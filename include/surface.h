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
    explicit Surface(int surface_size = 200);

    ~Surface();

    [[nodiscard]] unsigned int get_num_of_vertices(int state) const override;

    [[nodiscard]] const float *get_vertices(int state) const override;

    float get_vertex(int index, int state) override;

    void set_vertex(int index, float value, int state) override;

    [[nodiscard]] int get_surface_size() const;

    [[nodiscard]] int get_vertices_size() const;

    float *vertices[2]{};

protected:
    int surface_size;

    int vertices_size{};

    void push_vertex(glm::vec3 &vertex) override;

    void setup_surface();
};

#endif