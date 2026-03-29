#include "g_game.h"
#include "r_render.h"
#include "p_play.h"

gamestate g_gamestate = GAME_PLAYING;
gamestate g_upcomingstate = GAME_PLAYING;

void G_RequestStateChange (gamestate state)
{
    g_upcomingstate = state;
}

static void G_ApplyStateChange (void)
{
    gamestate oldstate;
    
    if (g_gamestate == g_upcomingstate)
        return;

    oldstate = g_gamestate;
    g_gamestate = g_upcomingstate;

    switch (g_gamestate) {
    case GAME_PLAYING:
        if (oldstate == GAME_OVER)
            P_Reset ();
        break;

    case GAME_OVER:
        break;

    case GAME_PAUSED:
        break;

    default:
        break;
    }
}
    

void G_Update (float dt)
{
    G_ApplyStateChange ();

    if (IsKeyPressed (KEY_ESCAPE))
    {
        if (g_gamestate == GAME_PLAYING)
            G_RequestStateChange (GAME_PAUSED);
        else if (g_gamestate == GAME_PAUSED)
            G_RequestStateChange (GAME_PLAYING);
    }
    
    switch(g_gamestate) {
    case GAME_PLAYING:
        P_UpdateBird (dt);
        P_UpdatePipes (dt);
        break;
    case GAME_OVER:
        P_HandleGameOver ();
        break;
    case GAME_PAUSED:
        P_HandlePaused ();
        break;
    }
}

void G_Draw (void)
{
    switch(g_gamestate) {
    case GAME_PLAYING:
        R_DrawBackground ();
        R_DrawBird ();
        R_DrawPipes ();
        break;
    case GAME_OVER:
        R_DrawBackground ();
        R_DrawBird ();
        R_DrawPipes ();
        R_DrawGameOver ();
        break;
    case GAME_PAUSED:
        R_DrawBackground ();
        R_DrawBird ();
        R_DrawPipes ();
        R_DrawPaused ();
        break;
    }
}
