CC = g++
CFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

game:
	$(CC) bionic_apocalypse_main.cpp -o play -I include -L lib -l SDL2-2.0.0

clean:
	rm -f main *.o