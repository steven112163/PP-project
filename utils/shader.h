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

    void set_transformations(glm::mat4 model,
                             glm::mat4 view,
                             glm::mat4 projection,
                             glm::mat3 normal_matrix);

    void set_model(glm::mat4 model);

    void set_view(glm::mat4 view);

    void set_projection(glm::mat4 projection);

    void set_normal_matrix(glm::mat3 normal_matrix);

    void set_light(glm::vec3 light_direction,
                   glm::vec3 ambient_light_color,
                   glm::vec3 diffuse_light_color,
                   glm::vec3 specular_light_color);

    void set_light_direction(glm::vec3 light_direction);

    void set_ambient_light_color(glm::vec3 ambient_light_color);

    void set_diffuse_light_color(glm::vec3 diffuse_light_color);

    void set_specular_light_color(glm::vec3 specular_light_color);

    void set_material(glm::vec3 ambient_material_color,
                      glm::vec3 diffuse_material_color,
                      glm::vec3 specular_material_color,
                      glm::float32 shininess);

    void set_ambient_material_color(glm::vec3 ambient_material_color);

    void set_diffuse_material_color(glm::vec3 diffuse_material_color);

    void set_specular_material_color(glm::vec3 specular_material_color);

    void set_shininess(glm::float32 shininess);

    void set_camera_position(glm::vec3 camera_position);

    void use();

    void destroy();

private:
    unsigned int id;

    // Transformation
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat3 normal_matrix;
    unsigned int model_location;
    unsigned int view_location;
    unsigned int projection_location;
    unsigned int normal_matrix_location;

    // Light source
    glm::vec3 light_direction;
    glm::vec3 ambient_light_color;
    glm::vec3 diffuse_light_color;
    glm::vec3 specular_light_color;
    unsigned int light_direction_location;
    unsigned int ambient_light_color_location;
    unsigned int diffuse_light_color_location;
    unsigned int specular_light_color_location;

    // Material
    glm::vec3 ambient_material_color;
    glm::vec3 diffuse_material_color;
    glm::vec3 specular_material_color;
    glm::float32 shininess;
    unsigned int ambient_material_color_location;
    unsigned int diffuse_material_color_location;
    unsigned int specular_material_color_location;
    unsigned int shininess_location;

    // Camera
    glm::vec3 camera_position;
    unsigned int camera_position_location;

    void check_errors(unsigned int shader, std::string type);
};

#endif