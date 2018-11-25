#ifndef ENTIDADES_H
#define ENTIDADES_H
/**************************************************
 *  Esta header deve conter todas as declarações  *
 * de structs que serão usados na main.c.         *
 *  Estes structs são os objetos do nosso código. *
 * Os "métodos" desses structs estarão descritos  *
 * em fisica.c e desenho.c.                       *
 **************************************************/

#define x coord<:0:>
#define y coord<:1:>

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
#endif

