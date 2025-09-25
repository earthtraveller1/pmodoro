CC_FLAGS=-Wall -Wextra -pedantic-errors -Ideps/raylib/src -L./deps/raylib/src
LIBS=-lraylib -lm
CC=cc

ifeq ($(OS),Windows_NT)
	LIBS=-lraylib -lm -lgdi32 -lopengl32 -lwinmm
endif

.PHONY all: pmodoro

pmodoro: src/pmodoro.c deps/raylib/src/libraylib.a
	$(CC) -o pmodoro $(CC_FLAGS) src/pmodoro.c $(LIBS)

deps/raylib/src/libraylib.a:
	$(MAKE) -C deps/raylib/src

