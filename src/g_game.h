#pragma once

typedef enum {
    GAME_PLAYING,
    GAME_OVER
} gamestate;

extern gamestate g_gamestate;

void G_RequestStateChange (gamestate state);
void G_Update (float dt);
void G_Draw (void);
