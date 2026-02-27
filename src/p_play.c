#include <stdlib.h>

#include "raylib.h"

#include "config.h"
#include "p_play.h"
#include "g_game.h"

static bird_t g_bird;
static pipe_t g_pipes[PIPECOUNT];

void P_Reset (void)
{
    int i;
    
    g_bird.y = DESIGN_HEIGHT/2;
    g_bird.velocity = 0.0f;
    g_bird.alive = true;

    for (i = 0; i < PIPECOUNT; ++i)
    {
        g_pipes[i].x = 200 + i*120;
        g_pipes[i].y = (rand () % 100) + 40;
        g_pipes[i].gap = (rand () % 60) + 40;
    }
}

const bird_t *P_GetBird (void)
{
    return &g_bird;
}

static bool P_CheckCollisionRR (Rectangle r1, Rectangle r2)
{
    if (r1.x + r1.width >= r2.x
        && r1.x <= r2.x + r2.width
        && r1.y + r1.height >= r2.y
        && r1.y <= r2.y + r2.height)
        return true;
    return false;
}

static bool P_CheckCollision (void)
{
    int i;
    const bird_t *bird;
    const pipe_t *pipes, *pipe;
    Rectangle birdrect, upperpipe, lowerpipe;

    bird = P_GetBird ();
    pipes = P_GetPipes ();

    birdrect = (Rectangle){ DESIGN_WIDTH/4 + HITBOX_DX,
        bird->y + HITBOX_DY, 20 - 2*HITBOX_DX, 20 - 2*HITBOX_DY };
    
    for (i = 0; i < PIPECOUNT; ++i)
    {
        pipe = pipes+i;
        upperpipe = (Rectangle){ pipe->x, 0, PIPE_WIDTH, pipe->y - pipe->gap/2 };
        lowerpipe = (Rectangle){ pipe->x, pipe->y + pipe->gap/2,
            PIPE_WIDTH, DESIGN_HEIGHT - pipe->y - pipe->gap/2 };
        
        if (P_CheckCollisionRR(birdrect, upperpipe) ||
            P_CheckCollisionRR(birdrect, lowerpipe))
            return true;
    }
    
    return false;
}

void P_UpdateBird (float dt)
{
    if (!g_bird.alive)
    {
        G_RequestStateChange (GAME_OVER);
        return;
    }
    
    g_bird.y += g_bird.velocity*dt;
    g_bird.velocity += GRAVITY*dt;

    if (IsKeyPressed (KEY_SPACE))
        g_bird.velocity = -BIRD_JUMP_VELOCITY;

    if (g_bird.y + HITBOX_DY >= DESIGN_HEIGHT || g_bird.y + HITBOX_DY <= 0 || P_CheckCollision ())
        g_bird.alive = false;
}

void P_HandleGameOver (void)
{
    if (IsKeyPressed (KEY_R))
    {
        G_RequestStateChange (GAME_PLAYING);
        P_Reset();
    }
}

const pipe_t *P_GetPipes (void)
{
    return g_pipes;
}

/* @Fix pipe logic still looks like shit */
void P_UpdatePipes (float dt)
{
    int i;

    for (i = 0; i < PIPECOUNT; ++i)
    {
        g_pipes[i].x -= PIPESPEED*dt;

        if (g_pipes[i].x + PIPE_WIDTH < 0)
        {
            g_pipes[i].x = PIPECOUNT * 120.0f;
            g_pipes[i].y   = (rand() % 100) + 40;
            g_pipes[i].gap = (rand() % 60) + 40;
        }
     }
}
