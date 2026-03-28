#include <errno.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "r_render.h"
#include "g_game.h"
#include "p_play.h"
#include "m_memory.h"
#include "i_interface.h"

int main (int argc, char **argv)
{
    Camera2D camera;
    float dt;
    arena_t configarena;

    configarena.size = 1024 * 4; /* 4 kilobytes */
    configarena.offset = 0;
    configarena.data = malloc(configarena.size);
    if (!configarena.data) {
        perror("out of memory!");
        exit(EXIT_FAILURE);
    }

    I_ConfigInit(&configarena);
    I_ConfigLoad("gamein.txt");
    
    srand(time(NULL));
    InitWindow (800, 450, "Flappy Bird");
    SetWindowState (FLAG_WINDOW_RESIZABLE);

    R_Init();
    P_Reset();
    
    SetTargetFPS (60);
    while (!WindowShouldClose ())
    {
        I_ConfigPoll("gamein.txt");
        
        dt = GetFrameTime();

        G_Update(dt);
        R_UpdateCamera (&camera);

        BeginDrawing ();
        ClearBackground (BLANK);
        BeginMode2D (camera);
        G_Draw();
        EndMode2D ();

        EndDrawing ();
    }

    R_Shutdown();
    return 0;
}
