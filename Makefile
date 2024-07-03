CC := gcc.exe
CCFLAGS := -std=c17

SRC := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, out/%.o, $(SRC))
BIN := encode.exe

BUILD ?= DEBUG
DEBUG := -g -Wall -Werror -O0
RELEASE := -O2

out/%.o: src/%.c
	@echo $(OBJS) $(SRC)
	$(CC) $(CCFLAGS) -c $< -o $@
	@echo [COMPILED] $@

all: $(OBJS)
	$(CC) $(CCFLAGS) $< -o $(BIN)

	@echo [COMPILATION SUCCESS]

release: BUILD = RELEASE
release: all

clean:
	rm -f out/*.o $(BIN)

.PHONY: all release clean