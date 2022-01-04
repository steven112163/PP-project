NVCC = /usr/local/cuda-11.5/bin/nvcc
CXX = g++

INCLUDES = -I. -I./include -I./utils -I/usr/local/cuda/include
LIBRARIES = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -L/usr/local/cuda/lib64 -lcudart

CFLAGS = $(INCLUDES) $(LIBRARIES) -std=c++17 -fopenmp -O3
CUDA_LINK_FLAGS =  -rdc=true -gencode=arch=compute_86,code=sm_86 -Xcompiler '-fPIC' $(LIBRARIES)
CUDA_COMPILE_FLAGS = --device-c -gencode=arch=compute_86,code=sm_86 -Xcompiler '-fPIC' -g -O3 $(INCLUDES)

SRC = main.cpp utils/*.c utils/*.cpp
EXE = ripple_simulation

all:
	nvcc $(CUDA_COMPILE_FLAGS) -c utils/ripple_cuda.cu -o ripple_cuda.o
	g++ -c $(SRC) $(CFLAGS)
	nvcc $(CUDA_LINK_FLAGS) -o $(EXE) *.o

.PHONY: clean

clean:
	rm -f $(EXE) $(PROF_EXE) *.o