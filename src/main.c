#include "raylib.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

// Screen attributes.
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef enum 
{
	MAIN_MENU,
	RUNNING,
	PAUSED,
	GAME_OVER,
	QUITTING
} ApplicationState;

// Declarations.
void SetupWindow();


int main(void)
{
	SetupWindow();
	ApplicationState applicationState = MAIN_MENU;

	while (!WindowShouldClose() && applicationState != QUITTING)
	{
		if (IsKeyPressed(KEY_ESCAPE)) applicationState = QUITTING;
		switch (applicationState)
		{
			case MAIN_MENU:
			{
				InitGame();
				applicationState = RUNNING;
			} break;

			case RUNNING:
			{
				TickGame(GetFrameTime());

				BeginDrawing();
				DrawFPS(10, 10);
				ClearBackground(RAYWHITE);
				DrawGame();
				EndDrawing();
			} break;

			case PAUSED:
			{
				// TODO: Implement pause menu.
			} break;

			case GAME_OVER:
			{
				// TODO: Implement game over menu.
			} break;
		}
	}

	CleanGame();
	CloseWindow();
	return 0;
}

void SetupWindow()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bin Chicken");
	SetExitKey(0);
	SetTargetFPS(144);
}
