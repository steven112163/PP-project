CFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -std=c++17 -fopenmp -O3
SRC = main.cpp glad.c
EXE = ripple_simulation

all: $(SRC)
	g++ $(SRC) -o $(EXE) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(EXE)