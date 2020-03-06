CC = g++
OBJS = $(wildcard src/*.cc)
LINKER_FLAGS = -lSDL2 -lGLEW -lGL -lGLU -lglut

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS)
