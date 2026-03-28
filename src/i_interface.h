#pragma once
#include "m_memory.h"

void I_ConfigInit(arena_t *a);
void I_ConfigLoad(const char *filename);

const char *I_ConfigGetStr(const char *key);
int I_ConfigGetInt(const char *key);
float I_ConfigGetFloat(const char *key);
