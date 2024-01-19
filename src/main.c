#include "raylib.h"
#include "main.h"
#include "menus.h"
#include "game.h"
#include <stdio.h>

// Screen attributes.
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

typedef enum 
{
	MAIN_MENU,
	RUNNING,
	PAUSED,
	GAME_OVER,
	QUITTING
} ApplicationState;
ApplicationState applicationState = MAIN_MENU;

// Declarations.
void SetupWindow();
void DrawScore();

int main(void)
{
	SetupWindow();

	while (!WindowShouldClose() && applicationState != QUITTING)
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawFPS(10, 10);

		switch (applicationState)
		{
			case MAIN_MENU:
			{
				InitGame();
				applicationState = RUNNING;
			} break;

			case RUNNING:
			{
                if (IsKeyPressed(KEY_ESCAPE)) SetGamePaused();
				TickGame(GetFrameTime());
				DrawGame();
			} break;

			case PAUSED:
			{
                if (IsKeyPressed(KEY_ESCAPE)) SetGameRunning();

                DrawGame();
			} break;

			case GAME_OVER:
			{
                DrawGame();
                DrawPanel();
                DrawLabel("GAME OVER");
                if (DrawPlayAgainButton()) RestartGame();
                if (DrawQuitButton()) applicationState = QUITTING;
			} break;

            case QUITTING:
            {
            } break;
		}

		DrawScore();
		EndDrawing();
	}

	CleanGame();
	CloseWindow();
	return 0;
}

void SetupWindow()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bin Chicken");
    InitGui();
	SetExitKey(0);
	SetTargetFPS(144);
}

void DrawScore()
{
	char scoreStr[8];
	sprintf(scoreStr, "%d", GetScore());
	DrawText(scoreStr, GetScreenWidth() / 2, GetScreenHeight() * 0.1, 32, BLACK);
}

void SetGamePaused()
{
    applicationState = PAUSED;
}

void SetGameRunning()
{
    applicationState = RUNNING;
}

void GameOver()
{
    // TODO: Present game over menu.
    applicationState = GAME_OVER; 
}
