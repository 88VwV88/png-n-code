CC := clang.exe
CCFLAGS := -std=c17

SRC := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, out/%.o, $(SRC))
BIN := encode

BUILD ?= DEBUG
DEBUG := -g -predantic -O0
RELEASE := -O2

out/%.o: src/%.c
	@$(CC) $(CCFLAGS) -c $< -o $@
	@echo [COMPILED] $@

all: $(OBJS)
	@$(CC) $(CCFLAGS) $? -o $(BIN)
	@echo [COMPILATION SUCCESS]

release: BUILD = RELEASE
release: all

test: all
	@./encode.exe

clean:
	rm -f out/*.o $(BIN)

.PHONY: all release clean