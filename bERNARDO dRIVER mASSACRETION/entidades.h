#ifndef ENTIDADES_H
#define ENTIDADES_H
/**************************************************
 *  Esta header deve conter todas as declarações  *
 * de structs que serão usados na main.c.         *
 *  Estes structs são os objetos do nosso código. *
 * Os "métodos" desses structs estarão descritos  *
 * em fisica.c e desenho.c.                       *
 **************************************************/
#include <allegro5/allegro.h>
#define x coord<:0:>
#define y coord<:1:>
#define WIDTH 1300
#define HEIGHT 800
#define windowX 100
#define windowY 0

struct Ponto2D
{
    float coord[2];
};

struct Vetor2D
{
    float coord[2];
};

struct Matriz2x2{

    float elementos[2][2];
};

struct CONVEXPOLYGON
{
    struct Ponto2D* v; // Aray de vértices
    int NumVertices;
};

struct CorpoFisico
{
    struct CONVEXPOLYGON *modelo;    /// endereço do modelo

    struct CONVEXPOLYGON locAtual;   /// para ser usado nas funções de desenho e detecção de colisão
                                     /// é obtido transformando o modelo pelo ângulo atual
    float angulo;                    /// em relação ao eixo x
    float movimentoAngular;          ///rate de modif do angulo
    float aceleracaoAngular;         ///rate de modif da vel angular

    struct Vetor2D forcas;
    float forcasModulo;

    struct Vetor2D velocidade;
    float velocidadeModulo;

    struct Vetor2D aceleracao;
    float aceleracaoModulo;

    float massa;
};

 struct Player
{
    struct CorpoFisico corpo;

    struct Ponto2D local;

    float intencaoDeGiro;

    int marcha;                      /// marcha do carro para as funções de áudio
    int giro;                        /// velocidade de giro do motor para alterar a velociadade do áudio
    int volume;                      /// volume do som do motor para as funções de áudio

    ALLEGRO_BITMAP *sprite_player;
};

struct Carro
{

    int ID;
    struct CorpoFisico corpo;

    float intencaoDeGiro;

    int marcha;                      /// marcha do carro para as funções de áudio
    int giro;                        /// velocidade de giro do motor para alterar a velociadade do áudio
    int volume;                      /// volume do som do motor para as funções de áudio

    ALLEGRO_BITMAP *sprite_carro;

    struct Ponto2D local;

    float dano;
};

struct Policia
{
    struct Carro carro;
};

#endif

