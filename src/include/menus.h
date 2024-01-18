static const int MENU_WIDTH = 200;
static const int MENU_HEIGHT = 300;
static const int BUTTON_WIDTH = 180;
static const int BUTTON_HEIGHT = 30;
static const int LABEL_WIDTH = 180;
static const int LABEL_HEIGHT = 100;
static const int H_PADDING = 10;
static const int V_PADDING = 10;

void InitGui();

void DrawPanel();
void DrawLabel(char* Text);
int DrawPlayAgainButton();
int DrawQuitButton();

