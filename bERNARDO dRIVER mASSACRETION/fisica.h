#ifndef FISICA_H
#define FISICA_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "matematica.h"
#include "entidades.h"

/**************************************
 * Essa é a header da fisica.c        *
 **************************************/

struct Carro
{
    int ID;
    struct Ponto2D v[5];              /// Vertieces do poligono
    struct Ponto2D centro;
    float angulo;                    /// em relação ao eixo x


};





#endif
