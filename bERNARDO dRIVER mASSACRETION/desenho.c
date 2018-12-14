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

desenhaPayer(struct Player *jogador,int WIDTH,int HEIGHT, int vy){

    al_draw_bitmap(jogador->sprite_player,WIDTH/2-500,HEIGHT/2+vy,0);
}
