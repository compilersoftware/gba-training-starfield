# Starfield - devkitPro - Game Boy Advance

Este programa de ejemplo está basado en esta serie de vídeos de [Fran Gallego](https://twitter.com/frangallegobr), también conocido como [Profesor Retroman](https://www.youtube.com/channel/UCSdIAKvPxlB3VlFDCBvI46A) en Youtube:

* [GameEngine ECS: Starfield Effect - part 1](https://www.youtube.com/watch?v=ighkMUM9-Ww).
* [GameEngine ECS: Starfield Effect - part 2](https://www.youtube.com/watch?v=MgmCjcVOc44).

El código se ha heredado casi íntegramente de la [versión original de tutorial para Amstrad CPC](https://github.com/compilersoftware/cpc-training-starfield). Solamente se han adaptado las partes específicas relativas a las diferencias en el hardware del Amstrad CPC y de la Game Boy Advance, así como de los respectivas librerías de apoyo empleadas.

Este proyecto se ha desarrollado en macOS, pero se supone que en Linux o Windows funcionará de forma similar.

Para construir el proyecto desde cero, teniendo instalado [devkitPro con libgba](https://devkitpro.org/wiki/Getting_Started) correctamente, tecleamos `make clean && make`.

## Consideraciones acerca del código

A continuación se citan las más relevantes (bajo nuestro criterio) de lo explicado en los vídeos, más lo que se ha intentado aportar por mi parte.

* El ejemplo es un tutorial de introducción a la [arquitectura ECS](https://en.wikipedia.org/wiki/Entity_component_system) (Entidad - Componente - Sistema). En realidad no necesitaríamos montar esta arquitectura para un caso de uso tan sencillo, pero precisamente la sencillez es la que permite centrarnos en aprender los conceptos que nos serán útiles en otros desarrollos más complejos.

* El ejemplo usa devkitPro con libgba, que genera "cartuchos" (ficheros `.gba`) para Game Boy Advance. El compilador y el hardware de destino condicionan notablemente el tipo de código que vamos a escribir. Por ejemplo, daremos por hecho que las llamadas a las funciones cumplen las precondiciones, las ejecución de las mismas cumple las postcondiciones y no haremos control de errores de ningún tipo. En caso contrario, simplemente se producirá un comportamiento inesperado.

* Sabiendo que la plataforma objeto es Game Boy Advance, y que vamos a usar el Modo 3 para pintar los gráficos, daremos bastantes cosas por supuestas (por ejemplo, las dimensiones de la pantalla). No queremos hacer un motor gráfico multiplataforma y multi modo de vídeo.

* Es importante estar atentos a la manera que tiene el compilador de generar el código ensamblador. Por ejemplo, en este caso vermos que hemos usado funciones de inicialización en vez de inicializar las variables globales en la declaración.

* Siendo C el lenguaje fuente, se utiliza una nomenclatura para nombrar variables y funciones que quiere asemejarse a cómo lo haríamos en lenguajes orientados a objetos, como C++. Si bien no tenemos disponible toda la potencia de la orientación a objetos, sí que nos ayuda a estructurar mejor nuestro código. Y portarlo a C++ no debería ser complicado. 

* La depuración es una tarea muy ardua en principio, hasta que cogemos práctica. Si bien el código está escrito en C, el depurador que nos ofrece el emulador mGBA (o cualquier otro que usemos) nos mostrará las instrucciones en lenguaje ensamblador. Tendremos que inspeccionar la memoria para determinar si el código se comporta como debería o hay errores.

* Tanto la documentación como los comentarios de código están escritos en español. En principio el objetivo es dirigirnos a un público hispanoparlante, ya que en inglés suele haber mucha más documentación en general.

## Adaptaciones respecto del tutorial para Amstrad CPC

* En esta ocasión no hemos puesto el foco en el código ensamblador que genera el compilador. Realmente, haciendo las adaptaciones obligatorias dadas las diferencias en el hardware y las librerías empledas, el ejemplo ha funcionado a la primera.

* Para pintar las estrellas hemos usado el Modo 3 de vídeo, que ofrece una resolución de 240x160 píxeles, con colores de 15 bits por píxel. Los píxeles tienen una relación de aspecto 1:1, y la velocidad de refresco, si nuestro código no es demasiado lento, debería ser de 60 fps.

* Para iluminar un píxel de la pantalla con un color basta con poner en la posición de memoria de vídeo correspondiente al píxel (que además tiene una distribución lineal) el valor de 15 bits correspondiente al RGB del color (con 5 bits para cada componente básico de color).

* Usamos las funciones de la librería estandar de C para copiar zonas de memoria (`memcpy()`), rellenar zonas de memoria con un valor (`memset()`) y generar números aleatorios (`srand()` y `rand()`).

* Por último, creo que hay maneras de hacer que el emulador mGBA funcione conectado al depurador y Visual Studio Code de tal forma que podemos poner puntos de ruptura e inspeccionar las variables sobre el propio código fuente en C.

## Versiones

* 0.9. Se corresponde con la versión 1.3 del tutorial para Amstrad CPC:
  * Se usan diferentes colores según la velocidad de la estrella (más oscuro, más lenta).
  * El movimiento del campo de estrellas cambia aleatoriamente de dirección cada 2 segundos.

## Limitaciones conocidas (posibles mejoras)

* No se tienen en cuenta las reglas de la perspectiva. Las estrellas se pintan en el orden que se crean. Por tanto, puede darse el caso de que una estrella más lenta (que, en teoría, está por detrás) se pinte por encima de una estrella más rápida (que debería estar por delante).
