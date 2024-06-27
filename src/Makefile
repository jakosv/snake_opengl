PROG = snake_game
CFLAGS = -Wall -g -ansi -pedantic

LIB = ../lib/
LIBS = -L$(LIB) -lglfw3 -framework Cocoa -framework OpenGL \
	   -framework IOKit -framework QuartzCore

INCLUDE = -I ../include/

SOURCES = glad.c snake.c snake_game.c fruit.c field.c snake_body.c shader.c \
		  field_block.c main.c rectangle.c

OBJECTS = $(SOURCES:.c=.o)


.PHONY: clean


$(PROG): $(OBJECTS)
	$(CC) -o $(PROG) $(INCLUDE) $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $<

clean:
	rm $(PROG) $(OBJECTS)
