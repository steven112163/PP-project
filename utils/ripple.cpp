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

void vertex_rest(Surface *surface, int &surface_size, int &surface_stride,
                 int &state, int &damp, int thread_id, int &thread_count) {
    float new_y;
    for (int z = 1 + thread_id; z < surface_size - 1; z += thread_count) {
        for (int x = 1; x < surface_size - 1; x++) {
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
}

void vertex_top_down_edge(Surface *surface, int &surface_size, int &surface_stride,
                          int &state, int &damp, int thread_id, int &thread_count) {
    int z = surface_size - 1;
    float new_y;
    for (int x = 1 + thread_id; x < surface_size - 1; x += thread_count) {
        new_y = (surface->vertices[state][3 * (x - 1) + 1] +
                 surface->vertices[state][3 * (x + 1) + 1] +
                 surface->vertices[state][surface_stride + 3 * x + 1] +
                 surface->vertices[state][surface_stride + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride + 3 * (x + 1) + 1]) / 2.5f;
        new_y -= surface->vertices[1 - state][3 * x + 1];
        new_y -= new_y / damp;
        surface->vertices[1 - state][3 * x + 1] = new_y;

        new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * (x + 1) + 1]) / 2.5f;
        new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
        new_y -= new_y / damp;
        surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
    }
}

void vertex_left_right_edge(Surface *surface, int &surface_size, int &surface_stride,
                            int &state, int &damp, int thread_id, int &thread_count) {
    int x = surface_size - 1;
    float new_y;
    for (int z = 1 + thread_id; z < surface_size - 1; z += thread_count) {
        new_y = (surface->vertices[state][surface_stride * z + 3 + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 3 + 1]) / 2.5f;
        new_y -= surface->vertices[1 - state][surface_stride * z + 1];
        new_y -= new_y / damp;
        surface->vertices[1 - state][surface_stride * z + 1] = new_y;

        new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1] +
                 surface->vertices[state][surface_stride * (z - 1) + 3 * (x - 1) + 1] +
                 surface->vertices[state][surface_stride * (z + 1) + 3 * (x - 1) + 1]) / 2.5f;
        new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
        new_y -= new_y / damp;
        surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
    }
}

void vertex_left_top_corner(Surface *surface, int &surface_size, int &surface_stride, int &state, int &damp) {
    float new_y = (surface->vertices[state][4] +
                   surface->vertices[state][surface_stride + 1] +
                   surface->vertices[state][surface_stride + 4]) / 1.5f;
    new_y -= surface->vertices[1 - state][1];
    new_y -= new_y / damp;
    surface->vertices[1 - state][1] = new_y;
}

void vertex_right_top_corner(Surface *surface, int &surface_size, int &surface_stride, int &state, int &damp) {
    int z = 0;
    int x = surface_size - 1;
    float new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                   surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1] +
                   surface->vertices[state][surface_stride * (z + 1) + 3 * (x - 1) + 1]) / 1.5f;
    new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
    new_y -= new_y / damp;
    surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
}

void vertex_left_bottom_corner(Surface *surface, int &surface_size, int &surface_stride, int &state, int &damp) {
    int z = surface_size - 1;
    int x = 0;
    float new_y = (surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1] +
                   surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                   surface->vertices[state][surface_stride * (z - 1) + 3 * (x + 1) + 1]) / 1.5f;
    new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
    new_y -= new_y / damp;
    surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
}

void vertex_right_bottom_corner(Surface *surface, int &surface_size, int &surface_stride, int &state, int &damp) {
    int z = surface_size - 1;
    int x = surface_size - 1;
    float new_y = (surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1] +
                   surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1] +
                   surface->vertices[state][surface_stride * (z - 1) + 3 * (x - 1) + 1]) / 1.5f;
    new_y -= surface->vertices[1 - state][surface_stride * z + 3 * x + 1];
    new_y -= new_y / damp;
    surface->vertices[1 - state][surface_stride * z + 3 * x + 1] = new_y;
}

void normal_rest(Surface *surface, int &surface_size, int &surface_stride,
                 int &state, int thread_id, int &thread_count) {
    glm::vec3 point, neg_z, pos_z, neg_x, pos_x, new_normal;
    for (int z = 1 + thread_id; z < surface_size - 1; z += thread_count) {
        for (int x = 1; x < surface_size - 1; x++) {
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
}

void normal_top_down_edge(Surface *surface, int &surface_size, int &surface_stride,
                          int &state, int thread_id, int &thread_count) {
    glm::vec3 point, neg_z, pos_z, neg_x, pos_x, new_normal;
    int z = surface_size - 1;
    for (int x = 1 + thread_id; x < surface_size - 1; x += thread_count) {
        point = glm::vec3(surface->vertices[state][3 * x],
                          surface->vertices[state][3 * x + 1],
                          surface->vertices[state][3 * x + 2]);

        pos_z = glm::vec3(surface->vertices[state][surface_stride + 3 * x],
                          surface->vertices[state][surface_stride + 3 * x + 1],
                          surface->vertices[state][surface_stride + 3 * x + 2]) - point;
        neg_x = glm::vec3(surface->vertices[state][3 * (x - 1)],
                          surface->vertices[state][3 * (x - 1) + 1],
                          surface->vertices[state][3 * (x - 1) + 2]) - point;
        pos_x = glm::vec3(surface->vertices[state][3 * (x + 1)],
                          surface->vertices[state][3 * (x + 1) + 1],
                          surface->vertices[state][3 * (x + 1) + 2]) - point;
        new_normal = glm::normalize(glm::cross(neg_x, pos_z) +
                                    glm::cross(pos_z, pos_x));

        surface->normals[3 * x] = new_normal.x;
        surface->normals[3 * x + 1] = new_normal.y;
        surface->normals[3 * x + 2] = new_normal.z;

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
}

void normal_left_right_edge(Surface *surface, int &surface_size, int &surface_stride,
                            int &state, int thread_id, int &thread_count) {
    glm::vec3 point, neg_z, pos_z, neg_x, pos_x, new_normal;
    int x = surface_size - 1;
    for (int z = 1 + thread_id; z < surface_size - 1; z += thread_count) {
        point = glm::vec3(surface->vertices[state][surface_stride * z],
                          surface->vertices[state][surface_stride * z + 1],
                          surface->vertices[state][surface_stride * z + 2]);

        neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1)],
                          surface->vertices[state][surface_stride * (z - 1) + 1],
                          surface->vertices[state][surface_stride * (z - 1) + 2]) - point;
        pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1)],
                          surface->vertices[state][surface_stride * (z + 1) + 1],
                          surface->vertices[state][surface_stride * (z + 1) + 2]) - point;
        pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3],
                          surface->vertices[state][surface_stride * z + 3 + 1],
                          surface->vertices[state][surface_stride * z + 3 + 2]) - point;
        new_normal = glm::normalize(glm::cross(pos_z, pos_x) +
                                    glm::cross(pos_x, neg_z));

        surface->normals[surface_stride * z] = new_normal.x;
        surface->normals[surface_stride * z + 1] = new_normal.y;
        surface->normals[surface_stride * z + 2] = new_normal.z;

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
}

void normal_left_top_corner(Surface *surface, int &surface_size, int &surface_stride, int &state) {
    glm::vec3 point = glm::vec3(surface->vertices[state][0],
                                surface->vertices[state][1],
                                surface->vertices[state][2]);
    glm::vec3 pos_z = glm::vec3(surface->vertices[state][surface_stride],
                                surface->vertices[state][surface_stride + 1],
                                surface->vertices[state][surface_stride + 2]) - point;
    glm::vec3 pos_x = glm::vec3(surface->vertices[state][3],
                                surface->vertices[state][4],
                                surface->vertices[state][5]) - point;
    glm::vec3 new_normal = glm::normalize(glm::cross(pos_z, pos_x));
    surface->normals[0] = new_normal.x;
    surface->normals[1] = new_normal.y;
    surface->normals[2] = new_normal.z;
}

void normal_right_top_corner(Surface *surface, int &surface_size, int &surface_stride, int &state) {
    int z = 0;
    int x = surface_size - 1;
    glm::vec3 point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                                surface->vertices[state][surface_stride * z + 3 * x + 1],
                                surface->vertices[state][surface_stride * z + 3 * x + 2]);
    glm::vec3 pos_z = glm::vec3(surface->vertices[state][surface_stride * (z + 1) + 3 * x],
                                surface->vertices[state][surface_stride * (z + 1) + 3 * x + 1],
                                surface->vertices[state][surface_stride * (z + 1) + 3 * x + 2]) - point;
    glm::vec3 neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                                surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                                surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
    glm::vec3 new_normal = glm::normalize(glm::cross(neg_x, pos_z));
    surface->normals[surface_stride * z + 3 * x] = new_normal.x;
    surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
    surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
}

void normal_left_bottom_corner(Surface *surface, int &surface_size, int &surface_stride, int &state) {
    int z = surface_size - 1;
    int x = 0;
    glm::vec3 point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                                surface->vertices[state][surface_stride * z + 3 * x + 1],
                                surface->vertices[state][surface_stride * z + 3 * x + 2]);
    glm::vec3 neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                                surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                                surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
    glm::vec3 pos_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x + 1)],
                                surface->vertices[state][surface_stride * z + 3 * (x + 1) + 1],
                                surface->vertices[state][surface_stride * z + 3 * (x + 1) + 2]) - point;
    glm::vec3 new_normal = glm::normalize(glm::cross(pos_x, neg_z));
    surface->normals[surface_stride * z + 3 * x] = new_normal.x;
    surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
    surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
}

void normal_right_bottom_corner(Surface *surface, int &surface_size, int &surface_stride, int &state) {
    int z = surface_size - 1;
    int x = surface_size - 1;
    glm::vec3 point = glm::vec3(surface->vertices[state][surface_stride * z + 3 * x],
                                surface->vertices[state][surface_stride * z + 3 * x + 1],
                                surface->vertices[state][surface_stride * z + 3 * x + 2]);
    glm::vec3 neg_z = glm::vec3(surface->vertices[state][surface_stride * (z - 1) + 3 * x],
                                surface->vertices[state][surface_stride * (z - 1) + 3 * x + 1],
                                surface->vertices[state][surface_stride * (z - 1) + 3 * x + 2]) - point;
    glm::vec3 neg_x = glm::vec3(surface->vertices[state][surface_stride * z + 3 * (x - 1)],
                                surface->vertices[state][surface_stride * z + 3 * (x - 1) + 1],
                                surface->vertices[state][surface_stride * z + 3 * (x - 1) + 2]) - point;
    glm::vec3 new_normal = glm::normalize(glm::cross(neg_z, neg_x));
    surface->normals[surface_stride * z + 3 * x] = new_normal.x;
    surface->normals[surface_stride * z + 3 * x + 1] = new_normal.y;
    surface->normals[surface_stride * z + 3 * x + 2] = new_normal.z;
}

void ripple_thread(Surface *surface, int &state, int &damp, int &thread_count) {
    int surface_size = surface->get_surface_size();
    int surface_stride = 3 * surface_size;

    // Setup threads
    std::thread threads[thread_count];

    // Update vertices
    // Rest
    for (int thread_idx = 0; thread_idx < thread_count; thread_idx++)
        threads[thread_idx] = std::thread(vertex_rest, surface, std::ref(surface_size), std::ref(surface_stride),
                                          std::ref(state), std::ref(damp), thread_idx, std::ref(thread_count));
    for (auto &th: threads)
        th.join();

    // Edges
    for (int thread_idx = 0; thread_idx < thread_count; thread_idx++)
        threads[thread_idx] = std::thread(vertex_top_down_edge, surface, std::ref(surface_size),
                                          std::ref(surface_stride), std::ref(state), std::ref(damp),
                                          thread_idx, std::ref(thread_count));
    for (auto &th: threads)
        th.join();

    for (int thread_idx = 0; thread_idx < thread_count; thread_idx++)
        threads[thread_idx] = std::thread(vertex_left_right_edge, surface, std::ref(surface_size),
                                          std::ref(surface_stride), std::ref(state), std::ref(damp),
                                          thread_idx, std::ref(thread_count));
    for (auto &th: threads)
        th.join();

    // Corners
    if (thread_count >= 4) {
        threads[0] = std::thread(vertex_left_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        threads[1] = std::thread(vertex_right_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        threads[2] = std::thread(vertex_left_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        threads[3] = std::thread(vertex_right_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        for (int thread_idx = 0; thread_idx < 4; thread_idx++)
            threads[thread_idx].join();
    } else if (thread_count == 3) {
        threads[0] = std::thread(vertex_left_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        threads[1] = std::thread(vertex_right_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        threads[2] = std::thread(vertex_left_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        vertex_right_bottom_corner(surface, surface_size, surface_stride, state, damp);
        for (int thread_idx = 0; thread_idx < 3; thread_idx++)
            threads[thread_idx].join();
    } else if (thread_count == 2) {
        threads[0] = std::thread(vertex_left_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        threads[1] = std::thread(vertex_right_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        for (int thread_idx = 0; thread_idx < 2; thread_idx++)
            threads[thread_idx].join();

        threads[0] = std::thread(vertex_left_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        threads[1] = std::thread(vertex_right_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        for (int thread_idx = 0; thread_idx < 2; thread_idx++)
            threads[thread_idx].join();
    } else if (thread_count == 1) {
        threads[0] = std::thread(vertex_left_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        vertex_right_top_corner(surface, surface_size, surface_stride, state, damp);
        threads[0].join();

        threads[0] = std::thread(vertex_left_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state), std::ref(damp));
        vertex_right_bottom_corner(surface, surface_size, surface_stride, state, damp);
        threads[0].join();
    }

    // Change current state
    state = 1 - state;

    // Update normals
    // Rest
    for (int thread_idx = 0; thread_idx < thread_count; thread_idx++)
        threads[thread_idx] = std::thread(normal_rest, surface, std::ref(surface_size), std::ref(surface_stride),
                                          std::ref(state), thread_idx, std::ref(thread_count));
    for (auto &th: threads)
        th.join();

    // Edges
    for (int thread_idx = 0; thread_idx < thread_count; thread_idx++)
        threads[thread_idx] = std::thread(normal_top_down_edge, surface, std::ref(surface_size),
                                          std::ref(surface_stride), std::ref(state), thread_idx,
                                          std::ref(thread_count));
    for (auto &th: threads)
        th.join();

    for (int thread_idx = 0; thread_idx < thread_count; thread_idx++)
        threads[thread_idx] = std::thread(normal_left_right_edge, surface, std::ref(surface_size),
                                          std::ref(surface_stride), std::ref(state), thread_idx,
                                          std::ref(thread_count));
    for (auto &th: threads)
        th.join();

    // Corners
    if (thread_count >= 4) {
        threads[0] = std::thread(normal_left_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        threads[1] = std::thread(normal_right_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        threads[2] = std::thread(normal_left_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        threads[3] = std::thread(normal_right_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        for (int thread_idx = 0; thread_idx < 4; thread_idx++)
            threads[thread_idx].join();
    } else if (thread_count == 3) {
        threads[0] = std::thread(normal_left_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        threads[1] = std::thread(normal_right_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        threads[2] = std::thread(normal_left_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        normal_right_bottom_corner(surface, surface_size, surface_stride, state);
        for (int thread_idx = 0; thread_idx < 3; thread_idx++)
            threads[thread_idx].join();
    } else if (thread_count == 2) {
        threads[0] = std::thread(normal_left_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        threads[1] = std::thread(normal_right_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        for (int thread_idx = 0; thread_idx < 2; thread_idx++)
            threads[thread_idx].join();

        threads[0] = std::thread(normal_left_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        threads[1] = std::thread(normal_right_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        for (int thread_idx = 0; thread_idx < 2; thread_idx++)
            threads[thread_idx].join();
    } else if (thread_count == 1) {
        threads[0] = std::thread(normal_left_top_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        normal_right_top_corner(surface, surface_size, surface_stride, state);
        threads[0].join();

        threads[0] = std::thread(normal_left_bottom_corner, surface, std::ref(surface_size),
                                 std::ref(surface_stride), std::ref(state));
        normal_right_bottom_corner(surface, surface_size, surface_stride, state);
        threads[0].join();
    }
}