#include "raylib.h"

#define SPRITE_W 16
#define SPRITE_H 16

Rectangle U_SpriteRect(int row, int col)
{
    return (Rectangle){
        col * SPRITE_W,
        row * SPRITE_H,
        SPRITE_W,
        SPRITE_H
    };
}
