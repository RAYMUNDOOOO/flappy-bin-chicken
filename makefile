RAYLIB_DIR := raylib
SRC_DIR := src
BUILD_DIR = _build
PROJECTS = raylib $(TARGET)
CC := gcc
LDLIBS = 
LDFLAGS =
SRC_FILES = main.c game.c bird.c pipe.c
OBJ_FILES = $(patsubst %.c,%.o,$(addprefix $(BUILD_DIR)/, $(SRC_FILES)))
TARGET = flappybinchicken
CLEAN_COMMAND =

# Configuring flags for detected platform.
ifeq ($(OS), Windows_NT)
	INCLUDE_PATHS +=  -I$(SRC_DIR)/include -I$(RAYLIB_DIR)/src -I$(RAYLIB_DIR)/src/external
	LDFLAGS += -L$(RAYLIB_DIR)/src
	LDLIBS += -lraylib -lopengl32 -lgdi32 -lwinmm
	CLEAN_COMMAND += del $(BUILD_DIR) /s /q $(TARGET)*
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		INCLUDE_PATHS += -I$(SRC_DIR)/include -I$(RAYLIB_DIR)
		LDFLAGS += -L$(RAYLIB_DIR)
		LDLIBS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
		CLEAN_COMMAND += rm -rf $(BUILD_DIR) $(TARGET)*
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
	$(CC) -o $@ -c $^ $(LDFLAGS) $(LDLIBS) $(INCLUDE_PATHS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -o $@ -c $< $(LDFLAGS) $(LDLIBS) $(INCLUDE_PATHS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	$(info Cleaning generated object files and executables.)
	$(CLEAN_COMMAND)
