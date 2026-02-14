#pragma once
#include <stdbool.h>

typedef struct bird_s {
    float y;
    float velocity;
    bool alive;
} bird_t;

typedef struct pipe_s {
    float x, y;
    int gap;
} pipe_t;

void P_Reset (void);
const bird_t *P_GetBird (void);
void P_UpdateBird (float dt);
void P_HandleGameOver (void);
const pipe_t *P_GetPipes (void);
void P_UpdatePipes (float dt);
