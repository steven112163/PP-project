CFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++17 -fopenmp -O3 -I. -I./include -I./utils
PROF_FLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++17 -fopenmp -O0 -I. -I./include -I./utils -pg

SRC = main.cpp utils/glad.c utils/object.cpp utils/ripple.cpp utils/shader.cpp utils/sphere.cpp utils/surface.cpp utils/util.cpp
EXE = ripple_simulation
PROF_EXE = ripple_simulation_prof

all: $(EXE)

$(EXE): $(SRC)
	g++ $(SRC) -o $(EXE) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(EXE) $(PROF_EXE)