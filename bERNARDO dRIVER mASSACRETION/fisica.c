#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "fisica.h"
#include "matematica.h"
#include "entidades.h"

/********************************************************
 *      Este arquivo deve conter as rotinas para        *
 *    atualizar as informações dentro dos structs       *
 *    que são entidades fisicas no jogo. Aqui deve      *
 *    conter o código que descreve o comportamento      *
 *   das entidades ao longo do tempo e as interações    *
 *             delas umas com as outras.                *
 *     Aqui não devem estar contidos códigos que        *
 * descrevam IA ou algo do tipo, apenas o comportamento *
 * físico (sem "tomada de decisões").                   *
 ********************************************************/

 ///globais

 float timeRate=1;

 ///corpos fisicos de uma maneira geral
void atualizaCorpoFisico(struct CorpoFisico *corpo){



}

 ///Player func

void atualizarPlayer(struct Player *P){


}

//void acelerar
void aceleraPlayer(struct Player *P){

}

void RePlayer(struct Player *P){

}

void viraPraDireita(struct Player *P){

}

void viraPraEsquerda(struct Player *P){

}

void mudaOtimeRate(float novoTimeRate){
    timeRate=novoTimeRate;
}

///carros func

void atualizaCarro(struct Carro *c, struct Player *P){
}
