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
struct Vetor2D retornaVelocidadeDoJogador();

 ///corpos fisicos de uma maneira geral
void atualizaCorpoFisico(struct CorpoFisico *corpo);

void aplicarForcaPont(struct CorpoFisico *corpo, struct Vetor2D *forca);

void aplicarForca(struct CorpoFisico *corpo, struct Vetor2D forca);

void aplicarAtritoAr(struct CorpoFisico *corpo);

void aplicarAtritoChao(struct CorpoFisico *corpo);

///Player func

void atualizarPlayer(struct Player *P);

//controles
void aceleraPlayer(struct Player *P);

void RePlayer(struct Player *P);

void viraPraDireita(struct Player *P);

void viraPraEsquerda(struct Player *P);

///carros func
void atualizaCarro(struct Carro *c);

void aceleraCarro(struct Carro *c);

void ReCarro(struct Carro *c);

void viraCarroParaADireita(struct Carro *c);

void viraCarroParaAEsquerda(struct Carro *c);






#endif
