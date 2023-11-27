typedef struct Pipe
{
	Rectangle upperBody;
	Rectangle lowerBody;
	Rectangle scoreBody;
} Pipe;

void Init(Pipe pipes[], const int NUM_PIPES);
void Tick(Pipe pipes[], const float DELTA_TIME);
void Draw(Pipe pipes[], const int NUM_PIPES);
