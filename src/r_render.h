#pragma once

#include "raylib.h"

void R_Init (void);
void R_Shutdown (void);
void R_UpdateCamera (Camera2D *camera);
void R_DrawBackground (void);
void R_DrawBird (void);
void R_DrawGameOver (void);
void R_DrawPipes (void);
