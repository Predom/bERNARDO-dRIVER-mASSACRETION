#include <math.h>
#include "matematica.h"

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
 ********************************************************/























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
