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

desenhaPlayer(struct Player *jogador,int WIDTH,int HEIGHT, int vy,int player_width,int player_height){

    al_draw_rotated_bitmap(jogador->sprite_player,player_width/2-70,player_height/2,WIDTH/2,HEIGHT/2,jogador->angulo,0);
}
