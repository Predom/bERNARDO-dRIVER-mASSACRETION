#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "matematica.h"
#include "fisica.h"
#include "desenho.h"
#include "entidades.h"

/****************************************************
 *  Este arquivo deve conter as funções de desenho  *
 * que plotam na tela as entidades fisicas e exibem *
 * de alguma forma seu comportamento.               *
 ***************************************************/

struct Vetor2D VelPlayer={0,0};
struct Ponto2D localRua_A={0,0};
struct Ponto2D localRua_B={WIDTH,0};

void atualiza_velplayer(struct Vetor2D v)
{
    VelPlayer.coord[0] = v.coord[0];
    VelPlayer.coord[1] = v.coord[1];
}

///Desenhos do Menu
void desenha_fundo(ALLEGRO_BITMAP *imagem, int imagem_width, int imagem_height)
{
    al_draw_scaled_bitmap(imagem,0,0,imagem_width,imagem_height,0,0,WIDTH,HEIGHT,0);
}

void desenha_botoes(ALLEGRO_FONT *font48, ALLEGRO_FONT *font40, int select)
{
    for(int k=110; k<=310; k+=100)
    {
        al_draw_filled_rounded_rectangle(WIDTH/2-100,HEIGHT/2+k,WIDTH/2+100,HEIGHT/2+k+70,10,10,al_map_rgb(34,31,117));
        al_draw_rounded_rectangle(WIDTH/2-100,HEIGHT/2+k,WIDTH/2+100,HEIGHT/2+k+70,10,10,al_map_rgb(0,0,0), 5);
    }
    al_draw_text(font48, al_map_rgb(0,0,0),WIDTH/2,HEIGHT/2+120,ALLEGRO_ALIGN_CENTRE,"Play");
    al_draw_text(font48, al_map_rgb(0,0,0),WIDTH/2,HEIGHT/2+220,ALLEGRO_ALIGN_CENTRE,"Lore");
    al_draw_text(font40, al_map_rgb(0,0,0),WIDTH/2,HEIGHT/2+320,ALLEGRO_ALIGN_CENTRE,"Credits");
    al_draw_rounded_rectangle(WIDTH/2-100,select*100+HEIGHT/2+110,WIDTH/2+100,select*100+HEIGHT/2+180,10,10,al_map_rgb(255,255,255), 5);
}

void desenha_back_button(int in_back_button)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_filled_rounded_rectangle(5,5,60,60,10,10,al_map_rgb(34,31,117));
    al_draw_filled_triangle(10,32.5,32.5,10,32.5,55,al_map_rgb(255,255,255));
    al_draw_filled_rectangle(32.5,26,55,39,al_map_rgb(255,255,255));
    al_draw_rounded_rectangle(5,5,60,60,10,10,al_map_rgb(0,0,0),5);
    if(in_back_button)
        al_draw_rounded_rectangle(5,5,60,60,10,10,al_map_rgb(255,255,255),5);
}

void desenha_lore(ALLEGRO_FONT *font48, ALLEGRO_FONT *font40)
{
    al_draw_line(WIDTH/2-75,HEIGHT/2-300,WIDTH/2+75,HEIGHT/2-300,al_map_rgb(255,255,255),3);
    al_draw_rounded_rectangle(WIDTH/2-550,HEIGHT/2-275,WIDTH/2+550,HEIGHT/2+125,20,20,al_map_rgb(255,255,255),5);
    al_draw_text(font48, al_map_rgb(255,255,255),WIDTH/2,HEIGHT/2-350,ALLEGRO_ALIGN_CENTRE,"LORE");
    al_draw_text(font40, al_map_rgb(255,255,255),WIDTH/2-415,HEIGHT/2-250,0,"Depois de se tornar o homem mais based  do  mundo,");
    al_draw_text(font40, al_map_rgb(255,255,255),WIDTH/2-535,HEIGHT/2-200,0,"Bernardo   eh   perseguido   pelos    seus   inumeros   crimes.");
    al_draw_text(font40, al_map_rgb(255,255,255),WIDTH/2-535,HEIGHT/2-150,0,"Com incontaveis organizacoes governamentais no seu rastro,");
    al_draw_text(font40, al_map_rgb(255,255,255),WIDTH/2-535,HEIGHT/2-100,0,"voce  deve  assumir o volante e despistar seus perseguidores");
    al_draw_text(font40, al_map_rgb(255,255,255),WIDTH/2-535,HEIGHT/2-50,0,"com seu carro blindado feito em sua garagem.");
    al_draw_text(font40, al_map_rgb(255,255,255),WIDTH/2-415,HEIGHT/2,0,"Bernardo  tenta  fugir  de tudo e todos  dirigindo  como");
    al_draw_text(font40, al_map_rgb(255,255,255),WIDTH/2-535,HEIGHT/2+50,0,"se nao tivesse medo de morrer, apenas de ser pego.");
}

void desenha_creditos(ALLEGRO_FONT *font48, ALLEGRO_FONT *font40)
{
    al_draw_filled_rectangle(WIDTH/2-350,HEIGHT,WIDTH/2+350,0,al_map_rgb(0,0,0));
    al_draw_line(WIDTH/2-110,HEIGHT/2-300,WIDTH/2+110,HEIGHT/2-300,al_map_rgb(255,255,255),3);
    al_draw_text(font48, al_map_rgb(255,255,255),WIDTH/2,HEIGHT/2-350,ALLEGRO_ALIGN_CENTRE,"CREDITS");
    al_draw_text(font48, al_map_rgb(255,255,255),WIDTH/2,HEIGHT/2-270,ALLEGRO_ALIGN_CENTRE,"Desenvolvedores:");
    al_draw_text(font40, al_map_rgb(255,255,255),WIDTH/2,HEIGHT/2-200,ALLEGRO_ALIGN_CENTRE,"Theo Pires");
    al_draw_text(font40, al_map_rgb(255,255,255),WIDTH/2,HEIGHT/2-150,ALLEGRO_ALIGN_CENTRE,"Pedro de Lima Batista");
    al_draw_text(font48, al_map_rgb(255,255,255),WIDTH/2,HEIGHT/2-70,ALLEGRO_ALIGN_CENTRE,"Efeitos sonoros:");
    al_draw_text(font40, al_map_rgb(255,255,255),WIDTH/2,HEIGHT/2,ALLEGRO_ALIGN_CENTRE,"bERNARDO bORGES sANDOVAL");
}

/// Desenhos durante o Jogo
void atualiza_localRua()
{
    if(retornaSubVetorAoPonto(&localRua_A,&VelPlayer,0)<=-WIDTH)
    {
            localRua_A.coord[0]=2*WIDTH+retornaSubVetorAoPonto(&localRua_A,&VelPlayer,0);
    }
    else
        subtraiVetorAoPontoRetOrig(&localRua_A,&VelPlayer);
    if(retornaSubVetorAoPonto(&localRua_B,&VelPlayer,0)<=-WIDTH)
    {
            localRua_B.coord[0]=2*WIDTH+retornaSubVetorAoPonto(&localRua_B,&VelPlayer,0);
    }
    else
        subtraiVetorAoPontoRetOrig(&localRua_B,&VelPlayer);


}

void desenha_ruas(ALLEGRO_BITMAP *imagem, int imagem_width, int imagem_height)
{
    al_draw_scaled_bitmap(imagem,0,localRua_A.coord[1],imagem_width,imagem_height,localRua_A.coord[0],0,WIDTH,HEIGHT,0);
    al_draw_scaled_bitmap(imagem,0,localRua_B.coord[1],imagem_width,imagem_height,localRua_B.coord[0],0,WIDTH,HEIGHT,0);
}
void desenhaPlayer(struct Player *jogador, int vy,int player_width,int player_height){

    al_draw_rotated_bitmap(jogador->sprite_player,player_width/2-70,player_height/2,WIDTH/2,HEIGHT/2,jogador->corpo.angulo,0);
}

