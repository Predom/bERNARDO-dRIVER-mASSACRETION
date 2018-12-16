/**************************************
 * Essa é a header da matematica.c
 **************************************/


#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		0.69314718055994530942
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440
#define SQUAR(n)    (n*n)
#define CUBE(n)     (n*n*n)


#ifndef MATEMATICA_H
#define MATEMATICA_H
#include <math.h>
#include "entidades.h"


// Operação com Polígonos
int CheckPenetration(struct CONVEXPOLYGON *cpA, struct CONVEXPOLYGON *cpB);

int TestCheckPenetration();

// Operação com vetores:
void diferencaEntrePontos(struct Ponto2D *Pa, struct Ponto2D *Pb, struct Vetor2D *Vr);

void somaVetorAoPonto(struct Ponto2D *Pa, struct Vetor2D *Vb, struct Ponto2D *Pr);

void somaVetorAoPontoRetOrig(struct Ponto2D *Pa, struct Vetor2D *Vb);

void subtraiVetorDoPonto(struct Ponto2D *Pa, struct Vetor2D *Vb, struct Ponto2D *Pr);

void somaVetores(struct Vetor2D *Va, struct Vetor2D *Vb, struct Vetor2D *Vr);

void somaVetoresRetOrig(struct Vetor2D *Va, struct Vetor2D *Vb);

void subtraiVetores(struct Vetor2D *Va, struct Vetor2D *Vb, struct Vetor2D *Vr);

void subtraiVetoresRetOrig(struct Vetor2D *Va, struct Vetor2D *Vb);

void produtoVetEscaLRetOrig(struct Vetor2D *V, float Escalar);

void produtoVetEscaL(struct Vetor2D *VA, struct Vetor2D *VR, float Escalar);

float DotProduct(struct Vetor2D *z, struct Vetor2D *e);

float returnComp(struct Vetor2D *V);

void normalizeVet(struct Vetor2D *V);

void retornarNormalizado(struct Vetor2D *V, struct Vetor2D *destino);

float returnVetDirec(struct Vetor2D V);

struct Vetor2D produtoVetEscaLRet(struct Vetor2D VA, float Escalar);

struct Vetor2D retornarNormalizadoSPont(struct Vetor2D *V);

void somaVetorAoPoligonoRetOrig(struct CONVEXPOLYGON *poligonoentrada,struct CONVEXPOLYGON *poligonosaida,struct Vetor2D *V);

//transformar e girar vetores
void transVet2DRetOrig(struct Vetor2D *vetor, struct Matriz2x2 *matriz);

void transVet2D(struct Vetor2D *vetorEntrada, struct Vetor2D *vetorSaida, struct Matriz2x2 *matriz);

void rotacionarVet2DRetOrig(struct Vetor2D *vetor, float graus);

void rotacionarVet2D(struct Vetor2D *vetorEntrada, struct Vetor2D *vetorSaida, float graus);








#endif



