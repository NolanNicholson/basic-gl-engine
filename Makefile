CC = g++
OBJS = $(wildcard src/*.cc)
LINKER_FLAGS = -lGL -lGLU -lglut

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS)
