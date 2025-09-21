CC_FLAGS=-Wall -Wextra -pedantic-errors -Iraylib/src -L./raylib/src
LIBS=-lraylib -lm
CC=cc

.PHONY all: pmodoro

pmodoro: src/pmodoro.c raylib/src/libraylib.a
	$(CC) -o pmodoro $(CC_FLAGS) src/pmodoro.c $(LIBS)

raylib/src/libraylib.a:
	$(MAKE) -C raylib/src

