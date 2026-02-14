#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "r_render.h"
#include "g_game.h"
#include "p_play.h"

int main (int argc, char **argv)
{
    Camera2D camera;
    float dt;

    srand(time(NULL));
    
    InitWindow (800, 450, "Flappy Bird");
    SetWindowState (FLAG_WINDOW_RESIZABLE);

    R_Init();
    P_Reset();
    
    SetTargetFPS (60);
    while (!WindowShouldClose ())
    {
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
