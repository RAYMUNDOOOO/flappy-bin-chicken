#include "raylib.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

// Screen attributes.
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 900

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
		switch (applicationState)
		{
			case MAIN_MENU:
			{
				InitGame();
				applicationState = RUNNING;
			} break;

			case RUNNING:
			{
				TickGame();
				DrawGame();
			} break;

			case PAUSED:
			{
				// TODO: Implement pause menu.
			} break;

			case GAME_OVER:
			{
				// TODO: Implement game over menu.
			} break;

			case QUITTING:
			{
				CleanGame();
			} break;
		}
	}
}

void SetupWindow()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bin Chicken");
	SetExitKey(0);
	SetTargetFPS(144);
}
