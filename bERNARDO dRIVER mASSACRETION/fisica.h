#ifndef FISICA_H
#define FISICA_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "matematica.h"
#include "entidades.h"

/**************************************
 * Essa é a header da fisica.c        *
 **************************************/


 struct Player
{

    struct CONVEXPOLYGON &modelo;    /// endereço do modelo

    struct CONVEXPOLYGON locAtual;   /// para ser usado nas funções de desenho e detecção de colisão
                                     /// é obtido transformando o modelo pelo ângulo atual
    float angulo;                    /// em relação ao eixo x


};

struct Carro
{
    int ID;
    struct CONVEXPOLYGON &modelo;    /// endereço do modelo

    struct CONVEXPOLYGON locAtual;   /// para ser usado nas funções de desenho e detecção de colisão
                                     /// é obtido transformando o modelo pelo ângulo atual+ânugo do player e
                                     /// somando o vetor local.

    struct Vetor2D local;            ///localização em relação ao player
    float angulo;                    /// em relação ao eixo x

    float dano;
};





#endif
