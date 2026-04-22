#pragma once

typedef enum {
    GAME_PLAYING,
    GAME_OVER,
    GAME_PAUSED,
    GAME_MENU
} gamestate;

extern gamestate g_gamestate;

void G_RequestStateChange (gamestate state);
void G_Update (float dt);
void G_Draw (void);
