typedef struct Pipe
{
	Rectangle upperBody;
	Rectangle lowerBody;
	Rectangle scoreBody;
} Pipe;

void Init(Pipe pipes[], const int numPipes);
void Tick(float deltaTime);
