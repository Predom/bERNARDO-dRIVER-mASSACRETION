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




 ///Player func

void atualizarPlayer(struct Player *P){
    if(P->velocidade.x!=0||P->velocidade.y!=0)
    P->angulo=returnVetDirec(P->velocidade);

    P->velocidadeModulo=returnComp(&P->velocidade);

    //atrito com o ar
        if(P->velocidadeModulo>0){
        float atritoModulo=SQUAR(P->velocidadeModulo)*0.0003;
        struct Vetor2D atrito;
        atrito=produtoVetEscaLRet(retornarNormalizadoSPont(&P->velocidade),atritoModulo);
        subtraiVetoresRetOrig(&P->velocidade,&atrito);
    }
    //atrito com o eixo
    if(P->velocidadeModulo>0.08){
        float atritoSupModulo=0.008;
        struct Vetor2D atritoSup;
        atritoSup=produtoVetEscaLRet(retornarNormalizadoSPont(&P->velocidade),atritoSupModulo);
        subtraiVetoresRetOrig(&P->velocidade,&atritoSup);
    }else if(P->velocidadeModulo<0.08){
        P->velocidade.x=0;
        P->velocidade.y=0;
    }

}

//void acelerar
void aceleraPlayer(struct Player *P){
    float acelrat = 1;
    if(P->velocidadeModulo>0){
        struct Vetor2D aceleracau=retornarNormalizadoSPont(&P->velocidade);
        produtoVetEscaLRetOrig(&aceleracau,acelrat);
        somaVetoresRetOrig(&P->velocidade,&aceleracau);
    }else if(P->velocidadeModulo<0){
        struct Vetor2D aceleracau=retornarNormalizadoSPont(&P->velocidade);
        produtoVetEscaLRetOrig(&aceleracau,acelrat);
        somaVetoresRetOrig(&P->velocidade,&aceleracau);
    }else{
        P->velocidade.x+=cos(P->angulo)*acelrat;
        P->velocidade.y+=sin(P->angulo)*acelrat;
    }

}

void RePlayer(struct Player *P){
    float acelrat = 0.25;
    if(P->velocidadeModulo>0){
        struct Vetor2D aceleracau=retornarNormalizadoSPont(&P->velocidade);
        produtoVetEscaLRetOrig(&aceleracau,acelrat);
        subtraiVetoresRetOrig(&P->velocidade,&aceleracau);
    }else if(P->velocidadeModulo<0){
        struct Vetor2D aceleracau=retornarNormalizadoSPont(&P->velocidade);
        produtoVetEscaLRetOrig(&aceleracau,acelrat);
        subtraiVetoresRetOrig(&P->velocidade,&aceleracau);
    }else{
        P->velocidade.x-=cos(P->angulo)*acelrat;
        P->velocidade.y-=sin(P->angulo)*acelrat;
    }

}

void viraPraDireita(struct Player *P){
    struct Vetor2D Giro = retornarNormalizadoSPont(&P->velocidade);
    produtoVetEscaLRetOrig(&Giro,0.005*P->velocidadeModulo);
    subtraiVetoresRetOrig(&P->velocidade,&Giro);
    rotacionarVet2DRetOrig(&Giro,90);
    somaVetoresRetOrig(&P->velocidade,&Giro);

}

void viraPraEsquerda(struct Player *P){
    struct Vetor2D Giro = retornarNormalizadoSPont(&P->velocidade);
    produtoVetEscaLRetOrig(&Giro,0.005*P->velocidadeModulo);
    subtraiVetoresRetOrig(&P->velocidade,&Giro);
    rotacionarVet2DRetOrig(&Giro,-90);
    somaVetoresRetOrig(&P->velocidade,&Giro);
}

///carros func

void atualizaCarro(struct Carro *c, struct Player *P){
}
