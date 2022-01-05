#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"

#include "../include/ripple.h"

void ripple_serial(Surface *surface, int &state, int &damp) {
    // Update vertices
    int x, z;
    float new_y;
    int surface_size = surface->get_surface_size();
    int surface_stride = 3 * surface_size;
    for (z = 1; z < surface_size - 1; z++) {
        for (x = 1; x < surface_size - 1; x++) {
            new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                     surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1] +
                     surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                     surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1] +
                     surface->vertices[state][surface_stride * (z - 1) + 3 * (x - 1) + 1] +
                     surface->vertices[state][surface_stride * (z - 1) + 3 * (x + 1) + 1] +
                     surface->vertices[state][surface_stride * (z + 1) + 3 * (x - 1) + 1] +
                     surface->vertices[state][surface_stride * (z + 1) + 3 * (x + 1) + 1]) / 4.0f;
            new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
            new_y -= new_y / damp;
            surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
        }
    }

    // Edge vertices
    z = 0;
    for (x = 1; x < surface_size - 1; x++) {
        new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 3 * (x + 1) + 1]) / 2.5f;
        new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
        new_y -= new_y / damp;
        surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
    }


    x = 0;
    for (z = 1; z < surface_size - 1; z++) {
        new_y = (surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * (x + 1) + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 3 * (x + 1) + 1]) / 2.5f;
        new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
        new_y -= new_y / damp;
        surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
    }

    z = surface_size - 1;
    for (x = 1; x < surface_size - 1; x++) {
        new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * (x + 1) + 1]) / 2.5f;
        new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
        new_y -= new_y / damp;
        surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
    }

    x = surface_size - 1;
    for (z = 1; z < surface_size - 1; z++) {
        new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 3 * (x - 1) + 1]) / 2.5f;
        new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
        new_y -= new_y / damp;
        surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
    }

    // Corner vertices
    z = 0;
    x = 0;
    new_y = (surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1] +
             surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1] +
             surface->vertices[state][surface_stride * (z + 1) + 3 * (x + 1) + 1]) / 1.5f;
    new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
    new_y -= new_y / damp;
    surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;

    z = 0;
    x = surface_size - 1;
    new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
             surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1] +
             surface->vertices[state][surface_stride * (z + 1) + 3 * (x - 1) + 1]) / 1.5f;
    new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
    new_y -= new_y / damp;
    surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;

    z = surface_size - 1;
    x = 0;
    new_y = (surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1] +
             surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
             surface->vertices[state][surface_stride * (z - 1) + 3 * (x + 1) + 1]) / 1.5f;
    new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
    new_y -= new_y / damp;
    surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;

    z = surface_size - 1;
    x = surface_size - 1;
    new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
             surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
             surface->vertices[state][surface_stride * (z - 1) + 3 * (x - 1) + 1]) / 1.5f;
    new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
    new_y -= new_y / damp;
    surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;

    // Change current state
    state = 1 - state;

    // Update normals
    glm::vec3 point, new_normal, neg_z, pos_z, neg_x, pos_x;
    for (z = 1; z < surface_size - 1; z++) {
        for (x = 1; x < surface_size - 1; x++) {
            point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                              surface->vertices[state][surface_stride * z + 3 * x + 1],
                              surface->vertices[state][surface_stride * z + 3 * x + 2]);

            neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                              surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                              surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
            pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                              surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                              surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
            neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                              surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                              surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
            pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                              surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                              surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
            new_normal = glm::normalize(glm::cross(neg_z, neg_x) +
                                        glm::cross(neg_x, pos_z) +
                                        glm::cross(pos_z, pos_x) +
                                        glm::cross(pos_x, neg_z));

            surface->normals[surface_stride * z + 3 * x] = new_normal.x;
            surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
            surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
        }
    }

    // Edge normals
    z = 0;
    for (x = 1; x < surface_size - 1; x++) {
        point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                          surface->vertices[state][surface_stride * z + 3 * x + 1],
                          surface->vertices[state][surface_stride * z + 3 * x + 2]);

        pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                          surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                          surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
        neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                          surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                          surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
        pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                          surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                          surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
        new_normal = glm::normalize(glm::cross(neg_x, pos_z) +
                                    glm::cross(pos_z, pos_x));

        surface->normals[surface_stride * z + 3 * x] = new_normal.x;
        surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
        surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
    }

    x = 0;
    for (z = 1; z < surface_size - 1; z++) {
        point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                          surface->vertices[state][surface_stride * z + 3 * x + 1],
                          surface->vertices[state][surface_stride * z + 3 * x + 2]);

        neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                          surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                          surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
        pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                          surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                          surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
        pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                          surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                          surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
        new_normal = glm::normalize(glm::cross(pos_z, pos_x) +
                                    glm::cross(pos_x, neg_z));

        surface->normals[surface_stride * z + 3 * x] = new_normal.x;
        surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
        surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
    }

    z = surface_size - 1;
    for (x = 1; x < surface_size - 1; x++) {
        point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                          surface->vertices[state][surface_stride * z + 3 * x + 1],
                          surface->vertices[state][surface_stride * z + 3 * x + 2]);

        neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                          surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                          surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
        neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                          surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                          surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
        pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                          surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                          surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
        new_normal = glm::normalize(glm::cross(pos_x, neg_z) +
                                    glm::cross(neg_z, neg_x));

        surface->normals[surface_stride * z + 3 * x] = new_normal.x;
        surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
        surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
    }

    x = surface_size - 1;
    for (z = 1; z < surface_size - 1; z++) {
        point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                          surface->vertices[state][surface_stride * z + 3 * x + 1],
                          surface->vertices[state][surface_stride * z + 3 * x + 2]);

        neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                          surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                          surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
        pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                          surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                          surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
        neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                          surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                          surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
        new_normal = glm::normalize(glm::cross(neg_z, neg_x) +
                                    glm::cross(neg_x, pos_z));

        surface->normals[surface_stride * z + 3 * x] = new_normal.x;
        surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
        surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
    }

    // Corner normals
    z = 0;
    x = 0;
    point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                      surface->vertices[state][surface_stride * z + 3 * x + 1],
                      surface->vertices[state][surface_stride * z + 3 * x + 2]);
    pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                      surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                      surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
    pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                      surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                      surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
    new_normal = glm::normalize(glm::cross(pos_z, pos_x));
    surface->normals[surface_stride * z + 3 * x] = new_normal.x;
    surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
    surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;

    z = 0;
    x = surface_size - 1;
    point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                      surface->vertices[state][surface_stride * z + 3 * x + 1],
                      surface->vertices[state][surface_stride * z + 3 * x + 2]);
    pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                      surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                      surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
    neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                      surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                      surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
    new_normal = glm::normalize(glm::cross(neg_x, pos_z));
    surface->normals[surface_stride * z + 3 * x] = new_normal.x;
    surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
    surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;

    z = surface_size - 1;
    x = 0;
    point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                      surface->vertices[state][surface_stride * z + 3 * x + 1],
                      surface->vertices[state][surface_stride * z + 3 * x + 2]);
    neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                      surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                      surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
    pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                      surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                      surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
    new_normal = glm::normalize(glm::cross(pos_x, neg_z));
    surface->normals[surface_stride * z + 3 * x] = new_normal.x;
    surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
    surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;

    z = surface_size - 1;
    x = surface_size - 1;
    point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                      surface->vertices[state][surface_stride * z + 3 * x + 1],
                      surface->vertices[state][surface_stride * z + 3 * x + 2]);
    neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                      surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                      surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
    neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                      surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                      surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
    new_normal = glm::normalize(glm::cross(neg_z, neg_x));
    surface->normals[surface_stride * z + 3 * x] = new_normal.x;
    surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
    surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
}

void ripple_omp(Surface *surface, int &state, int &dampI) {
    // Update vertices
    int x, z;
    float new_y;
    auto damp = float(dampI);
    int surface_size = surface->get_surface_size();
    const int surface_stride = 3 * surface_size;
#pragma omp parallel
    {
//#pragma omp for collapse (2)
#pragma omp for
        for (x = 1; x < surface_size - 1; x++) {
            for (z = 1; z < surface_size - 1; z++) {
                new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                         surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1] +
                         surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                         surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1] +
                         surface->vertices[state][surface_stride * (z - 1) + 3 * (x - 1) + 1] +
                         surface->vertices[state][surface_stride * (z - 1) + 3 * (x + 1) + 1] +
                         surface->vertices[state][surface_stride * (z + 1) + 3 * (x - 1) + 1] +
                         surface->vertices[state][surface_stride * (z + 1) + 3 * (x + 1) + 1]) / 4.0f;
                new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
                new_y -= new_y / damp;
                surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
            }
        }

        // Edge vertices
#pragma omp for
        for (x = 1; x < surface_size - 1; x++) {
            new_y = (surface->vertices[state][3 * (x - 1) + 1] +
                     surface->vertices[state][3 * (x + 1) + 1] +
                     surface->vertices[state][surface_stride + 3 * x + 1] +
                     surface->vertices[state][surface_stride + 3 * (x - 1) + 1] +
                     surface->vertices[state][surface_stride + 3 * (x + 1) + 1]) / 2.5f;
            new_y -= surface->vertices[1 - state][3 * x + 1];
            new_y -= new_y / damp;
            surface->vertices[1 - state][3 * x + 1] = new_y;

            new_y = (surface->vertices[state][surface_stride * (surface_size - 1) + 3 * (x - 1) + 1] +
                     surface->vertices[state][surface_stride * (surface_size - 1) + 3 * (x + 1) + 1] +
                     surface->vertices[state][surface_stride * (surface_size - 2) + 3 * x + 1] +
                     surface->vertices[state][surface_stride * (surface_size - 2) + 3 * (x - 1) + 1] +
                     surface->vertices[state][surface_stride * (surface_size - 2) + 3 * (x + 1) + 1]) / 2.5f;
            new_y -= surface->vertices[1 - state][surface_stride * (surface_size - 1) + 3 * x + 1];
            new_y -= new_y / damp;
            surface->vertices[1 - state][surface_stride * (surface_size - 1) + 3 * x + 1] = new_y;
        }

#pragma omp for
        for (z = 1; z < surface_size - 1; z++) {
            new_y = (surface->vertices[state][surface_stride * z + 3 + 1] +
                     surface->vertices[state][surface_stride * (z - 1) + 1] +
                     surface->vertices[state][surface_stride * (z + 1) + 1] +
                     surface->vertices[state][surface_stride * (z - 1) + 3 + 1] +
                     surface->vertices[state][surface_stride * (z + 1) + 3 + 1]) / 2.5f;
            new_y -= surface->vertices[1 - state][surface_stride * z + 1];
            new_y -= new_y / damp;
            surface->vertices[1 - state][surface_stride * z + 1] = new_y;

            new_y = (surface->vertices[state][surface_stride * z + 3 * (surface_size - 2) + 1] +
                     surface->vertices[state][surface_stride * (z - 1) + 3 * (surface_size - 1) + 1] +
                     surface->vertices[state][surface_stride * (z + 1) + 3 * (surface_size - 1) + 1] +
                     surface->vertices[state][surface_stride * (z - 1) + 3 * (surface_size - 2) + 1] +
                     surface->vertices[state][surface_stride * (z + 1) + 3 * (surface_size - 2) + 1]) / 2.5f;
            new_y -= surface->vertices[1 - state][surface_stride * z + 3 * (surface_size - 1) + 1];
            new_y -= new_y / damp;
            surface->vertices[1 - state][surface_stride * z + 3 * (surface_size - 1) + 1] = new_y;
        }

        // Corner vertices
#pragma omp sections
        {
#pragma omp section
            {
                z = 0;
                x = 0;
                new_y = (surface->vertices[state][4] +
                         surface->vertices[state][surface_stride + 1] +
                         surface->vertices[state][surface_stride + 4]) / 1.5f;
                new_y -= surface->vertices[1 - state][1];
                new_y -= new_y / damp;
                surface->vertices[1 - state][1] = new_y;
            }
#pragma omp section
            {
                z = 0;
                x = surface_size - 1;
                new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                         surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1] +
                         surface->vertices[state][surface_stride * (z + 1) + 3 * (x - 1) + 1]) / 1.5f;
                new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
                new_y -= new_y / damp;
                surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
            }
#pragma omp section
            {
                z = surface_size - 1;
                x = 0;
                new_y = (surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1] +
                         surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                         surface->vertices[state][surface_stride * (z - 1) + 3 * (x + 1) + 1]) / 1.5f;
                new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
                new_y -= new_y / damp;
                surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
            }
#pragma omp section
            {
                z = surface_size - 1;
                x = surface_size - 1;
                new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                         surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                         surface->vertices[state][surface_stride * (z - 1) + 3 * (x - 1) + 1]) / 1.5f;
                new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
                new_y -= new_y / damp;
                surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
            }
        }
    }

    // Change current state
    state = 1 - state;

#pragma omp parallel
    {
        // Update normals
//#pragma omp for collapse(2)
#pragma omp for
        for (z = 1; z < surface_size - 1; z++) {
            for (x = 1; x < surface_size - 1; x++) {
                glm::vec3 point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                                            surface->vertices[state][surface_stride * z + 3 * x + 1],
                                            surface->vertices[state][surface_stride * z + 3 * x + 2]);

                glm::vec3 neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                                            surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                                            surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
                glm::vec3 pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                                            surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                                            surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
                glm::vec3 neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                                            surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                                            surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
                glm::vec3 pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                                            surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                                            surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
                glm::vec3 new_normal = glm::normalize(glm::cross(neg_z, neg_x) +
                                                      glm::cross(neg_x, pos_z) +
                                                      glm::cross(pos_z, pos_x) +
                                                      glm::cross(pos_x, neg_z));

                surface->normals[surface_stride * z + 3 * x] = new_normal.x;
                surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
                surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
            }
        }

        // Edge normals
#pragma omp for
        for (x = 1; x < surface_size - 1; x++) {
            glm::vec3 point = glm::vec3(surface->vertices[state][3 * x],
                                        surface->vertices[state][3 * x + 1],
                                        surface->vertices[state][3 * x + 2]);

            glm::vec3 pos_z = glm::vec3(surface->vertices[state][surface_stride + 3 * x],
                                        surface->vertices[state][surface_stride + 3 * x + 1],
                                        surface->vertices[state][surface_stride + 3 * x + 2]) - point;
            glm::vec3 neg_x = glm::vec3(surface->vertices[state][3 * (x - 1)],
                                        surface->vertices[state][3 * (x - 1) + 1],
                                        surface->vertices[state][3 * (x - 1) + 2]) - point;
            glm::vec3 pos_x = glm::vec3(surface->vertices[state][3 * (x + 1)],
                                        surface->vertices[state][3 * (x + 1) + 1],
                                        surface->vertices[state][3 * (x + 1) + 2]) - point;
            glm::vec3 new_normal = glm::normalize(glm::cross(neg_x, pos_z) +
                                                  glm::cross(pos_z, pos_x));

            surface->normals[3 * x] = new_normal.x;
            surface->normals[3 * x + 1] = new_normal.y;
            surface->normals[3 * x + 2] = new_normal.z;
        }

#pragma omp for
        for (z = 1; z < surface_size - 1; z++) {
            glm::vec3 point = glm::vec3(surface->vertices[state][surface_stride * z],
                                        surface->vertices[state][surface_stride * z + 1],
                                        surface->vertices[state][surface_stride * z + 2]);

            glm::vec3 neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1)],
                                        surface->vertices[state][surface_stride * (z - 1) + 1],
                                        surface->vertices[state][surface_stride * (z - 1) + 2]) - point;
            glm::vec3 pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1)],
                                        surface->vertices[state][surface_stride * (z + 1) + 1],
                                        surface->vertices[state][surface_stride * (z + 1) + 2]) - point;
            glm::vec3 pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3],
                                        surface->vertices[state][surface_stride * z + 3 + 1],
                                        surface->vertices[state][surface_stride * z + 3 + 2]) - point;
            glm::vec3 new_normal = glm::normalize(glm::cross(pos_z, pos_x) +
                                                  glm::cross(pos_x, neg_z));

            surface->normals[surface_stride * z] = new_normal.x;
            surface->normals[surface_stride * z + 1] = new_normal.y;
            surface->normals[surface_stride * z + 2] = new_normal.z;
        }

        z = surface_size - 1;
#pragma omp for
        for (x = 1; x < surface_size - 1; x++) {
            glm::vec3 point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                                        surface->vertices[state][surface_stride * z + 3 * x + 1],
                                        surface->vertices[state][surface_stride * z + 3 * x + 2]);

            glm::vec3 neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                                        surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                                        surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
            glm::vec3 neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                                        surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                                        surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
            glm::vec3 pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                                        surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                                        surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
            glm::vec3 new_normal = glm::normalize(glm::cross(pos_x, neg_z) +
                                                  glm::cross(neg_z, neg_x));

            surface->normals[surface_stride * z + 3 * x] = new_normal.x;
            surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
            surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
        }

        x = surface_size - 1;
#pragma omp for
        for (z = 1; z < surface_size - 1; z++) {
            glm::vec3 point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                                        surface->vertices[state][surface_stride * z + 3 * x + 1],
                                        surface->vertices[state][surface_stride * z + 3 * x + 2]);

            glm::vec3 neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                                        surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                                        surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
            glm::vec3 pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                                        surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                                        surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
            glm::vec3 neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                                        surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                                        surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
            glm::vec3 new_normal = glm::normalize(glm::cross(neg_z, neg_x) +
                                                  glm::cross(neg_x, pos_z));

            surface->normals[surface_stride * z + 3 * x] = new_normal.x;
            surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
            surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
        }

        // 4 Corner normals, 4 sections
#pragma omp sections
        {
#pragma omp section
            {
                glm::vec3 point, neg_z, pos_z, neg_x, pos_x, new_normal;
                z = 0;
                x = 0;
                point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                                  surface->vertices[state][surface_stride * z + 3 * x + 1],
                                  surface->vertices[state][surface_stride * z + 3 * x + 2]);
                pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                                  surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                                  surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
                pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                                  surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                                  surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
                new_normal = glm::normalize(glm::cross(pos_z, pos_x));
                surface->normals[surface_stride * z + 3 * x] = new_normal.x;
                surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
                surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
            }
#pragma omp section
            {
                glm::vec3 point, neg_z, pos_z, neg_x, pos_x, new_normal;
                z = 0;
                x = surface_size - 1;
                point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                                  surface->vertices[state][surface_stride * z + 3 * x + 1],
                                  surface->vertices[state][surface_stride * z + 3 * x + 2]);
                pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                                  surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                                  surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
                neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                                  surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                                  surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
                new_normal = glm::normalize(glm::cross(neg_x, pos_z));
                surface->normals[surface_stride * z + 3 * x] = new_normal.x;
                surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
                surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
            }
#pragma omp section
            {
                glm::vec3 point, neg_z, pos_z, neg_x, pos_x, new_normal;
                z = surface_size - 1;
                x = 0;
                point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                                  surface->vertices[state][surface_stride * z + 3 * x + 1],
                                  surface->vertices[state][surface_stride * z + 3 * x + 2]);
                neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                                  surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                                  surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
                pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                                  surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                                  surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
                new_normal = glm::normalize(glm::cross(pos_x, neg_z));
                surface->normals[surface_stride * z + 3 * x] = new_normal.x;
                surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
                surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
            }
#pragma omp section
            {
                glm::vec3 point, neg_z, pos_z, neg_x, pos_x, new_normal;
                z = surface_size - 1;
                x = surface_size - 1;
                point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                                  surface->vertices[state][surface_stride * z + 3 * x + 1],
                                  surface->vertices[state][surface_stride * z + 3 * x + 2]);
                neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                                  surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                                  surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
                neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                                  surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                                  surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
                new_normal = glm::normalize(glm::cross(neg_z, neg_x));
                surface->normals[surface_stride * z + 3 * x] = new_normal.x;
                surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
                surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
            }
        }
    }
}

#pragma clang diagnostic pop