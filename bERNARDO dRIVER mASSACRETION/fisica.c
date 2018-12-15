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
 struct Vetor2D VELPLAYER={0,0};;

 void mudaOtimeRate(float novoTimeRate){
    timeRate=novoTimeRate;
}

float retornaOtimeRate(){
    return timeRate;
}

 ///corpos fisicos de uma maneira geral

void atualizaCorpoFisico(struct CorpoFisico *corpo){

    corpo->aceleracaoModulo=returnComp(&corpo->aceleracao);

    //provisório
    if(corpo->velocidade.x!=0||corpo->velocidade.y!=0)
    corpo->angulo=returnVetDirec(corpo->velocidade);




    //vel = vel + acel
    somaVetoresRetOrig(&corpo->velocidade,&corpo->aceleracao);
    produtoVetEscaLRetOrig(&corpo->aceleracao,0);
/*
    //provisório
    //atrito com o ar
        if(corpo->velocidadeModulo>0){
        float atritoModulo=SQUAR(corpo->velocidadeModulo)*0.0003*timeRate;
        struct Vetor2D atrito;
        atrito=produtoVetEscaLRet(retornarNormalizadoSPont(&corpo->velocidade),atritoModulo);
        subtraiVetoresRetOrig(&corpo->velocidade,&atrito);
    }

    //atrito com o eixo
    if(corpo->velocidadeModulo>0.08){
        float atritoSupModulo=0.008*timeRate;
        struct Vetor2D atritoSup;
        atritoSup=produtoVetEscaLRet(retornarNormalizadoSPont(&corpo->velocidade),atritoSupModulo);
        subtraiVetoresRetOrig(&corpo->velocidade,&atritoSup);
    }else if(corpo->velocidadeModulo<0.08){
        corpo->velocidade.x=0;
        corpo->velocidade.y=0;
    }
    */

}

 ///Player func

void atualizarPlayer(struct Player *P){
    atualizaCorpoFisico(&P->corpo);

}

//void acelerar
void aceleraPlayer(struct Player *P){

    float acelrat = timeRate;
    if(P->corpo.velocidadeModulo>0){

        P->corpo.aceleracao=retornarNormalizadoSPont(&P->corpo.velocidade);
        produtoVetEscaLRetOrig(&P->corpo.aceleracao,acelrat);

    }else if(P->corpo.velocidadeModulo<0){
        P->corpo.aceleracao=retornarNormalizadoSPont(&P->corpo.velocidade);
        produtoVetEscaLRetOrig(&P->corpo.aceleracao,acelrat);
        somaVetoresRetOrig(&P->corpo.velocidade,&P->corpo.aceleracao);
    }else{
        P->corpo.velocidade.x+=cos(P->corpo.angulo)*acelrat;
        P->corpo.velocidade.y+=sin(P->corpo.angulo)*acelrat;
    }
}

void RePlayer(struct Player *P){

}

void viraPraDireita(struct Player *P){

}

void viraPraEsquerda(struct Player *P){

}



///carros func

void atualizaCarro(struct Carro *c, struct Player *P){
}
