#ifndef ENTIDADES_H
#define ENTIDADES_H
/**************************************************
 *  Esta header deve conter todas as declarações  *
 * de structs que serão usados na main.c.         *
 *  Estes structs são os objetos do nosso código. *
 * Os "métodos" desses structs estarão descritos  *
 * em fisica.c e desenho.c.                       *
 **************************************************/

struct Ponto2D
{
    float x;
    float y;
};
struct Vetor2D
{
    float x;
    float y;
};
struct CONVEXPOLYGON
{
    struct Ponto2D* v; // Aray de vértices
    int NumVertices;
};
#endif
