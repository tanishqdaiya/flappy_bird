#pragma once

typedef enum {
    UI_ACTION_NONE,
    UI_ACTION_RESUME,
    UI_ACTION_MENU
} ui_action_t;

ui_action_t UI_UpdatePause (void);
void UI_DrawPause (void);
void UI_DrawMainMenu (void);
