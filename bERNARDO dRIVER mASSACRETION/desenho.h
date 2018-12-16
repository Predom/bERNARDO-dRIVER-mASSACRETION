#ifndef DESENHO_H
#define DESENHO_H

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

/// Função para atualizar as variaveis globais
void atualiza_velplayer(struct Vetor2D v);
void atualiza_localRua();

/// Desenhos do Menu
void desenha_fundo(ALLEGRO_BITMAP *imagem, int imagem_width, int imagem_height);
void desenha_botoes(ALLEGRO_FONT *font48, ALLEGRO_FONT *font40, int select);
void desenha_back_button(int in_back_button);
void desenha_lore(ALLEGRO_FONT *font48, ALLEGRO_FONT *font40);
void desenha_creditos(ALLEGRO_FONT *font48, ALLEGRO_FONT *font40);

/// Desenhos durante o jogo
void desenha_metros(ALLEGRO_FONT *font48);
void desenha_ruas(ALLEGRO_BITMAP *imagem, int imagem_width, int imagem_height);
void desenhaPlayer(struct Player *jogador, int vy,int player_width,int player_height);

#endif // DESENHO_H
