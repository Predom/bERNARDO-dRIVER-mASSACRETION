#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

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


#define x coord<:0:>
#define y coord<:1:>

struct Ponto2D
{
    float coord[2];
};

struct Vetor2D
{
    float coord[2];
};

struct Matriz2x2{

    float elementos[2][2];
};

struct CONVEXPOLYGON
{
    struct Ponto2D* v; // Aray de vértices
    int NumVertices;
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

struct Vetor2D diferencaPontos(struct Ponto2D *Pa, struct Ponto2D *Pb)
{
    struct Vetor2D retorno;
    retorno.x=Pa->x - Pb->x;
    retorno.y=Pa->y - Pb->y;
    return retorno;
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

float DotProduct(struct Vetor2D *z, struct Vetor2D *e)
{
    float product;
    product = z->x * e->x + z->y * e->y;

    return product;
}

#define SQUAR(n)    (n*n)
#define CUBE(n)     (n*n*n)

float returnVetComp(struct Vetor2D *V){
    return sqrt(SQUAR(V->x)+SQUAR(V->y));
}

void normalizeVet(struct Vetor2D *V){
    float comp = returnVetComp(V);
    V->x = V->x/comp;
    V->y = V->y/comp;
}

float returnVetDirec(struct Vetor2D V){

    normalizeVet(&V);
    if(V.y>0)return acos(V.x);
    return acos(V.x)+M_PI;
}

int colisao(struct CONVEXPOLYGON *cpA, struct CONVEXPOLYGON *cpB){

    float direc[cpA->NumVertices];
    float distribuicao;

    for(int i = 0; i<cpB->NumVertices;i++){

        for(int ii=0;ii<cpA->NumVertices;ii++){
            direc[ii]=returnVetDirec(diferencaPontos(&cpA->v[ii],&cpB->v[i]));
        }
        distribuicao=0;
        for(int ii=1;ii<cpA->NumVertices;ii++){

            distribuicao += direc[ii]-direc[ii-1];
            if(fabs(distribuicao)>M_PI)return 1;
        }
    }
    return 0;
}


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
        for(i = 0; i < cpB->NumVertices; i++)
        {
            // Usar uma aresta de B como um Separation Axis
            struct Vetor2D e, d;
            float xm,ym;
            diferencaEntrePontos(&cpB->v[i+1>cpB->NumVertices?0:i+1], &cpB->v[i], &e);
            // Rotacionando em 90º
            xm = e.x;
            ym = e.y;
            e.x = ym;
            e.y = -xm;

            int b = 1;

            for(int j=0; j<cpA->NumVertices; j++)
            {
                diferencaEntrePontos(&cpA->v[j], &cpB->v[i], &d);//errado
                if(DotProduct(&d, &e)<0)
                {
                    b = 0;
                    break;
                }
            }

            if(b) //Existe um Separation Axis
                    return 0;
        }

        for(i=0; i<cpB->NumVertices; i++)
        {
            // Usar uma aresta de A como um Separation Axis
            struct Vetor2D e, d;
            float xm,ym;
            diferencaEntrePontos(&cpA->v[i+1>cpA->NumVertices?0:i+1], &cpA->v[i], &e);
            // Rotacionando em 90º
            xm = e.x;
            ym = e.y;
            e.x = ym;
            e.y = -xm;

            int b = 1;

            for(int j=0; j<cpB->NumVertices; j++)
            {
                diferencaEntrePontos(&cpB->v[j], &cpA->v[i], &d);
                if(DotProduct(&d, &e)<0)
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

void gerarPoligonoConvexoAleatorio(struct CONVEXPOLYGON *pol,int maxVert){

    struct Vetor2D Vmod;
    float graus = 180, proximTransf, inclReta, consReta;
    pol->NumVertices=1;

    Vmod.x=(float)(rand()%200)-100;
    Vmod.y=(float)(rand()%200)-100;
/*
    if(Vmod!=0)
        inclReta=Vmod.y/(Vmod.x+0.0001);
    else
        inclReta=800;
   */
    pol->v[0].x=(float)(rand()%600)+100;
    pol->v[0].y=(float)(rand()%600)+100;

    consReta=pol->v[0].y - pol->v[0].y*inclReta;

    int i;

    for(i=1;i<maxVert;i++){
        pol->v[i].x = pol->v[i-1].x + Vmod.x;
        pol->v[i].y = pol->v[i-1].y + Vmod.y;

        //verif se o ponto é válido


        pol->NumVertices++;

        normalizeVet(&Vmod);
        produtoVetEscaLRetOrig(&Vmod,(float)(rand()%380));
        proximTransf=(float)(rand()%180);

        if(proximTransf>graus)break;
        graus-=proximTransf;

        rotacionarVet2DRetOrig(&Vmod,proximTransf);
    }

}



void desenhaPoligono(struct CONVEXPOLYGON *pol, struct ALLEGRO_COLOR corPol,float thickness){

    int i;
    for(i=1;i<pol->NumVertices;i++){
        al_draw_line(pol->v[i-1].x,pol->v[i-1].y,pol->v[i].x,pol->v[i].y,corPol,thickness);
    }

    al_draw_line(pol->v[0].x, pol->v[0].y, pol->v[i-1].x, pol->v[i-1].y,corPol,thickness);
}





struct Ponto2D arrPontos1[20],arrPontos2[20];

struct CONVEXPOLYGON pol_1={arrPontos1,20},pol_2={arrPontos2,20};

struct ALLEGRO_COLOR cor;

struct Matriz2x2 matriz = {0.5,2,1,0};

struct Ponto2D PA={50,4}, PB={-89.5,5}, PR;

struct Vetor2D VA = {1,1}, VB = {0,50}, VR;




int height=720;
int width=1080;

int main(void){

	ALLEGRO_DISPLAY *tela = NULL;
	ALLEGRO_EVENT_QUEUE *filaEvento = NULL;
	int done=NULL;
	int redraw=1;
	float graus;

	if(!al_init())return -1;

	tela=al_create_display(width,height);

	if(!tela)return -2;

	al_init_primitives_addon();
	al_install_keyboard();

	filaEvento=al_create_event_queue();

	al_register_event_source(filaEvento,al_get_keyboard_event_source());

    srand(time(NULL));

	while(!done){

        if(redraw){
            redraw = 0;

            al_draw_line(width,height,0,height,al_map_rgb(rand()%256,rand()%256,rand()%256),50);

            gerarPoligonoConvexoAleatorio(&pol_1,20);
            gerarPoligonoConvexoAleatorio(&pol_2,20);

            if(CheckPenetration(&pol_1,&pol_2))cor=al_map_rgb(255,0,0);
            else cor=al_map_rgb(20,230,40);

            desenhaPoligono(&pol_1,cor,2);
            desenhaPoligono(&pol_2,cor,2);
/*
            al_draw_line(width/2, height/2,width/2+VB.x,height/2+VB.y,al_map_rgb(255,255,255),3);
            al_draw_circle(width/2,height/2,50,al_map_rgb(200,90,120),3);
            fflush(stdin); */
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
/*
            scanf("%f",&graus);
            rotacionarVet2DRetOrig(&VB,graus);
*/

        }

        ALLEGRO_EVENT evento;
        al_wait_for_event(filaEvento,&evento);

        if(evento.type==ALLEGRO_EVENT_KEY_DOWN){

            switch(evento.keyboard.keycode){
            al_clear_to_color(al_map_rgb(0,0,0));
                case ALLEGRO_KEY_ESCAPE:done=1;
            break;
                case ALLEGRO_KEY_SPACE:redraw=1;
            break;

            }
        }


	}

	al_destroy_event_queue(filaEvento);
	al_destroy_display(tela);



	return 0;
}

