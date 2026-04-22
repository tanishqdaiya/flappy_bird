#include <stdio.h>

#include "config.h"
#include "u_utils.h"
#include "r_render.h"
#include "p_play.h"

typedef struct viewport_s {
    float scale;
    int x, y, w, h;
} viewport_t;

static viewport_t r_viewport;
static Texture2D r_bgtexture, r_birdtexture, r_pipetexture;

static viewport_t R_MakeViewport (int screenwidth, int screenheight)
{
    viewport_t vp;
    float sx, sy;

    sx = (float)screenwidth / DESIGN_WIDTH;
    sy = (float)screenheight / DESIGN_HEIGHT;

    vp.scale = (sx < sy) ? sx : sy;

    vp.w = (int)(DESIGN_WIDTH * vp.scale);
    vp.h = (int)(DESIGN_HEIGHT * vp.scale);
    vp.x = (screenwidth - vp.w) / 2;
    vp.y = (screenheight - vp.h) / 2;

    return vp;
}

void R_UpdateCamera (Camera2D *camera)
{
    int screenwidth, screenheight;
    
    screenwidth = GetScreenWidth ();
    screenheight = GetScreenHeight ();

    r_viewport = R_MakeViewport (screenwidth, screenheight);

    camera->target = (Vector2){ 0, 0 };
    camera->offset = (Vector2){
        (float)r_viewport.x,
        (float)r_viewport.y
    };
    camera->zoom = r_viewport.scale;
    camera->rotation = 0.0f;
}

void R_Init (void)
{
    r_bgtexture = LoadTexture ("resources/Background/Background1.png");
    r_birdtexture = LoadTexture ("resources/Player/StyleBird1/Bird1-1.png");
    r_pipetexture = LoadTexture ("resources/Tiles/Style 1/PipeStyle1.png");
}

void R_Shutdown (void)
{
    UnloadTexture (r_bgtexture);
    UnloadTexture (r_birdtexture);
    UnloadTexture (r_pipetexture);
}

void R_DrawBackground (void)
{
    DrawTexturePro (r_bgtexture,
                    (Rectangle){ 0, 0, r_bgtexture.width, r_bgtexture.height },
                    (Rectangle){ 0, 0, DESIGN_WIDTH, DESIGN_HEIGHT },
                    (Vector2){ 0, 0 }, 0.0f, WHITE);
}

void R_DrawBird (void)
{
    const bird_t *bird;

    bird = P_GetBird ();
    DrawTexturePro (r_birdtexture,
                    (Rectangle){ 0, 0, 16, 16 },
                    (Rectangle){ (int)DESIGN_WIDTH/4, (int)bird->y, 20, 20 },
                    (Vector2){ 0, 0 }, 0.0f, WHITE);

#ifndef MODE_PROD
    DrawRectangleLines ((int)DESIGN_WIDTH/4 + HITBOX_DX, (int)bird->y + HITBOX_DY, 20 - 2*HITBOX_DX, 20 - 2*HITBOX_DY, GREEN);
#endif
}

static void R_DrawTextCentered (const char *text, float y, int fontsize, Color color)
{
    float x;
    Vector2 textsize;

    textsize = MeasureTextEx(GetFontDefault(), text, (float)fontsize, (float)fontsize/10);
    x = (DESIGN_WIDTH - textsize.x) / 2.0f;
    DrawText(text, (int)x, (int)y, fontsize, color);
}

void R_DrawGameOver (void)
{
    DrawRectangle (0, 0, DESIGN_WIDTH, DESIGN_HEIGHT, (Color){ 0, 0, 0, 180 });
    
    R_DrawTextCentered ("GAME OVER", (int)DESIGN_HEIGHT/4, 20, WHITE);
    R_DrawTextCentered ("Press 'r' to play again", (int)DESIGN_HEIGHT/4 + 20, 10, WHITE);
}

void R_DrawPaused (void)
{
    DrawText ("Paused", (int)DESIGN_WIDTH/6, (int)DESIGN_HEIGHT/4, 20, WHITE);
    DrawText ("Press 'esc' to resume", (int)DESIGN_WIDTH/6,
              (int)DESIGN_HEIGHT/4 + 20, 10, WHITE);
}

void R_DrawPipes (void)
{
    int i;
    float h;
    const pipe_t *pipes;

    pipes = P_GetPipes ();
    for (i = 0; i < PIPECOUNT; ++i) {
        h = pipes[i].y - pipes[i].gap/2;
        if (h <= 0) continue;
        
        DrawTexturePro (r_pipetexture,
                        (Rectangle){ 0, 0, PIPE_WIDTH, PIPE_HEIGHT },
                        (Rectangle){ pipes[i].x, 0, PIPE_WIDTH, h },
                        (Vector2){ 0, 0 },
                        0.0f, WHITE);

        DrawTexturePro (r_pipetexture,
                        (Rectangle){ 0, 0, PIPE_WIDTH, PIPE_HEIGHT },
                        (Rectangle){ pipes[i].x, pipes[i].y + pipes[i].gap/2,
                            PIPE_WIDTH, DESIGN_HEIGHT - pipes[i].y - pipes[i].gap/2 },
                        (Vector2){ 0, 0 },
                        0.0f, WHITE);
    }
}

void R_DrawHUD ()
{
    int score, high, yoffset;
    char scorebuf[16], highbuf[16];

    score = P_GetScore();
    high  = P_GetHighScore();
    yoffset  = 10;

    snprintf(scorebuf, sizeof(scorebuf), "SCORE: %d", score);
    snprintf(highbuf, sizeof(highbuf), "BEST: %d", high);

    DrawText(scorebuf, DESIGN_WIDTH - 60, yoffset, 10, RAYWHITE);
    DrawText(highbuf, DESIGN_WIDTH - 60, yoffset + 12, 10, GRAY);
}
