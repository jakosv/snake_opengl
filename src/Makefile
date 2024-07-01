PROG = snake_game
CFLAGS = -Wall -g -ansi -pedantic

#LIB = ../lib/
#LIBS = -L$(LIB) -lglfw3
LIBS = -lglfw3

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS += -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
endif
ifeq ($(UNAME_S),Darwin)
	LIBS += -framework Cocoa -framework OpenGL -framework IOKit \
			-framework QuartzCore
endif

INCLUDE = -I ../include/

SOURCES = glad.c snake.c snake_game.c fruit.c field.c snake_body.c shader.c \
		  field_block.c main.c rectangle.c turn_queue.c

OBJECTS = $(SOURCES:.c=.o)


.PHONY: clean


$(PROG): $(OBJECTS)
	$(CC) -o $(PROG) $(INCLUDE) $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $<

clean:
	rm $(PROG) $(OBJECTS)
