#include <gba.h>
#include "man/entity.h"
#include "sys/generator.h"
#include "sys/physics.h"
#include "sys/render.h"
#include "sys/starfield.h"
#include <stdlib.h>
#include <time.h>

int main(void)
{
    // Inicializar la semilla de números aleatorios
    srand(time(NULL));

    // Inicializar sistemas
    sys_render_init();
    sys_starfield_init();

    // Inicializar manager
    man_entity_init();
 
    while(1) {

        // Actualizar sistemas
        sys_physics_update();
        sys_generator_update();
        sys_render_update();
        sys_starfield_update();

        // Actualizar manager
        man_entity_update();

        VBlankIntrWait();
    }
}
