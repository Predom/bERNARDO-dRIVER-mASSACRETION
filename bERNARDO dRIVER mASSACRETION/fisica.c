#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "fisica.h"
#include "matematica.h"
#include "entidades.h"

/********************************************************
 *      Este arquivo deve conter as rotinas para        *
 *    atualizar as informa��es dentro dos structs       *
 *    que s�o entidades fisicas no jogo. Aqui deve      *
 *    conter o c�digo que descreve o comportamento      *
 *   das entidades ao longo do tempo e as intera��es    *
 *             delas umas com as outras.                *
 *     Aqui n�o devem estar contidos c�digos que        *
 * descrevam IA ou algo do tipo, apenas o comportamento *
 * f�sico (sem "tomada de decis�es").                   *
 ********************************************************/

 ///globais

float timeRate=1;
float REFERENCIA_X;

 void mudaOtimeRate(float novoTimeRate){
    timeRate=novoTimeRate;
}

float retornaOtimeRate(){
    return timeRate;
}

float retornaREFERENCIA_X(){
    return REFERENCIA_X;
}


 ///corpos fisicos de uma maneira geral

void atualizaCorpoFisico(struct CorpoFisico *corpo){

    //guarda o m�dulo da acelera��o
    corpo->aceleracaoModulo=returnComp(&corpo->aceleracao);

    //atualiza velocidade e zera acelera��o
    produtoVetEscaLRetOrig(&corpo->aceleracao,timeRate);
    somaVetoresRetOrig(&corpo->velocidade,&corpo->aceleracao);
    produtoVetEscaLRetOrig(&corpo->aceleracao,0);

    //guarda o m�dulo da velocidade
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

    REFERENCIA_X=-P->corpo.velocidade.x*timeRate;

    if(P->local.y+P->corpo.velocidade.y*timeRate>HEIGHT/2-600)
    {
        P->local.y=HEIGHT/2-600;
        P->corpo.velocidade.y=0;
    }
    else if(P->local.y+P->corpo.velocidade.y*timeRate<HEIGHT/2-1000)
    {
        P->local.y=HEIGHT/2-1000;
        P->corpo.velocidade.y=0;
    }
    else
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

    //soma a velocidade do player e do pr�prio carro � localiza��o atual
    c->local.x+=(c->corpo.velocidade.x*timeRate+REFERENCIA_X);
    c->local.y+=c->corpo.velocidade.y*timeRate;

    //virar
    struct Vetor2D Giro = retornarNormalizadoSPont(&c->corpo.velocidade);
    produtoVetEscaLRetOrig(&Giro,0.02*c->corpo.velocidadeModulo*timeRate);
    subtraiVetoresRetOrig(&c->corpo.velocidade,&Giro);
    rotacionarVet2DRetOrig(&Giro,c->intencaoDeGiro);
    somaVetoresRetOrig(&c->corpo.velocidade,&Giro);

    if(c->intencaoDeGiro<0)c->intencaoDeGiro+=1.5;
    else if(c->intencaoDeGiro>0)c->intencaoDeGiro-=1.5;

    if(c->intencaoDeGiro>90)c->intencaoDeGiro=90;
    else if(c->intencaoDeGiro<-90)c->intencaoDeGiro=-90;
}

void aceleraCarro(struct Carro *c, float velProporcao){
    if(c->corpo.velocidadeModulo>0){
        struct Vetor2D aceleracau=retornarNormalizadoSPont(&c->corpo.velocidade);
        produtoVetEscaLRetOrig(&aceleracau,velProporcao);
        somaVetoresRetOrig(&c->corpo.aceleracao,&aceleracau);
    }else{
        c->corpo.velocidade.x+=cos(c->corpo.angulo);
        c->corpo.velocidade.y+=sin(c->corpo.angulo);
    }
}

void ReCarro(struct Carro *c){

}

void viraCarroParaADireita(struct Carro *c){
    c->intencaoDeGiro-=2;
}

void viraCarroParaAEsquerda(struct Carro *c){
    c->intencaoDeGiro-=2;
}
