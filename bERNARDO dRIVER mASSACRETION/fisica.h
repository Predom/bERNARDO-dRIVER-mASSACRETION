#ifndef FISICA_H
#define FISICA_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "matematica.h"
#include "entidades.h"

/**************************************
 * Essa é a header da fisica.c        *
 **************************************/


///Player func

void atualizarPlayer(struct Player *P);

///carros func

void atualizaCarro(struct Carro *c);






#endif
