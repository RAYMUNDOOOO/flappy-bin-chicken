typedef struct Pipe
{
	Rectangle upperBody;
	Rectangle lowerBody;
	Rectangle scoreBody;
} Pipe;

void InitPipe(Pipe pipes[], const int NUM_PIPES);
void TickPipe(Pipe pipes[], const float DELTA_TIME);
void DrawPipe(Pipe pipes[]);
int GetNumPipes(cont int SCREEN_W);
