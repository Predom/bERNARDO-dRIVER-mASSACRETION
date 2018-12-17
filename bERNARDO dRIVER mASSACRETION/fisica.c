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

    if(corpo->velocidadeModulo!=0)corpo->angulo=returnVetDirec(corpo->velocidade);

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
        float moduloAtrito=SQUAR(corpo->velocidadeModulo)*0.0003;
        struct Vetor2D atrito = produtoVetEscaLRet(retornarNormalizadoSPont(&corpo->velocidade), -moduloAtrito);
        somaVetoresRetOrig(&corpo->aceleracao,&atrito);
    }
}

void aplicarAtritoChao(struct CorpoFisico *corpo){
    if(corpo->velocidadeModulo>0.8){
        float atritoSupModulo=0.03;
        struct Vetor2D atritoSup;
        atritoSup=produtoVetEscaLRet(retornarNormalizadoSPont(&corpo->velocidade),atritoSupModulo);
        subtraiVetoresRetOrig(&corpo->velocidade,&atritoSup);
    }else if(corpo->velocidadeModulo<0.8){
        corpo->velocidade.x=0;
        corpo->velocidade.y=0;
        corpo->aceleracao.x=0;
        corpo->aceleracao.y=0;
    }
}

///Player func

void atualizarPlayer(struct Player *P){
    atualizaCorpoFisico(&P->corpo);
    aplicarAtritoAr(&P->corpo);
    aplicarAtritoChao(&P->corpo);
    produtoVetEscaL(&P->corpo.velocidade,&VELPLAYER,timeRate);


    P->local.x+=P->corpo.velocidade.x*timeRate;
    P->local.y+=P->corpo.velocidade.y*timeRate;


    //virar
    struct Vetor2D Giro = retornarNormalizadoSPont(&P->corpo.velocidade);
    produtoVetEscaLRetOrig(&Giro,0.02*P->corpo.velocidadeModulo*timeRate);
    subtraiVetoresRetOrig(&P->corpo.velocidade,&Giro);
    rotacionarVet2DRetOrig(&Giro,P->intencaoDeGiro);
    somaVetoresRetOrig(&P->corpo.velocidade,&Giro);

    if(P->intencaoDeGiro<0)P->intencaoDeGiro+=1.5;
    else if(P->intencaoDeGiro>0)P->intencaoDeGiro-=1.5;

    if(P->intencaoDeGiro>90)P->intencaoDeGiro=90;
    else if(P->intencaoDeGiro<-90)P->intencaoDeGiro=-90;


}

//void acelerar
void aceleraPlayer(struct Player *P){
    if(P->corpo.velocidadeModulo>0){
        struct Vetor2D aceleracau=retornarNormalizadoSPont(&P->corpo.velocidade);
        somaVetoresRetOrig(&P->corpo.aceleracao,&aceleracau);
    }else{
        P->corpo.velocidade.x+=cos(P->corpo.angulo);
        P->corpo.velocidade.y+=sin(P->corpo.angulo);
    }
}

void RePlayer(struct Player *P){
    if(P->corpo.velocidadeModulo>1.1){
        struct Vetor2D aceleracau=retornarNormalizadoSPont(&P->corpo.velocidade);
        subtraiVetoresRetOrig(&P->corpo.aceleracao,&aceleracau);
    }
}

void viraPraDireita(struct Player *P){
    P->intencaoDeGiro-=2;
}

void viraPraEsquerda(struct Player *P){
    P->intencaoDeGiro+=2;
}



///carros func

void atualizaCarro(struct Carro *c){
    atualizaCorpoFisico(&c->corpo);
    aplicarAtritoAr(&c->corpo);
    aplicarAtritoChao(&c->corpo);

    //soma a velocidade do player e do próprio carro à localização atual
    c->local.x+=c->corpo.velocidade.x*timeRate;
    c->local.y+=c->corpo.velocidade.y*timeRate;
}

void aceleraCarro(struct Carro *c){

}

void ReCarro(struct Carro *c){

}

void viraCarroParaADireita(struct Carro *c){

}

void viraCarroParaAEsquerda(struct Carro *c){

}
