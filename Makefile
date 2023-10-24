CC = gcc
CFLAGS = -W -Wall -ansi -std=c99
LIBS = -L./SDL2_ttf/.libs
LDFLAGS = `sdl2-config --cflags --libs`
EXEC = main
SRC = src/main.c src/image.c
OBJ = $(SRC:.c=.o)
all: $(EXEC)
main: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)