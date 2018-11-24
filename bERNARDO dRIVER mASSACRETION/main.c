#include <stdio.h>
#include <stdlib.h>
#include "fisica.h"
#include "desenho.h"
#include "entidades.h"

int main()
{
    printf("Hello world!\n");
    //testando a edição simultânea
    printf("\nBerardo Piranha\n");

    struct Ponto2D vetorA[] = {{3, 5}, {2, 1}, {-1, 3}, {1, 7}};
    struct Ponto2D vetorB[] = {{6, 8}, {5, 3}, {2, 6}, {4, 10}};
    struct CONVEXPOLYGON cpA;
    struct CONVEXPOLYGON cpB;
    cpA.v = vetorA;
    cpA.NumVertices = 4;
    cpB.v = vetorB;
    cpB.NumVertices = 4;

    if(CheckPenetration(&cpA, &cpB))
        printf("Dentro");
    else
        printf("Fora");
    return 0;
}
