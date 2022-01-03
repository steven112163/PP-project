#include "../include/ripple_cuda.h"

#define NUM_THREADS 25
#define NUM_STREAMS 8

__global__ void vertex_kernel(float *d_current_state,
                              float *d_next_state,
                              int offset, float damp,
                              int surface_size) {
    int x = blockIdx.x * blockDim.x + threadIdx.x, z_in_next_state = blockIdx.y * blockDim.y + threadIdx.y;
    int z = z_in_next_state + offset;
    int surface_stride = 3 * surface_size;
    float new_y = -d_next_state[3 * blockDim.x * z_in_next_state + 3 * x + 1];

    if (x == 0 && z == 0) {
        new_y = (d_current_state[surface_stride * z + 3 * (x + 1) + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * (x + 1) + 1]) / 1.5f;
    } else if (x == surface_size - 1 && z == 0) {
        new_y = (d_current_state[surface_stride * z + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * (x - 1) + 1]) / 1.5f;
    } else if (x == 0 && z == surface_size - 1) {
        new_y = (d_current_state[surface_stride * z + 3 * (x + 1) + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * (x + 1) + 1]) / 1.5f;
    } else if (x == surface_size - 1 && z == surface_size - 1) {
        new_y = (d_current_state[surface_stride * z + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * (x - 1) + 1]) / 1.5;
    } else if (z == 0) {
        new_y = (d_current_state[surface_stride * z + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * z + 3 * (x + 1) + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * (x + 1) + 1]) / 2.5f;
    } else if (x == 0) {
        new_y = (d_current_state[surface_stride * z + 3 * (x + 1) + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * (x + 1) + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * (x + 1) + 1]) / 2.5f;
    } else if (z == surface_size - 1) {
        new_y = (d_current_state[surface_stride * z + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * z + 3 * (x + 1) + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * (x + 1) + 1]) / 2.5f;
    } else if (x == surface_size - 1) {
        new_y = (d_current_state[surface_stride * z + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * (x - 1) + 1]) / 2.5f;
    } else {
        new_y = (d_current_state[surface_stride * z + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * z + 3 * (x + 1) + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * x + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * (z - 1) + 3 * (x + 1) + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * (x - 1) + 1] +
                 d_current_state[surface_stride * (z + 1) + 3 * (x + 1) + 1]) / 4.0f;
    }

    new_y -= new_y / damp;
    d_next_state[3 * blockDim.x * z_in_next_state + 3 * x] = d_current_state[surface_stride * z + 3 * x];
    d_next_state[3 * blockDim.x * z_in_next_state + 3 * x + 1] = new_y;
    d_next_state[3 * blockDim.x * z_in_next_state + 3 * x + 2] = d_current_state[surface_stride * z + 3 * x + 2];
}

__device__ float3 operator+(const float3 &a, const float3 &b) {
    return make_float3(a.x + b.x, a.y + b.y, a.z + b.z);
}

__device__ float3 operator-(const float3 &a, const float3 &b) {
    return make_float3(a.x - b.x, a.y - b.y, a.z - b.z);
}

__device__ float3 vec_cross(const float3 &a, const float3 &b) {
    return make_float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

__device__ float3 vec_normalize(const float3 &a) {
    float length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return make_float3(a.x / length, a.y / length, a.z / length);
}

__global__ void normal_kernel(float *d_current_state,
                              float *d_normal,
                              int offset,
                              int surface_size) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int z_in_normal = blockIdx.y * blockDim.y + threadIdx.y;
    int z = z_in_normal + offset;
    int surface_stride = 3 * surface_size;

    float3 point = make_float3(d_current_state[surface_stride * z + 3 * x],
                               d_current_state[surface_stride * z + 3 * x + 1],
                               d_current_state[surface_stride * z + 3 * x + 2]);
    float3 new_normal, neg_z, pos_z, neg_x, pos_x;

    if (x == 0 && z == 0) {
        pos_z = make_float3(d_current_state[surface_stride * (z + 1) + 3 * x],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 2]) - point;
        pos_x = make_float3(d_current_state[surface_stride * z + 3 * (x + 1)],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 2]) - point;
        new_normal = vec_cross(pos_z, pos_x);
    } else if (x == surface_size - 1 && z == 0) {
        pos_z = make_float3(d_current_state[surface_stride * (z + 1) + 3 * x],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 2]) - point;
        neg_x = make_float3(d_current_state[surface_stride * z + 3 * (x - 1)],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 2]) - point;
        new_normal = vec_cross(neg_x, pos_z);
    } else if (x == 0 && z == surface_size - 1) {
        neg_z = make_float3(d_current_state[surface_stride * (z - 1) + 3 * x],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 2]) - point;
        pos_x = make_float3(d_current_state[surface_stride * z + 3 * (x + 1)],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 2]) - point;
        new_normal = vec_cross(pos_x, neg_z);
    } else if (x == surface_size - 1 && z == surface_size - 1) {
        neg_z = make_float3(d_current_state[surface_stride * (z - 1) + 3 * x],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 2]) - point;
        neg_x = make_float3(d_current_state[surface_stride * z + 3 * (x - 1)],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 2]) - point;
        new_normal = vec_cross(neg_z, neg_x);
    } else if (z == 0) {
        pos_z = make_float3(d_current_state[surface_stride * (z + 1) + 3 * x],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 2]) - point;
        neg_x = make_float3(d_current_state[surface_stride * z + 3 * (x - 1)],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 2]) - point;
        pos_x = make_float3(d_current_state[surface_stride * z + 3 * (x + 1)],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 2]) - point;
        new_normal = vec_cross(neg_x, pos_z) + vec_cross(pos_z, pos_x);
    } else if (x == 0) {
        neg_z = make_float3(d_current_state[surface_stride * (z - 1) + 3 * x],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 2]) - point;
        pos_z = make_float3(d_current_state[surface_stride * (z + 1) + 3 * x],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 2]) - point;
        pos_x = make_float3(d_current_state[surface_stride * z + 3 * (x + 1)],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 2]) - point;
        new_normal = vec_cross(pos_z, pos_x) + vec_cross(pos_x, neg_z);
    } else if (z == surface_size - 1) {
        neg_z = make_float3(d_current_state[surface_stride * (z - 1) + 3 * x],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 2]) - point;
        neg_x = make_float3(d_current_state[surface_stride * z + 3 * (x - 1)],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 2]) - point;
        pos_x = make_float3(d_current_state[surface_stride * z + 3 * (x + 1)],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 2]) - point;
        new_normal = vec_cross(pos_x, neg_z) + vec_cross(neg_z, neg_x);
    } else if (x == surface_size - 1) {
        neg_z = make_float3(d_current_state[surface_stride * (z - 1) + 3 * x],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 2]) - point;
        pos_z = make_float3(d_current_state[surface_stride * (z + 1) + 3 * x],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 2]) - point;
        neg_x = make_float3(d_current_state[surface_stride * z + 3 * (x - 1)],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 2]) - point;
        new_normal = vec_cross(neg_z, neg_x) + vec_cross(neg_x, pos_z);
    } else {
        neg_z = make_float3(d_current_state[surface_stride * (z - 1) + 3 * x],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z - 1) + 3 * x + 2]) - point;
        pos_z = make_float3(d_current_state[surface_stride * (z + 1) + 3 * x],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 1],
                            d_current_state[surface_stride * (z + 1) + 3 * x + 2]) - point;
        neg_x = make_float3(d_current_state[surface_stride * z + 3 * (x - 1)],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x - 1) + 2]) - point;
        pos_x = make_float3(d_current_state[surface_stride * z + 3 * (x + 1)],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 1],
                            d_current_state[surface_stride * z + 3 * (x + 1) + 2]) - point;
        new_normal = vec_cross(neg_z, neg_x) + vec_cross(neg_x, pos_z) +
                     vec_cross(pos_z, pos_x) + vec_cross(pos_x, neg_z);
    }

    new_normal = vec_normalize(new_normal);
    d_normal[3 * blockDim.x * z + 3 * x] = new_normal.x;
    d_normal[3 * blockDim.x * z + 3 * x + 1] = new_normal.y;
    d_normal[3 * blockDim.x * z + 3 * x + 2] = new_normal.z;
}

void ripple_cuda(Surface *surface, int &state, int &dampI) {
    const int surface_size = surface->get_surface_size();
    const int vertices_size = surface->get_vertices_size() * sizeof(float);
    float damp = float(dampI);

    // Compute grid step and size
    int grid_step = surface_size / NUM_STREAMS;
    int grid_size = vertices_size / NUM_STREAMS;

    // Allocate device memory for vertices
    float *d_current_state, *d_next_state;
    cudaMalloc(&d_current_state, vertices_size);
    cudaMalloc(&d_next_state, grid_size);
    cudaHostRegister(surface->vertices[0], vertices_size, cudaHostRegisterPortable);
    cudaHostRegister(surface->vertices[1], vertices_size, cudaHostRegisterPortable);

    // Copy current state to device
    cudaMemcpy(d_current_state, surface->vertices[state], vertices_size, cudaMemcpyHostToDevice);

    // Create streams
    cudaStream_t streams[NUM_STREAMS];
    for (int i = 0; i < NUM_STREAMS; i++)
        cudaStreamCreate(&streams[i]);

    // Start kernels
    dim3 block(NUM_THREADS, NUM_THREADS);
    dim3 grid(surface_size / NUM_THREADS, grid_step / NUM_THREADS);
    int offset = 0;
    for (int i = 0; i < NUM_STREAMS; i++) {
        cudaMemcpyAsync(d_next_state + vertices_size * offset,
                        surface->vertices[1 - state] + vertices_size * offset,
                        grid_size, cudaMemcpyHostToDevice, streams[i]);
        vertex_kernel<<<grid, block, 0, streams[i]>>>(
                d_current_state,
                d_next_state,
                offset, damp,
                surface_size
        );
        cudaMemcpyAsync(surface->vertices[1 - state] + vertices_size * offset,
                        d_next_state + vertices_size * offset,
                        grid_size, cudaMemcpyDeviceToHost, streams[i]);
        offset += grid_step;
    }

    // Free vertices space
    cudaDeviceSynchronize();
    cudaHostUnregister(surface->vertices[state]);
    cudaFree(d_next_state);

    // Flip state
    state = 1 - state;

    // Allocate device memory for normals
    float *d_normal;
    cudaMalloc(&d_normal, grid_size);
    cudaHostRegister(surface->normals.data(), vertices_size, cudaHostRegisterPortable);

    // Copy current state to device
    cudaMemcpy(d_current_state, surface->vertices[state], vertices_size, cudaMemcpyHostToDevice);

    // Start kernels
    offset = 0;
    for (int i = 0; i < NUM_STREAMS; i++) {
        normal_kernel<<<grid, block, 0, streams[i]>>>(
                d_current_state,
                d_normal,
                offset,
                surface_size
        );
        cudaMemcpyAsync(surface->normals.data() + vertices_size * offset,
                        d_normal + vertices_size * offset,
                        grid_size, cudaMemcpyDeviceToHost, streams[i]);
        offset += grid_step;
    }

    // Free space
    cudaDeviceSynchronize();
    for (int i = 0; i < NUM_STREAMS; i++)
        cudaStreamDestroy(streams[i]);
    cudaHostUnregister(surface->vertices[state]);
    cudaHostUnregister(surface->normals.data());
    cudaFree(d_next_state);
    cudaFree(d_normal);
}