#pragma once
#include <gba.h>

/* Estructuras de datos */

typedef struct typeOrientation {
    s8 x;
    s8 y;
} Orientation_t;

/* Interfaz pública */

void sys_starfield_init();
void sys_starfield_update();
Orientation_t *sys_starfield_getOrientation();
