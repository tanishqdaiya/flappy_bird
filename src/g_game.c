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
    if (g_gamestate == g_upcomingstate)
        return;
    
    g_gamestate = g_upcomingstate;

    switch (g_gamestate) {
    case GAME_PLAYING:
        P_Reset ();
        break;

    case GAME_OVER:
        break;

    default:
        break;
    }
}
    

void G_Update (float dt)
{
    G_ApplyStateChange ();
    
    switch(g_gamestate) {
    case GAME_PLAYING:
        P_UpdateBird (dt);
        P_UpdatePipes (dt);
        break;
    case GAME_OVER:
        P_HandleGameOver ();
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
    }
}
