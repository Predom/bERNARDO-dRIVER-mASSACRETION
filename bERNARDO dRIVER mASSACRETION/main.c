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

    if(!TestCheckPenetration())
        printf("\nA colisao de poligonos esta funcionando corretamente\n");
    else
        printf("\nHouve algum erro! A colisao de poligonos nao esta funcionando corretamente\n");


    return 0;
}
