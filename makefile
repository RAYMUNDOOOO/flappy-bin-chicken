RAYLIB_DIR := raylib
SRC_DIR := game/src
BUILD_DIR = _build
PROJECTS = raylib $(TARGET)
CC := gcc
LDLIBS = 
LDFLAGS =
SRC_FILES = main.c game.c bird.c pipe.c
OBJ_FILES = $(patsubst %.c,%.o,$(addprefix $(BUILD_DIR)/, $(SRC_FILES)))
TARGET = flappybinchicken

# Configuring flags for detected platform.
ifeq ($(OS), Windows_NT)
	INCLUDE_PATHS +=  -I$(SRC_DIR)/include -I$(RAYLIB_DIR)/src -I$(RAYLIB_DIR)/src/external
	LDFLAGS += -L$(RAYLIB_DIR)/src
	LDLIBS += -lraylib -lopengl32 -lgdi32 -lwinmm
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		INCLUDE_PATHS += -I$(SRC_DIR)/include -I$(RAYLIB_DIR)
		LDFLAGS += -L$(RAYLIB_DIR)
		LDLIBS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	endif
endif

.PHONY: all clean $(PROJECTS)

all: $(PROJECTS)

raylib:
	$(info Building raylib...)
	@$(MAKE) --no-print-directory -C $(RAYLIB_DIR)/src -f makefile

$(TARGET): $(OBJ_FILES) | $(BUILD_DIR)
	$(info Building $(TARGET))
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(INCLUDE_PATHS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(filter-out main.o, $(OBJ_FILES)) | $(BUILD_DIR)
	$(info Building main.o)
	$(CC) -o $@ -c $^ $(LDFLAGS) $(LDLIBS) $(INCLUDE_PATHS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(info Building pre-requisites of main.o)
	$(CC) -o $@ -c $< $(LDFLAGS) $(LDLIBS) $(INCLUDE_PATHS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
