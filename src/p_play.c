#include <stdlib.h>

#include "raylib.h"

#include "config.h"
#include "p_play.h"
#include "g_game.h"
#include "i_interface.h"

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
    float gravity;
    float jump_velocity;
    
    if (!g_bird.alive)
    {
        G_RequestStateChange (GAME_OVER);
        return;
    }

    gravity = I_ConfigGetFloat("GRAVITY");
    jump_velocity = I_ConfigGetFloat("BIRD_JUMP_VELOCITY");
    
    g_bird.y += g_bird.velocity*dt;
    g_bird.velocity += gravity*dt;

    if (IsKeyPressed (KEY_SPACE))
        g_bird.velocity = -jump_velocity;

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

void P_HandlePaused (void)
{
    if (IsKeyPressed (KEY_ESCAPE))
        G_RequestStateChange (GAME_PLAYING);
}

const pipe_t *P_GetPipes (void)
{
    return g_pipes;
}

/* @Fix pipe logic still looks like shit */
void P_UpdatePipes (float dt)
{
    int i, j;
    float speed, spacing, max_x;

    speed = I_ConfigGetFloat("PIPESPEED");
    spacing = I_ConfigGetFloat("PIPESPACING");
    for (i = 0; i < PIPECOUNT; ++i)
    {
        g_pipes[i].x -= speed*dt;

        if (g_pipes[i].x + PIPE_WIDTH < 0)
        {
            max_x = 0;
            for (j = 0; j < PIPECOUNT; ++j)
            {
                if (g_pipes[j].x > max_x)
                    max_x = g_pipes[j].x;
            }
            
            g_pipes[i].x = max_x + spacing;
            
            g_pipes[i].y   = (rand() % 100) + 40;
            g_pipes[i].gap = (rand() % 60) + 40;
        }
     }
}
