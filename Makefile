CC = g++
OBJS = $(wildcard src/*.cc)
LINKER_FLAGS = -lSDL2 -lGLEW -lGL -lGLU -lglfw

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS)
