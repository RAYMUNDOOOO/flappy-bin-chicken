RAYLIB_SRC_DIR = raylib/src
GAME_DIR = game
PROJECTS := raylib game

.PHONY: all clean $(PROJECTS)

all: $(PROJECTS)

# Builds makefile found in raylib/src.
raylib:
	@echo building raylib
	@${MAKE} --no-print-directory -C $(RAYLIB_SRC_DIR) -f makefile

# Builds makefile found in game/.
game:
	@echo building game
	@${MAKE} --no-print-directory -C $(GAME_DIR) -f makefile

# Deletes generated object files and executables.
clean:
	@echo cleaning raylib
	@${MAKE} --no-print-directory -C $(RAYLIB_SRC_DIR) -f makefile clean
	@echo cleaning game
	@${MAKE} --no-print-directory -C $(GAME_DIR) -f makefile clean
