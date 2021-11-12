#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
public:
    unsigned int id;

    Shader(const char *vertex_path, const char *fragment_path);

    void use();

    void destroy();

private:
    void check_errors(unsigned int shader, std::string type);
};

#endif