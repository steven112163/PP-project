#include "ripple.h"

void ripple_serial(Object *object, float &current_frame) {
    for (int idx = 0; idx < object->get_num_of_vertices(); idx += 3) {
        float x = object->get_vertex(idx);
        float z = object->get_vertex(idx + 2);
        float distance = std::sqrt(std::pow(x, 2) + std::pow(z, 2));
        float radian = 16 * (distance / std::sqrt(2) - current_frame / 7) * PI;
        object->set_vertex(idx + 1, 0.05 * std::sin(radian));

        if (x == 0.0f && z == 0.0f)
            continue;

        glm::vec3 direction = glm::normalize(glm::vec3(x, 0.0f, z));
        glm::vec3 up(0.0f, 1.0f, 0.0f);
        glm::vec3 tangent = glm::normalize(glm::cross(direction, up));
        glm::vec3 derivative = glm::normalize(
                glm::vec3(x,
                          0.05 * std::cos(radian) * distance,
                          z)
        );
        glm::vec3 normal = glm::normalize(glm::cross(tangent, derivative));
        object->set_normal(idx, normal.x);
        object->set_normal(idx + 1, normal.y);
        object->set_normal(idx + 2, normal.z);
    }
}