#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_matrix;

out vec3 position_in_global;
out vec3 normal_in_global;

void main() {
    // Get the vertex position in global space
    position_in_global = vec3(model * vec4(position, 1.0f));

    // Calculate the normal in global space
    normal_in_global = normalize(normal_matrix * normal);

    gl_Position = projection * view * model * vec4(position_in_global, 1.0f);
}