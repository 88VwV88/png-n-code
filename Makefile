CC := gcc.exe
CCFLAGS := -std=c17

SRC := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, out/%.o, $(SRC))
BIN := encode

BUILD ?= DEBUG
DEBUG := -g -Wall -Werror -O0
RELEASE := -O2

out/%.o: src/%.c
	@echo $@, $<, $?
	$(CC) $(CCFLAGS) $< -o $@
	@echo [COMPILED] $@

all: $(OBJS)
	@echo SOURCE FILES: $(SRC)
	@echo OBJECT FILES: $(OBJS)

	@$(CC) $(CCFLAGS) -o $(BIN) $<

	@echo [COMPILATION SUCCESS]

release: BUILD = RELEASE
release: all

.PHONY: all release