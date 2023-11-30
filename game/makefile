# Determine the platform OS.
ifeq ($(OS), Windows_NT)
	PLATFORM_OS = WINDOWS
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		PLATFORM_OS = LINUX
	endif
endif

CC = gcc
LDLIBS =
LDFLAGS =
RAYLIB_PATH = ../raylib
SRC_FILES = src/main.c src/game.c src/bird.c src/pipe.c
OBJ_FILES = $(SRC_FILES:.c=.o)
TARGET = flappybinchicken

# Define include paths for required headers.
# RAYLIB_PATH adjustment for different platforms.
ifeq ($(PLATFORM_OS), WINDOWS)
	INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -Isrc/include
	LDFLAGS += -L. -L$(RAYLIB_PATH)/src
	LDLIBS += -lraylib -lopengl32 -lgdi32 -lwinmm
endif
ifeq ($(PLATFORM_OS), LINUX)
	INCLUDE_PATHS = -I. -I$(RAYLIB_PATH) -Isrc/include
	LDFLAGS += -L$(RAYLIB_PATH)
	LDLIBS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(INCLUDE_PATHS)

main.o: main.c game.o pipe.o bird.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(INCLUDE_PATHS)

%.o: %.c
	$(CC) -o $@ -c $< $(LDFLAGS) $(LDLIBS) $(INCLUDE_PATHS)

.PHONY: clean
clean:
	@echo Cleaning game.
