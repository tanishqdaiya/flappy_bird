#include <stdio.h>
#include "raylib.h"
#include "config.h"
#include "ui_menu.h"
#include "i_interface.h"

#define OPTION_COUNT 2

static int ui_cursor = 0;
static const char *ui_options[OPTION_COUNT] = { "RESUME", "MAIN MENU" };

/* @todo: play sound */
ui_action_t UI_UpdatePause (void)
{
    if (IsKeyPressed (KEY_UP))
        ui_cursor = (ui_cursor - 1 + OPTION_COUNT) % OPTION_COUNT;
    if (IsKeyPressed (KEY_DOWN))
        ui_cursor = (ui_cursor + 1) % OPTION_COUNT;

    if (IsKeyPressed (KEY_ENTER))
    {
        switch (ui_cursor)
        {
        case 0: return UI_ACTION_RESUME;
        case 1: return UI_ACTION_MENU;
        }
    }

    return UI_ACTION_NONE;
}

void UI_DrawPause (void)
{
    int i;
    int sb_w, sb_m, p_y, p_size;
    int opt_y, opt_spacing, opt_size;
    float current_opt_y;
    Color c;
    Color bg_color;

    sb_w        = I_ConfigGetInt("ui_sb_width");
    sb_m        = I_ConfigGetInt("ui_sb_margin");
    p_y         = I_ConfigGetInt("ui_pause_y");
    p_size      = I_ConfigGetInt("ui_pause_size");
    opt_y       = I_ConfigGetInt("ui_option_y");
    opt_spacing = I_ConfigGetInt("ui_option_spacing");
    opt_size    = I_ConfigGetInt("ui_option_size");

    bg_color    = (Color){ 0, 0, 0, 180 };

    DrawRectangle (0, 0, sb_w, DESIGN_HEIGHT, bg_color);
    DrawRectangle (sb_w - 1, 0, 1, DESIGN_HEIGHT, YELLOW);
    DrawText ("PAUSED", sb_m, p_y, p_size, RAYWHITE);
    
    for (i = 0; i < OPTION_COUNT; ++i)
    {
        c = (i == ui_cursor) ? YELLOW : RAYWHITE;
        current_opt_y = (float)(opt_y + (i * opt_spacing));

        if (i == ui_cursor)
        {
            DrawText (">", sb_m, (int)current_opt_y, opt_size, YELLOW);
            DrawText (ui_options[i], sb_m + 12, (int)current_opt_y, opt_size, c);
        } else
            DrawText (ui_options[i], sb_m + 12, (int)current_opt_y, opt_size, c);
    }
}
