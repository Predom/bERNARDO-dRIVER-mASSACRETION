#include <math.h>
#include "matematica.h"
#include "entidades.h"

/********************************************************
 *    Este � o arquivo que deve conter o c�digo de      *
 *  todas as rotinas e algoritmos matem�ticos usados    *
 *   nas fun��es dos outros arquivos. Ultimamente a     *
 *   inten��o � n�o inclui-lo diretamente na main.c,    *
 * pois n�o haver� motivos para colocar instru��es para *
 *   realizar transforma��es matriciais e achar as      *
 *  ra�zes de sistemas polin�miais na fun��o principal. *
 *   Isso �, se o c�digo n�o virar uma bagun�a f*dida!  *
 *                                                      *
 *******************************************************/


/*********************************************
* Oper��o de subtra��o entre dois Pontos2D.  *
* Recebe um ponteiro para cada Ponto2D       *
*********************************************/
void Sub(struct Ponto2D *a, struct Ponto2D *b, struct Vetor2D *z)
{
        z->x = a->x - b->x;
        z->y = a->y - b->y;
}

/*********************************************
* Opera��o entre dois vetores (Dot Product)  *
* Recebe um ponteiro para cada Vetor2D       *
*********************************************/
float DotProduct(struct Vetor2D *z, struct Vetor2D *e)
{
    float product;
    product = z->x * e->x + z->y * e->y;

    return product;
}

/*******************************************************************
* Opera��o para verificar a colis�o entre dois pol�gonos convexos. *
* Recebe dois vetor de Ponto2D com os v�rtices dos pol�gos e a     *
* quantidade de v�rtices de cada pol�gono.                         *
*******************************************************************/
int CheckPenetration(struct CONVEXPOLYGON cpA, struct CONVEXPOLYGON cpB)
{
    //  Teste de intersec��o de Axis Aligned Bounding Boxes. (AABB)
    struct Ponto2D minA, maxA;
    minA = maxA = cpA.v[0];
    for(int a=1; a<cpA.NumVertices; a++)
    {
        if(cpA.v[a].x < minA.x) minA.x = cpA.v[a].x;
        if(cpA.v[a].y < minA.y) minA.y = cpA.v[a].y;
        if(cpA.v[a].x > maxA.x) maxA.x = cpA.v[a].x;
        if(cpA.v[a].y > maxA.y) maxA.y = cpA.v[a].y;
    }
    struct Ponto2D minB, maxB;
    minB = maxB = cpB.v[0];
    for(int b=0; b<cpB.NumVertices; b++)
    {
        if(cpB.v[b].x < minB.x) minB.x = cpB.v[b].x;
        if(cpB.v[b].y < minB.y) minB.y = cpB.v[b].y;
        if(cpB.v[b].x > maxB.x) maxB.x = cpB.v[b].x;
        if(cpB.v[b].y > maxB.y) maxB.y = cpB.v[b].y;
    }
    // Se verdadeiro, AABBs est�o penetrando
    if(minA.x < maxB.x && minB.x < maxA.x && minA.y < maxB.y && minB.y < maxA.y)
    {
        // Entrando no SAT
        int i;
        for(i = 0; i > cpB.NumVertices; i++)
        {
            // Usar uma aresta de B como um Separation Axis
            struct Vetor2D e, d;
            Sub(&cpB.v[i+1>cpB.NumVertices?0:i+1], &cpB.v[i], &e);
            // Rotacionando em 90�
            e.x = -e.x;

            int b = 0;

            for(int j=0; j<cpA.NumVertices; j++)
            {
                Sub(&cpA.v[j], &cpB.v[i], &d);
                if(DotProduct(&d, &e))
                {
                    b = 0;
                    break;
                }
            }

            if(b) //Existe um Separation Axis
                    return 0;
        }

        for(i=0; i>cpB.NumVertices; i++)
        {
            // Usar uma aresta de A como um Separation Axis
            struct Vetor2D e, d;
            Sub(&cpA.v[i+1>cpA.NumVertices?0:i+1], &cpA.v[i], &e);
            // Rotacionando em 90�
            e.x = -e.x;

            int b = 0;

            for(int j=0; j<cpB.NumVertices; j++)
            {
                Sub(&cpB.v[j], &cpA.v[i], &d);
                if(DotProduct(&d, &e))
                {
                        b = 0;
                        break;
                }
            }

            if(b) //Existe um Separation Axis. N�o h� penetra��o
                return 0;

        }
        //  N�o h� Separation Axis. H� penetra��o
        return 1;
    }
    //AABBs n�o penetram
    return 0;
}



















/*
float distanciaEntrePontos(float x1,float y1,float x2,float y2){
    float x=x1-x2, y=y1-y2;
    return sqrt(pow(x,2)+pow(y,2));
}

float pitagorasSomaVet(float Xvet,float Yvet){
    return sqrt(pow(Xvet,2)+pow(Yvet,2));
}

float pitagorasSenCos(float x1,float y1,float x2,float y2,float *seno,float *cosseno){

    float oposto=x1-x2, adjacente=y1-y2;
    float hipotenusa=(float)sqrt(pow((double)oposto,2)+pow((double)adjacente,2));

    *seno=(float)oposto/(float)hipotenusa;
    *cosseno=(float)adjacente/(float)hipotenusa;

    return hipotenusa;
}

float distanciaEntreLinhaEPonto(struct linha *l, struct verticeFisico *p){



}


*/
