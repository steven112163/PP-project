#version 330 core
in vec3 position_in_global;
in vec3 normal_in_global;

uniform vec3 light_position;
uniform vec3 ambient_light_color;
uniform vec3 diffuse_light_color;
uniform vec3 specular_light_color;

uniform vec3 ambient_material_color;
uniform vec3 diffuse_material_color;
uniform vec3 specular_material_color;

uniform float shininess;

uniform vec3 camera_position;

out vec4 FragColor;

void main() {
    // Calculate the vector (l) to the light source
    vec3 vector_to_light_source = normalize(light_position - position_in_global);

    // Calculate n dot l for diffuse lighting
    float diffuse_light_weighing = max(dot(normal_in_global, vector_to_light_source), 0.0f);

    // Calculate the reflection vector (r) that is needed for specular light
    vec3 reflection_vector = normalize(reflect(-vector_to_light_source, normal_in_global));

    // Calculate view_vector (v) that is needed for specular light
    vec3 view_vector = normalize(camera_position - position_in_global);

    float r_dot_v = max(dot(reflection_vector, view_vector), 0.0f);

    float specular_light_weighing = pow(r_dot_v, shininess);

    // Sum up all three reflection components and send to the fragment shader
    FragColor = vec4(((ambient_light_color * ambient_material_color)
            + (diffuse_light_color * diffuse_material_color) * diffuse_light_weighing
            + (specular_light_color * specular_material_color) * specular_light_weighing), 1.0f);
}