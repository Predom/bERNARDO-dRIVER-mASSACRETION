#include <math.h>
#include "matematica.h"
#include "entidades.h"

/********************************************************
 *    Este é o arquivo que deve conter o código de      *
 *  todas as rotinas e algoritmos matemáticos usados    *
 *   nas funções dos outros arquivos. Ultimamente a     *
 *   intenção é não inclui-lo diretamente na main.c,    *
 * pois não haverá motivos para colocar instruções para *
 *   realizar transformações matriciais e achar as      *
 *  raízes de sistemas polinômiais na função principal. *
 *   Isso é, se o código não virar uma bagunça f*dida!  *
 *                                                      *
 *******************************************************/


/*********************************************
* Operção de subtração entre dois Pontos2D.  *
* Recebe um ponteiro para cada Ponto2D       *
*********************************************/
void Sub(struct Ponto2D *a, struct Ponto2D *b, struct Vetor2D *z)
{
        z->x = a->x - b->x;
        z->y = a->y - b->y;
}

/**************************************************
* Operações de soma e subtração com ponto e vetor *
***************************************************/

/*********************************
 * SUMÁRIO
 *
 * Ponto + Ponto = ???   <-N existe
 * Ponto - Ponto = Vetor
 * Ponto + Vetor = Ponto
 * Ponto - Vetor = Ponto
 *
 * Vetor + Ponto = ??? <- O que você tá tentando fazer?
 * Vetor - Ponto = ??? <-            \\
 *
 * Vetor + Vetor = Vetor
 * Vetor - Vetor = Vetor
 *
 **********************************/


void diferencaEntrePontos(struct Ponto2D *Pa, struct Ponto2D *Pb, struct Vetor2D *Vr)
{
    Vr->x = Pa->x - Pb->x;
    Vr->y = Pa->y - Pb->y;
}

void somaVetorAoPonto(struct Ponto2D *Pa, struct Vetor2D *Vb, struct Ponto2D *Pr)
{
    Pr->x = Pa->x + Vb->x;
    Pr->y = Pa->y + Vb->y;
}

void subtraiVetorDoPonto(struct Ponto2D *Pa, struct Vetor2D *Vb, struct Ponto2D *Pr)
{
    Pr->x = Pa->x - Vb->x;
    Pr->y = Pa->y - Vb->y;
}

void somaVetores(struct Vetor2D *Va, struct Vetor2D *Vb, struct Vetor2D *Vr)
{
    Vr->x = Va->x + Vb->x;
    Vr->y = Va->y + Vb->y;
}

void subtraiVetores(struct Vetor2D *Va, struct Vetor2D *Vb, struct Vetor2D *Vr)
{
    Vr->x = Va->x - Vb->x;
    Vr->y = Va->y - Vb->y;
}

//Pra multiplicar um vetor por uma escalar
void produtoVetEscaLRetOrig(struct Vetor2D *V, float Escalar){
    V->x=V->x*Escalar;
    V->y=V->y*Escalar;
}

void produtoVetEscaL(struct Vetor2D *VA, struct Vetor2D *VR, float Escalar){
    VR->x=VA->x*Escalar;
    VR->y=VA->y*Escalar;
}

/*********************************************
* Operação entre dois vetores (Dot Product)  *
* Recebe um ponteiro para cada Vetor2D       *
*********************************************/
float DotProduct(struct Vetor2D *z, struct Vetor2D *e)
{
    float product;
    product = z->x * e->x + z->y * e->y;

    return product;
}

float returnComp(struct Vetor2D *V){
    return sqrt(SQUAR(V->x)+SQUAR(V->y));
}

void normalizeVet(struct Vetor2D *V){
    float comp = returnVetComp(V);
    V->x = V->x/comp;
    V->y = V->y/comp;
}

void retornarNormalizado(struct Vetor2D *V, struct Vetor2D *destino){
    float comp = returnVetComp(V);
    destino->x=V->x/comp;
    destino->y=V->y/comp};
};




/***********************************************************************************
 *  Essas funções obétm o produto do vetor pela matriz para aplicar a transformação
 * representada pela matriz no vetor. A transVet2DRetOrig() devolve o resultado
 * diretamente no vetor de entada, sobrescrevendo-o, já a transVet2D()
 * guarda o resultado em um outro vetor.
 *  Todas as funções são específicas para trabalhar com vetores bidimensionais e
 * matrizes 2x2.
 *************************************************************************************/

/******************************************************************************/
void transVet2DRetOrig(struct Vetor2D *vetor, struct Matriz2x2 *matriz){

    float memoria[2];

    //guarda o conteudo original do vetor na memória e zera-o
    for(int i=0; i<2; i++){
            memoria[i]=vetor->coord[i];
            vetor->coord[i]=0;
    }

    //reescreve o original com seus valores originais transformados
    for(int i=0; i<2; i++){
        for(int ii=0; ii<2; ii++){
            vetor->coord[i]+=memoria[ii]*matriz->elementos[i][ii];
        }
    }


}

void transVet2D(struct Vetor2D *vetorEntrada, struct Vetor2D *vetorSaida, struct Matriz2x2 *matriz){


    for(int i=0; i<2; i++){
            //zera o elemento a ser sobreescrito na saída
            vetorSaida->coord[i]=0;

        for(int ii=0; ii<2; ii++){

            vetorSaida->coord[i]+=vetorEntrada->coord[ii]*matriz->elementos[i][ii];
        }
    }


}
/******************************************************************************/

void rotacionarVet2DRetOrig(struct Vetor2D *vetor, float graus){

    float grausConv=graus*(M_PI/180);
    float s=sin(grausConv);
    float c=cos(grausConv);

    struct Matriz2x2 matriz={c,-s,s,c};

    transVet2DRetOrig(vetor,&matriz);

}

void rotacionarVet2D(struct Vetor2D *vetorEntrada, struct Vetor2D *vetorSaida, float graus){

    float grausConv=(graus/180)* M_PI;
    float s=sin(grausConv);
    float c=cos(grausConv);

    struct Matriz2x2 matriz={c,-s,s,c};

    transVet2D(vetorEntrada,vetorSaida,&matriz);

}






/*******************************************************************
* Operação para verificar a colisão entre dois polígonos convexos. *
* Recebe dois vetor de Ponto2D com os vértices dos polígos e a     *
* quantidade de vértices de cada polígono.                         *
*******************************************************************/
int CheckPenetration(struct CONVEXPOLYGON *cpA, struct CONVEXPOLYGON *cpB)
{
    //  Teste de intersecção de Axis Aligned Bounding Boxes. (AABB)
    struct Ponto2D minA, maxA;
    minA = maxA = cpA->v[0];
    for(int a=1; a<cpA->NumVertices; a++)
    {
        if(cpA->v[a].x < minA.x) minA.x = cpA->v[a].x;
        if(cpA->v[a].y < minA.y) minA.y = cpA->v[a].y;

        if(cpA->v[a].x > maxA.x) maxA.x = cpA->v[a].x;
        if(cpA->v[a].y > maxA.y) maxA.y = cpA->v[a].y;
    }
    struct Ponto2D minB, maxB;
    minB = maxB = cpB->v[0];
    for(int b=0; b<cpB->NumVertices; b++)
    {
        if(cpB->v[b].x < minB.x) minB.x = cpB->v[b].x;
        if(cpB->v[b].y < minB.y) minB.y = cpB->v[b].y;

        if(cpB->v[b].x > maxB.x) maxB.x = cpB->v[b].x;
        if(cpB->v[b].y > maxB.y) maxB.y = cpB->v[b].y;
    }
    // Se verdadeiro, AABBs estão penetrando
    if(minA.x < maxB.x && minB.x < maxA.x &&
       minA.y < maxB.y && minB.y < maxA.y)
    {
        // Entrando no SAT
        int i;
        for(i = 0; i > cpB->NumVertices; i++)
        {
            // Usar uma aresta de B como um Separation Axis
            struct Vetor2D e, d;
            diferencaEntrePontos(&cpB->v[i+1>cpB->NumVertices?0:i+1], &cpB->v[i], &e);
            // Rotacionando em 90º
            e.x = -e.x;

            int b = 0;

            for(int j=0; j<cpA->NumVertices; j++)
            {
                diferencaEntrePontos(&cpA->v[j], &cpB->v[i], &d);//errado
                if(DotProduct(&d, &e))
                {
                    b = 0;
                    break;
                }
            }

            if(b) //Existe um Separation Axis
                    return 0;
        }

        for(i=0; i>cpB->NumVertices; i++)
        {
            // Usar uma aresta de A como um Separation Axis
            struct Vetor2D e, d;
            diferencaEntrePontos(&cpA->v[i+1>cpA->NumVertices?0:i+1], &cpA->v[i], &e);
            // Rotacionando em 90º
            e.x = -e.x;

            int b = 0;

            for(int j=0; j<cpB->NumVertices; j++)
            {
                diferencaEntrePontos(&cpB->v[j], &cpA->v[i], &d);
                if(DotProduct(&d, &e))
                {
                        b = 0;
                        break;
                }
            }

            if(b) //Existe um Separation Axis. Não há penetração
                return 0;

        }
        //  Não há Separation Axis. Há penetração
        return 1;
    }
    //AABBs não penetram
    return 0;
}

/**************************************************************************
* Operação para testar a função de colisão entre dois polígonos convexos. *
**************************************************************************/

int TestCheckPenetration()
{
    struct Ponto2D vetorA[] = {{3, 5}, {2, 1}, {-1, 3}, {1, 7}};
    struct Ponto2D vetorB[] = {{6, 8}, {5, 3}, {2, 6}, {4, 10}};
    struct CONVEXPOLYGON cpA;
    struct CONVEXPOLYGON cpB;
    cpA.v = vetorA;
    cpA.NumVertices = 4;
    cpB.v = vetorB;
    cpB.NumVertices = 4;

    if(CheckPenetration(&cpA, &cpB))
    {
        struct Ponto2D vetorC[] = {{7, 9}, {6, 4}, {3, 7}, {5, 11}};
        struct CONVEXPOLYGON cpC;
        cpC.v = vetorC;
        cpC.NumVertices = 4;

        if(!CheckPenetration(&cpA, &cpC))
            return 0;
        else
            return 1;
    }
    else
        return 1;
}





