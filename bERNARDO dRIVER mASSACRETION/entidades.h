#ifndef ENTIDADES_H
#define ENTIDADES_H
/**************************************************
 *  Esta header deve conter todas as declara��es  *
 * de structs que ser�o usados na main.c.         *
 *  Estes structs s�o os objetos do nosso c�digo. *
 * Os "m�todos" desses structs estar�o descritos  *
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
    struct Ponto2D* v; // Aray de v�rtices
    int NumVertices;
};

struct CorpoFisico
{
    struct CONVEXPOLYGON *modelo;    /// endere�o do modelo

    struct CONVEXPOLYGON locAtual;   /// para ser usado nas fun��es de desenho e detec��o de colis�o
                                     /// � obtido transformando o modelo pelo �ngulo atual
    float angulo;                    /// em rela��o ao eixo x
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

    int marcha;                      /// marcha do carro para as fun��es de �udio
    int giro;                        /// velocidade de giro do motor para alterar a velociadade do �udio
    int volume;                      /// volume do som do motor para as fun��es de �udio

    ALLEGRO_BITMAP *sprite_player;
};

struct Carro
{

    int ID;
    struct CorpoFisico corpo;

    float intencaoDeGiro;

    int marcha;                      /// marcha do carro para as fun��es de �udio
    int giro;                        /// velocidade de giro do motor para alterar a velociadade do �udio
    int volume;                      /// volume do som do motor para as fun��es de �udio

    ALLEGRO_BITMAP *sprite_carro;

    struct Ponto2D local;

    float dano;
};

struct Policia
{
    struct Carro carro;
};

#endif

