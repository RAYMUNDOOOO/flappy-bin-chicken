#include "game.h"
#include "bird.h"
#include "pipe.h"
#include "raylib.h"

Bird* bird;
Pipe* pipes[];

void Init()
{
	bird = (Bird*)malloc(sizeof(Bird));
	Init(bird);

	const int NUM_PIPES = GetNumPipes(GetScreenWidth());
	pipes = malloc(NUM_PIPES * sizeof(Pipe));
	Init(*pipes, NUM_PIPES);
}

void Tick(const float DELTA_TIME)
{
	Tick(bird, DELTA_TIME);
	Tick(*pipes, DELTA_TIME);
}

void Draw()
{
	Draw(bird);
	Draw(*pipes);
}
