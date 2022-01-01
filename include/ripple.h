#include "surface.h"

#include <omp.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

#define PI 3.1415926
#define DAMP 20

void ripple_serial(Surface *surface, int &state);

void ripple_omp(Surface *surface, int &state, int num_threads);
