#include "surface.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <thread>

#define PI 3.1415926

void ripple_serial(Surface *surface, int &state, int &damp);

void vertex_rest(Surface *surface, int &surface_size, int &surface_stride,
                 int &state, int &damp, int thread_id, int &thread_count);

void vertex_top_down_edge(Surface *surface, int &surface_size, int &surface_stride,
                          int &state, int &damp, int thread_id, int &thread_count);

void vertex_left_right_edge(Surface *surface, int &surface_size, int &surface_stride,
                            int &state, int &damp, int thread_id, int &thread_count);

void vertex_left_top_corner(Surface *surface, int &surface_size, int &surface_stride, int &state, int &damp);

void vertex_right_top_corner(Surface *surface, int &surface_size, int &surface_stride, int &state, int &damp);

void vertex_left_bottom_corner(Surface *surface, int &surface_size, int &surface_stride, int &state, int &damp);

void vertex_right_bottom_corner(Surface *surface, int &surface_size, int &surface_stride, int &state, int &damp);

void normal_rest(Surface *surface, int &surface_size, int &surface_stride,
                 int &state, int thread_id, int &thread_count);

void normal_top_down_edge(Surface *surface, int &surface_size, int &surface_stride,
                          int &state, int thread_id, int &thread_count);

void normal_left_right_edge(Surface *surface, int &surface_size, int &surface_stride,
                            int &state, int thread_id, int &thread_count);

void normal_left_top_corner(Surface *surface, int &surface_size, int &surface_stride, int &state);

void normal_right_top_corner(Surface *surface, int &surface_size, int &surface_stride, int &state);

void normal_left_bottom_corner(Surface *surface, int &surface_size, int &surface_stride, int &state);

void normal_right_bottom_corner(Surface *surface, int &surface_size, int &surface_stride, int &state);

void ripple_thread(Surface *surface, int &state, int &damp, int &thread_count);
