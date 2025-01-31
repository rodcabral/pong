FLAGS = -Wall -Wextra -O3
LIBRARIES = -lSDL2 -lSDL2_ttf

pong: $(wildcard ./src/*.c) $(wildcard ./src/*.h)
	$(CC) $(FLAGS) $(wildcard ./src/*.c) $(LIBRARIES) -o pong
