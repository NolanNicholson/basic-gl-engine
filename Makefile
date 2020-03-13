CC = g++
OBJS = $(wildcard src/*.cc)
LINKER_FLAGS = -lGLEW -lGL -lGLU -lglfw

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS)
