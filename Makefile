CFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++17 -fopenmp -O3 -I. -I./utils

SRC = main.cpp utils/*.cpp utils/glad.c
EXE = ripple_simulation

all: $(EXE)

$(EXE): $(SRC)
	g++ $(SRC) -o $(EXE) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(EXE)