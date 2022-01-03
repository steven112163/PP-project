CFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++17 -fopenmp -O3 -I. -I./include -I./utils
PROF_FLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++17 -fopenmp -O0 -I. -I./include -I./utils -pg
CUDA_LINK_FLAGS =  -rdc=true -gencode=arch=compute_61,code=sm_61 -Xcompiler '-fPIC' -I. -I./include
CUDA_COMPILE_FLAGS = --device-c -gencode=arch=compute_61,code=sm_61 -Xcompiler '-fPIC' -g -O3 -I. -I./include

SRC = main.cpp utils/glad.c utils/object.cpp utils/ripple.cpp utils/shader.cpp utils/sphere.cpp utils/surface.cpp utils/util.cpp
EXE = ripple_simulation
PROF_EXE = ripple_simulation_prof

all: $(EXE)

$(EXE): $(SRC)
	nvcc $(CUDA_COMPILE_FLAGS) -c utils/ripple_cuda.cu -o ripple_cuda.o
	g++ $(SRC) -o main.o $(CFLAGS)
	g++ $(SRC) -o main_prof.o $(PROF_FLAGS)
	nvcc $(CUDA_LINK_FLAGS) -o $(EXE) main.o ripple_cuda.o
	nvcc $(CUDA_LINK_FLAGS) -o $(PROF_EXE) main_prof.o ripple_cuda.o

.PHONY: clean

clean:
	rm -f $(EXE) $(PROF_EXE) *.o