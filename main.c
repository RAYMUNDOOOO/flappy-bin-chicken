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

typedef struct Pipe
{
	// The positions from which the pipe will be rendered and their size (l x h).
	Vector2 upperPosition; 
	Vector2 lowerPosition;
	Vector2 size;
} Pipe;

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
	int JUMP_STRENGTH;
	float yVelocity;
} Bird;

Bird* InitBird(Bird* bird);

int main(void)
{

	return 0;
}

Bird* InitBird(Bird* bird)
{
	if (bird == NULL)
	{
		printf("Bird was not allocated memory properly and was a nullptr.\n");
		CloseWindow();
	}

	bird->position.x = GetScreenWidth() * 0.1;
	bird->position.y = GetScreenHeight() / 2;
	bird->size.x, bird->size.y = 30;
	bird->JUMP_STRENGTH = 600;
	bird->yVelocity = 0;

	return bird;
}
