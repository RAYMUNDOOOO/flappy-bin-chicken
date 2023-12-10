#include "raylib.h"

typedef struct Pipe
{
	Rectangle upperBody;
	Rectangle lowerBody;
	Rectangle scoreBody;
} Pipe;

void InitPipe(Pipe* pipes, int numPipes);
void TickPipe(Pipe* pipes, int numPipes, const float DELTA_TIME);
void DrawPipe(Pipe* pipes, int numPipes);
int GetNumPipes(const int SCREEN_W);
