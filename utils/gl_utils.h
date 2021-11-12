#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
public:
    Shader(const char *vertex_path, const char *fragment_path);

    void set_transformations(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

    void use();

    void destroy();

private:
    unsigned int id;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    unsigned int model_location;
    unsigned int view_location;
    unsigned int projection_location;

    void check_errors(unsigned int shader, std::string type);
};

#endif