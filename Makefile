CC = g++
OBJS = src/opengl.cc src/main.cc
LINKER_FLAGS = -lGL -lGLU -lglut

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS)
