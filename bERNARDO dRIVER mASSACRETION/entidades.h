#ifndef ENTIDADES_H
#define ENTIDADES_H
/**************************************************
 *  Esta header deve conter todas as declara��es  *
 * de structs que ser�o usados na main.c.         *
 *  Estes structs s�o os objetos do nosso c�digo. *
 * Os "m�todos" desses structs estar�o descritos  *
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
    struct Ponto2D* v; // Aray de v�rtices
    int NumVertices;
};
#endif
