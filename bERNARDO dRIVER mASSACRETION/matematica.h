#ifndef MATEMATICA_H
#define MATEMATICA_H
#include <math.h>
#include "entidades.h"

/**************************************
 * Essa � a header da matematica.c
 **************************************/






// Opera��o com Pol�gonos
int CheckPenetration(struct CONVEXPOLYGON *cpA, struct CONVEXPOLYGON *cpB);

int TestCheckPenetration();

// Opera��o com vetores:
void Sub(struct Ponto2D *a, struct Ponto2D *b, struct Vetor2D *z);

float DotProduct(struct Vetor2D *z, struct Vetor2D *e);
#endif

