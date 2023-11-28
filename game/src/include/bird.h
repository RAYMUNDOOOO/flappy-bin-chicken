typedef struct Bird
{
	Rectangle body;
	int jumpStrength;
	float yVelocity;
	int score;
	int gravity;
} Bird;

void Init(Bird* bird);
void Tick(Bird* bird, const float DELTA_TIME);
void Draw(Bird* bird);
