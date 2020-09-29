#include "render.h"
#include <gba.h>
#include "../man/entity.h"

/* Funciones privadas */

/**
 * @precondition speed ha de tener un valor entre 1 y 4
 */
u16 _sys_render_getColourFromSpeed(u8 speed)
{
    switch (speed) {
        case 1:
            return RGB8(0x44, 0x44, 0x44);
        case 2:
            return RGB8(0x88, 0x88, 0x88);
        case 3:
            return RGB8(0xCC, 0xCC, 0xCC);
        case 4:
            return RGB8(0xFF, 0xFF, 0xFF);
        default:
            // No debería ocurrir, lo ponemos para evitar el warning del compilador
            return 0x0000;
    }
}

void _sys_render_updateSingleEntity(Entity_t* entity)
{
    // Borra la anterior (si existe)
    if (entity->prevPtr != 0) {
        *entity->prevPtr = 0;
    }

    // Dibuja la actual (si no está marcada para destruir)
    // Draw current (if it is not marked for destruction)
    if (!(entity->type & entityTypeDead)) {
        u16* pVideoMem = (u16*)MODE3_FB;
        pVideoMem = pVideoMem + (entity->y * SCREEN_WIDTH) + entity->x;
        u16 colour = _sys_render_getColourFromSpeed(entity->speed);

        // Escribe colour en la celda de memoria a la que apunta pVideoMem
        *pVideoMem = colour; 
        entity->prevPtr = pVideoMem;
    }
}

/* Funciones públicas */

void sys_render_init()
{
    irqInit();
    irqEnable(IRQ_VBLANK);
    REG_DISPCNT = MODE_3 | BG2_ENABLE;

    // @TODO borrar la pantalla
}

void sys_render_update()
{
    man_entity_forAll(_sys_render_updateSingleEntity);
}