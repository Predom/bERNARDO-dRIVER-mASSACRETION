#include "matematica.h"
#include "fisica.h"
#include "entidades.h"
#undef x
#undef y
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


/**************************************
 * Essa é a header do desenho.c
 **************************************/


/// Desenhos do Menu
void desenha_fundo(ALLEGRO_BITMAP *imagem, int imagem_width, int imagem_height, const int WIDTH, const int HEIGHT);
void desenha_botoes(ALLEGRO_FONT *font48, ALLEGRO_FONT *font40, int select,const int WIDTH, const int HEIGHT);
void desenha_back_button(int in_back_button);
void desenha_lore(ALLEGRO_FONT *font48, ALLEGRO_FONT *font40, const int WIDTH, const int HEIGHT);
void desenha_creditos(ALLEGRO_FONT *font48, ALLEGRO_FONT *font40, const int WIDTH, const int HEIGHT);

/// Desenhos durante o jogo
void desenha_ruas(ALLEGRO_BITMAP *imagem, int imagem_width, int imagem_height, float vx_1, float vx_2, float vy, const int WIDTH, const int HEIGHT);
void desenhaPlayer(struct Player *jogador,int WIDTH,int HEIGHT, int vy,int player_width,int player_height);

