#ifndef MATEMATICA_H
#define MATEMATICA_H
#include <math.h>
#include "entidades.h"

/**************************************
 * Essa é a header da matematica.c
 **************************************/






// Operação com Polígonos
int CheckPenetration(struct CONVEXPOLYGON *cpA, struct CONVEXPOLYGON *cpB);

int TestCheckPenetration();

// Operação com vetores:
void Sub(struct Ponto2D *a, struct Ponto2D *b, struct Vetor2D *z);


//transformar e girar vetores
void transVet2DRetOrig(struct Vetor2D *vetor, struct Matriz2x2 *matriz);

void transVet2D(struct Vetor2D *vetorEntrada, struct Vetor2D *vetorSaida, struct Matriz2x2 *matriz);

void rotacionarVet2DRetOrig(struct Vetor2D *vetor, float graus);

void rotacionarVet2D(struct Vetor2D *vetorEntrada, struct Vetor2D *vetorSaida, float graus);


float DotProduct(struct Vetor2D *z, struct Vetor2D *e);







#endif

