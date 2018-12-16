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
 struct Vetor2D VELPLAYER={0,0};

 void mudaOtimeRate(float novoTimeRate){
    timeRate=novoTimeRate;
}

float retornaOtimeRate(){
    return timeRate;
}

struct Vetor2D retornaVelocidadeDoJogador(){
    return VELPLAYER;
}


 ///corpos fisicos de uma maneira geral

void atualizaCorpoFisico(struct CorpoFisico *corpo){

    //guarda o módulo da aceleração
    corpo->aceleracaoModulo=returnComp(&corpo->aceleracao);

    //atualiza velocidade e zera aceleração
    produtoVetEscaLRetOrig(&corpo->aceleracao,timeRate);
    somaVetoresRetOrig(&corpo->velocidade,&corpo->aceleracao);
    produtoVetEscaLRetOrig(&corpo->aceleracao,0);

    //guarda o módulo da velocidade
    corpo->velocidadeModulo=returnComp(&corpo->velocidade);

    if(corpo->velocidadeModulo!=0)
        corpo->angulo=returnVetDirec(corpo->velocidade);

}

void aplicarForcaPont(struct CorpoFisico *corpo, struct Vetor2D *forca){
    struct Vetor2D deltaAcel;
    deltaAcel.x=forca->x/corpo->massa;
    deltaAcel.y=forca->y/corpo->massa;
    somaVetoresRetOrig(&corpo->aceleracao,&deltaAcel);
}

void aplicarForca(struct CorpoFisico *corpo, struct Vetor2D forca){
    forca.x/=corpo->massa;
    forca.y/=corpo->massa;
    somaVetoresRetOrig(&corpo->aceleracao,&forca);
}

void aplicarAtritoAr(struct CorpoFisico *corpo){
    if(corpo->velocidadeModulo!=0){
        float moduloAtrito=corpo->velocidadeModulo*0.003;
        struct Vetor2D atrito = produtoVetEscaLRet(retornarNormalizadoSPont(&corpo->velocidade), -moduloAtrito);
        somaVetoresRetOrig(&corpo->aceleracao,&atrito);
    }
}

void aplicarAtritoChao(struct CorpoFisico *corpo){
    if(corpo->velocidadeModulo>0.08){
        float atritoSupModulo=0.003;
        struct Vetor2D atritoSup;
        atritoSup=produtoVetEscaLRet(retornarNormalizadoSPont(&corpo->velocidade),atritoSupModulo);
        subtraiVetoresRetOrig(&corpo->velocidade,&atritoSup);
    }else if(corpo->velocidadeModulo<0.08){
        corpo->velocidade.x=0;
        corpo->velocidade.y=0;
    }
}

///Player func

void atualizarPlayer(struct Player *P){
    aplicarAtritoAr(&P->corpo);
    aplicarAtritoChao(&P->corpo);
    atualizaCorpoFisico(&P->corpo);
    produtoVetEscaL(&P->corpo.velocidade,&VELPLAYER,timeRate);


    VELPLAYER.x=P->corpo.velocidade.x*timeRate;
    VELPLAYER.y=P->corpo.velocidade.y*timeRate;


}

//void acelerar
void aceleraPlayer(struct Player *P){
    if(P->corpo.velocidadeModulo>0){
        struct Vetor2D aceleracau=retornarNormalizadoSPont(&P->corpo.velocidade);
        somaVetoresRetOrig(&P->corpo.aceleracao,&aceleracau);
    }else if(P->corpo.velocidadeModulo<0){
        struct Vetor2D aceleracau=retornarNormalizadoSPont(&P->corpo.velocidade);
        somaVetoresRetOrig(&P->corpo.aceleracao,&aceleracau);
    }else{
        P->corpo.velocidade.x+=cos(P->corpo.angulo);
        P->corpo.velocidade.y+=sin(P->corpo.angulo);
    }
}

void RePlayer(struct Player *P){

}

void viraPraDireita(struct Player *P){

}

void viraPraEsquerda(struct Player *P){

}



///carros func
/*
void atualizaCarro(struct Carro *c, struct Player *P){
}*/
