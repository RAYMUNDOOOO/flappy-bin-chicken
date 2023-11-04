#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define GRAVITY 980 // To effect how the bird flies.

// Screen attributes.
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

// Pipe attributes.
#define PIPE_DELTA_X 240
#define PIPE_DELTA_Y 125
#define PIPE_WIDTH 30
#define PIPE_MS 1000

typedef struct Pipe
{
	// The positions from which the pipe will be rendered and their size (l x h).
	Vector2 upperPosition; 
	Vector2 lowerPosition;
} Pipe;

int GetNumPipes(const int screenWidth, const int pipeWidth, const int pipeDeltaX);
void InitPipes(Pipe pipes[], const int numPipes);
void MovePipes(Pipe pipes[], const int numPipes, const float deltaTime);
void DrawPipes(Pipe pipes[], const int numPipes);

// Bird attributes.
typedef struct Bird
{
	// The position from which the bird will be rendered and its size (l x h).
	Vector2 position;
	Vector2 size;

	/*
	 * The JUMP_STRENGTH will be used to set the vertical velocity of the bird
	 * and each tick, GRAVITY will reduce the yVelocity to simulate it
	 * dropping in the air.
	 */
	int jumpStrength;
	float yVelocity;
} Bird;

Bird* InitBird();
void Jump(Bird* bird);
void ApplyGravity(Bird* bird, float deltaTime);

int main(void)
{
	// Initialise the window.
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bin Chicken");
	SetTargetFPS(240);
	
	// Initialise entities in the game (bird and pipes).
	Bird* player = InitBird();

	const int numPipes = GetNumPipes(GetScreenWidth(), PIPE_WIDTH, PIPE_DELTA_X);
	Pipe pipes[numPipes];
	InitPipes(pipes, numPipes);
	
	// Tick.
	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			Jump(player);
		}

		// Applying movement to bird and pipes.
		ApplyGravity(player, GetFrameTime());
		MovePipes(pipes, numPipes, GetFrameTime());

		// Drawing.
		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangleV(player->position, player->size, GOLD);
		DrawPipes(pipes, numPipes);
		EndDrawing();
	}

	free(player);
	player = NULL;

	CloseWindow();
	return 0;
}

Bird* InitBird()
{
	Bird* bird = (Bird*)malloc(sizeof(Bird));
	if (bird != NULL)
	{
		bird->position.x = GetScreenWidth() * 0.1;
		bird->position.y = GetScreenHeight() / 2;
		bird->size.x = 30;
		bird->size.y = 30;
		bird->jumpStrength = 600;
		bird->yVelocity = 0;
	}

	return bird;
}

void Jump(Bird* bird)
{
	if (bird != NULL) bird->yVelocity = bird->jumpStrength;
}

void ApplyGravity(Bird* bird, float deltaTime)
{
	if (bird != NULL)
	{
		bird->position.y -= bird->yVelocity * deltaTime;
		bird->yVelocity -= GRAVITY * deltaTime;
	}
}

int GetNumPipes(const int screenWidth, const int pipeWidth, const int pipeDeltaX)
{
	return screenWidth / (pipeWidth + pipeDeltaX);
}

// Initialise the drawing position of the pipes based on the screen width, height and the gaps between them.
void InitPipes(Pipe pipes[], const int numPipes)
{
	if (sizeof(*pipes) > 0)
	{
		const int middleOfScreen = GetScreenHeight() / 2; // We will determine the drawing positions of the pipes from this.
		for (int i = 0; i < numPipes; ++i)
		{
			pipes[i].upperPosition.x = GetScreenWidth() + (i * (PIPE_WIDTH + PIPE_DELTA_X));
			pipes[i].lowerPosition.x = GetScreenWidth() + (i * (PIPE_WIDTH + PIPE_DELTA_X));

			pipes[i].upperPosition.y = middleOfScreen - (PIPE_DELTA_Y / 2) - GetScreenHeight();
			pipes[i].lowerPosition.y = middleOfScreen + (PIPE_DELTA_Y / 2);
		}
	}
}

void MovePipes(Pipe pipes[], const int numPipes, const float deltaTime)
{
	if (sizeof(*pipes) > 0)
	{
		for (int i = 0; i < numPipes; ++i)
		{
			pipes[i].upperPosition.x -= PIPE_MS * deltaTime;
			pipes[i].lowerPosition.x -= PIPE_MS * deltaTime;

			if (pipes[i].upperPosition.x <= 0)
			{
				pipes[i].upperPosition.x = GetScreenWidth();
				pipes[i].lowerPosition.x = GetScreenWidth();
			}
		}
	}
}

void DrawPipes(Pipe pipes[], const int numPipes)
{
	if (sizeof(*pipes) > 0)
	{
		for (int i = 0; i < numPipes; ++i)
		{
			DrawRectangle(pipes[i].upperPosition.x, pipes[i].upperPosition.y, PIPE_WIDTH, GetScreenHeight(), RAYWHITE);
			DrawRectangle(pipes[i].lowerPosition.x, pipes[i].lowerPosition.y, PIPE_WIDTH, GetScreenHeight(), RAYWHITE);
		}
	}
}
