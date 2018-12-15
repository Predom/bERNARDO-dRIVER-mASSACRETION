#ifndef FISICA_H
#define FISICA_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "matematica.h"
#include "entidades.h"

/**************************************
 * Essa é a header da fisica.c        *
 **************************************/

 ///pra mexer nas globais a partir da main.c
void mudaOtimeRate(float novoTimeRate);
float retornaOtimeRate();

 ///corpos fisicos de uma maneira geral
void atualizaCorpoFisico(struct CorpoFisico *corpo);

///Player func

void atualizarPlayer(struct Player *P);

void aceleraPlayer(struct Player *P);

void RePlayer(struct Player *P);

void viraPraDireita(struct Player *P);

void viraPraEsquerda(struct Player *P);

///carros func

void atualizaCarro(struct Carro *c, struct Player *P);






#endif
