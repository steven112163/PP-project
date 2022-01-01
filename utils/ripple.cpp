#include "../include/ripple.h"

void ripple_serial(Surface *surface, int &state) {
    // Update vertices
    int x, z;
    float new_y;
    int surface_size = surface->get_surface_size();
    for (z = 1; z < surface_size - 1; z++) {
        for (x = 1; x < surface_size - 1; x++) {
            new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
                     surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
                     surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
                     surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
                     surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x - 1) + 1, state) +
                     surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x + 1) + 1, state) +
                     surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x - 1) + 1, state) +
                     surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x + 1) + 1, state)) / 4;
            new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
            new_y -= new_y / DAMP;
            surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);
        }
    }

    // Edge vertices
    z = 0;
    for (x = 1; x < surface_size - 1; x++) {
        new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x + 1) + 1, state)) / 2.5;
        new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
        new_y -= new_y / DAMP;
        surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);
    }


    x = 0;
    for (z = 1; z < surface_size - 1; z++) {
        new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x + 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x + 1) + 1, state)) / 2.5;
        new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
        new_y -= new_y / DAMP;
        surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);
    }

    z = surface_size - 1;
    for (x = 1; x < surface_size - 1; x++) {
        new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x + 1) + 1, state)) / 2.5;
        new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
        new_y -= new_y / DAMP;
        surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);
    }

    x = surface_size - 1;
    for (z = 1; z < surface_size - 1; z++) {
        new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x - 1) + 1, state)) / 2.5;
        new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
        new_y -= new_y / DAMP;
        surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);
    }

    // Corner vertices
    z = 0;
    x = 0;
    new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
             surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
             surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x + 1) + 1, state)) / 1.5;
    new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
    new_y -= new_y / DAMP;
    surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);

    z = 0;
    x = surface_size - 1;
    new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
             surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
             surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x - 1) + 1, state)) / 1.5;
    new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
    new_y -= new_y / DAMP;
    surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);

    z = surface_size - 1;
    x = 0;
    new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
             surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
             surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x + 1) + 1, state)) / 1.5;
    new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
    new_y -= new_y / DAMP;
    surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);

    z = surface_size - 1;
    x = surface_size - 1;
    new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
             surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
             surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x - 1) + 1, state)) / 1.5;
    new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
    new_y -= new_y / DAMP;
    surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);

    // Change current state
    state = 1 - state;

    // Update normals
    glm::vec3 point, new_normal, neg_z, pos_z, neg_x, pos_x;
    for (z = 1; z < surface_size - 1; z++) {
        for (x = 1; x < surface_size - 1; x++) {
            point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                              surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                              surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));

            neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                              surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                              surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
            pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                              surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                              surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
            neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                              surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                              surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
            pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                              surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                              surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
            new_normal = glm::normalize(glm::cross(neg_z, neg_x) +
                                        glm::cross(neg_x, pos_z) +
                                        glm::cross(pos_z, pos_x) +
                                        glm::cross(pos_x, neg_z));

            surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
            surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
            surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
        }
    }

    // Edge normals
    z = 0;
    for (x = 1; x < surface_size - 1; x++) {
        point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));

        pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
        neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
        pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
        new_normal = glm::normalize(glm::cross(neg_x, pos_z) +
                                    glm::cross(pos_z, pos_x));

        surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
        surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
        surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
    }

    x = 0;
    for (z = 1; z < surface_size - 1; z++) {
        point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));

        neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
        pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
        pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
        new_normal = glm::normalize(glm::cross(pos_z, pos_x) +
                                    glm::cross(pos_x, neg_z));

        surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
        surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
        surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
    }

    z = surface_size - 1;
    for (x = 1; x < surface_size - 1; x++) {
        point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));

        neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
        neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
        pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
        new_normal = glm::normalize(glm::cross(pos_x, neg_z) +
                                    glm::cross(neg_z, neg_x));

        surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
        surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
        surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
    }

    x = surface_size - 1;
    for (z = 1; z < surface_size - 1; z++) {
        point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));

        neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
        pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
        neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
        new_normal = glm::normalize(glm::cross(neg_z, neg_x) +
                                    glm::cross(neg_x, pos_z));

        surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
        surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
        surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
    }

    // Corner normals
    z = 0;
    x = 0;
    point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));
    pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                      surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
    pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
    new_normal = glm::normalize(glm::cross(pos_z, pos_x));
    surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
    surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
    surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);

    z = 0;
    x = surface_size - 1;
    point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));
    pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                      surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
    neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
    new_normal = glm::normalize(glm::cross(neg_x, pos_z));
    surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
    surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
    surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);

    z = surface_size - 1;
    x = 0;
    point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));
    neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                      surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
    pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
    new_normal = glm::normalize(glm::cross(pos_x, neg_z));
    surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
    surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
    surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);

    z = surface_size - 1;
    x = surface_size - 1;
    point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));
    neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                      surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
    neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
    new_normal = glm::normalize(glm::cross(neg_z, neg_x));
    surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
    surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
    surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
}

void ripple_omp(Surface *surface, int &state, int num_threads) {
    // Update vertices
    int x, z;
    float new_y;
    int surface_size = surface->get_surface_size();
    for (z = 1; z < surface_size - 1; z++) {
        for (x = 1; x < surface_size - 1; x++) {
            new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
                     surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
                     surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
                     surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
                     surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x - 1) + 1, state) +
                     surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x + 1) + 1, state) +
                     surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x - 1) + 1, state) +
                     surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x + 1) + 1, state)) / 4;
            new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
            new_y -= new_y / DAMP;
            surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);
        }
    }

    // Edge vertices
    z = 0;
    for (x = 1; x < surface_size - 1; x++) {
        new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x + 1) + 1, state)) / 2.5;
        new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
        new_y -= new_y / DAMP;
        surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);
    }


    x = 0;
    for (z = 1; z < surface_size - 1; z++) {
        new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x + 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x + 1) + 1, state)) / 2.5;
        new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
        new_y -= new_y / DAMP;
        surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);
    }

    z = surface_size - 1;
    for (x = 1; x < surface_size - 1; x++) {
        new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x + 1) + 1, state)) / 2.5;
        new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
        new_y -= new_y / DAMP;
        surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);
    }

    x = surface_size - 1;
    for (z = 1; z < surface_size - 1; z++) {
        new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
                 surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x - 1) + 1, state) +
                 surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x - 1) + 1, state)) / 2.5;
        new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
        new_y -= new_y / DAMP;
        surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);
    }

    // Corner vertices
    z = 0;
    x = 0;
    new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
             surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
             surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x + 1) + 1, state)) / 1.5;
    new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
    new_y -= new_y / DAMP;
    surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);

    z = 0;
    x = surface_size - 1;
    new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
             surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state) +
             surface->get_vertex(3 * surface_size * (z + 1) + 3 * (x - 1) + 1, state)) / 1.5;
    new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
    new_y -= new_y / DAMP;
    surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);

    z = surface_size - 1;
    x = 0;
    new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state) +
             surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
             surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x + 1) + 1, state)) / 1.5;
    new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
    new_y -= new_y / DAMP;
    surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);

    z = surface_size - 1;
    x = surface_size - 1;
    new_y = (surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state) +
             surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state) +
             surface->get_vertex(3 * surface_size * (z - 1) + 3 * (x - 1) + 1, state)) / 1.5;
    new_y -= surface->get_vertex(3 * surface_size * z + 3 * x + 1, 1 - state);
    new_y -= new_y / DAMP;
    surface->set_vertex(3 * surface_size * z + 3 * x + 1, new_y, 1 - state);

    // Change current state
    state = 1 - state;

    // Update normals
    glm::vec3 point, new_normal, neg_z, pos_z, neg_x, pos_x;
    for (z = 1; z < surface_size - 1; z++) {
        for (x = 1; x < surface_size - 1; x++) {
            point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                              surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                              surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));

            neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                              surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                              surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
            pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                              surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                              surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
            neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                              surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                              surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
            pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                              surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                              surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
            new_normal = glm::normalize(glm::cross(neg_z, neg_x) +
                                        glm::cross(neg_x, pos_z) +
                                        glm::cross(pos_z, pos_x) +
                                        glm::cross(pos_x, neg_z));

            surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
            surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
            surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
        }
    }

    // Edge normals
    z = 0;
    for (x = 1; x < surface_size - 1; x++) {
        point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));

        pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
        neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
        pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
        new_normal = glm::normalize(glm::cross(neg_x, pos_z) +
                                    glm::cross(pos_z, pos_x));

        surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
        surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
        surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
    }

    x = 0;
    for (z = 1; z < surface_size - 1; z++) {
        point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));

        neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
        pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
        pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
        new_normal = glm::normalize(glm::cross(pos_z, pos_x) +
                                    glm::cross(pos_x, neg_z));

        surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
        surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
        surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
    }

    z = surface_size - 1;
    for (x = 1; x < surface_size - 1; x++) {
        point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));

        neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
        neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
        pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
        new_normal = glm::normalize(glm::cross(pos_x, neg_z) +
                                    glm::cross(neg_z, neg_x));

        surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
        surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
        surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
    }

    x = surface_size - 1;
    for (z = 1; z < surface_size - 1; z++) {
        point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));

        neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
        pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                          surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
        neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                          surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
        new_normal = glm::normalize(glm::cross(neg_z, neg_x) +
                                    glm::cross(neg_x, pos_z));

        surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
        surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
        surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
    }

    // Corner normals
    z = 0;
    x = 0;
    point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));
    pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                      surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
    pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
    new_normal = glm::normalize(glm::cross(pos_z, pos_x));
    surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
    surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
    surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);

    z = 0;
    x = surface_size - 1;
    point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));
    pos_z = glm::vec3(surface->get_vertex(3 * surface_size * (z + 1) + 3 * x, state),
                      surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * (z + 1) + 3 * x + 2, state)) - point;
    neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
    new_normal = glm::normalize(glm::cross(neg_x, pos_z));
    surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
    surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
    surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);

    z = surface_size - 1;
    x = 0;
    point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));
    neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                      surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
    pos_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x + 1), state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x + 1) + 2, state)) - point;
    new_normal = glm::normalize(glm::cross(pos_x, neg_z));
    surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
    surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
    surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);

    z = surface_size - 1;
    x = surface_size - 1;
    point = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * x, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * x + 2, state));
    neg_z = glm::vec3(surface->get_vertex(3 * surface_size * (z - 1) + 3 * x, state),
                      surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 1, state),
                      surface->get_vertex(3 * surface_size * (z - 1) + 3 * x + 2, state)) - point;
    neg_x = glm::vec3(surface->get_vertex(3 * surface_size * z + 3 * (x - 1), state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 1, state),
                      surface->get_vertex(3 * surface_size * z + 3 * (x - 1) + 2, state)) - point;
    new_normal = glm::normalize(glm::cross(neg_z, neg_x));
    surface->set_normal(3 * surface_size * z + 3 * x, new_normal.x);
    surface->set_normal(3 * surface_size * z + 3 * x + 1, new_normal.y);
    surface->set_normal(3 * surface_size * z + 3 * x + 2, new_normal.z);
}