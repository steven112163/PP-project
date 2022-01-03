CFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++17 -fopenmp -O3 -I. -I./include -I./utils
PROF_FLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++17 -fopenmp -O0 -I. -I./include -I./utils -pg

SRC = main.cpp utils/*.cpp utils/glad.c
EXE = ripple_simulation
PROF_EXE = ripple_simulation_prof

all: $(EXE)

$(EXE): $(SRC)
	g++ $(SRC) -o $(EXE) $(CFLAGS)
	g++ $(SRC) -o $(PROF_EXE) $(PROF_FLAGS)

.PHONY: clean

clean:
	rm -f $(EXE) $(PROF_EXE)