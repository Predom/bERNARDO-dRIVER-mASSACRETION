#ifndef MATEMATICA_H
#define MATEMATICA_H
#include <math.h>
#include "entidades.h"

/**************************************
 * Essa é a header da matematica.c
 **************************************/

float pitagoras(float x1,float y1,float x2,float y2);

float pitagorasSenCos(float x1,float y1,float x2,float y2,float *seno,float *cosseno);

float distanciaEntrePontos(struct verticeFisico *p1, struct verticeFisico *p2);

// Operação com Polígonos
int CheckPenetration(struct CONVEXPOLYGON *cpA, struct CONVEXPOLYGON *cpB);

int TestCheckPenetration();

// Operação com vetores:
void Sub(struct Ponto2D *a, struct Ponto2D *b, struct Vetor2D *z);

float DotProduct(struct Vetor2D *z, struct Vetor2D *e);
#endif

