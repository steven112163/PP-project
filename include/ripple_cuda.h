#include "surface.h"

#include <cuda.h>
#include "cublas_v2.h"
#include <cstdlib>
#include <cmath>

#define PI 3.1415926

void ripple_cuda(Surface *surface, int &state, int &dampI);