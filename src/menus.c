#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "menus.h"

Rectangle panel;
Rectangle label;
Rectangle buttonPlayAgain;
Rectangle buttonQuit;

void InitGui()
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    panel = (Rectangle){ GetScreenWidth() / 2 - 100, GetScreenHeight() * 0.4, MENU_WIDTH, MENU_HEIGHT };
    label = (Rectangle){ GetScreenWidth() / 2 - 100 + H_PADDING, GetScreenHeight() * 0.4 + V_PADDING, LABEL_WIDTH, LABEL_HEIGHT };
    buttonPlayAgain = (Rectangle){ GetScreenWidth() / 2 - 100 + H_PADDING, GetScreenHeight() * 0.4 + V_PADDING + LABEL_HEIGHT + V_PADDING, BUTTON_WIDTH, BUTTON_HEIGHT };
    buttonQuit = (Rectangle){ GetScreenWidth() / 2 - 100 + H_PADDING, GetScreenHeight() * 0.4 + V_PADDING + LABEL_HEIGHT + V_PADDING + 30, BUTTON_WIDTH, BUTTON_HEIGHT };
}

void DrawStartScreenMenu()
{
}

void DrawGameOverMenu()
{
    GuiPanel(panel, "");
    GuiLabel(label, "GAME OVER");
    GuiLabelButton(buttonPlayAgain, "PLAY AGAIN");
    GuiLabelButton(buttonQuit, "QUIT");
}

void DrawPauseMenu()
{
}
