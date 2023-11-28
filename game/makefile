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

# Define include paths for required headers.
# RAYLIB_PATH adjustment for different platforms.
ifeq ($(PLATFORM_OS), WINDOWS)
	INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external 
	LDFLAGS += -L. -L$(RAYLIB_PATH)/src
	LDLIBS += -lraylib -lopengl32 -lgdi32 -lwinmm
endif
ifeq ($(PLATFORM_OS), LINUX)
	INCLUDE_PATHS = -I. -I$(RAYLIB_PATH) 
	LDFLAGS += -L$(RAYLIB_PATH)
	LDLIBS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

flappybinchicken: main.c
	$(CC) -o flappybinchicken main.c $(LDFLAGS) $(LDLIBS) $(INCLUDE_PATHS)
	@echo FlappyBinChicken successfully compiled!

.PHONY: clean

clean:
	@echo Cleaning game.
