#include "game.h"
#include "bird.h"
#include "pipe.h"
#include "raylib.h"

Bird* bird;
Pipe* pipes[];

void InitGame()
{
	bird = (Bird*)malloc(sizeof(Bird));
	InitBird(bird);

	const int NUM_PIPES = GetNumPipes(GetScreenWidth());
	pipes = malloc(NUM_PIPES * sizeof(Pipe));
	InitPipe(*pipes, NUM_PIPES);
}

void TickGame(const float DELTA_TIME)
{
	TickBird(bird, DELTA_TIME);
	TickPipe(*pipes, DELTA_TIME);
}

void DrawGame()
{
	DrawBird(bird);
	DrawPipe(*pipes);
}
