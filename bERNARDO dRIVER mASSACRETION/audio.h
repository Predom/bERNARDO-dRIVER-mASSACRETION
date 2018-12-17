#include "matematica.h"
#include "fisica.h"
#include "entidades.h"
#undef x
#undef y
#include <allegro5\allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/**************************************
 * Essa é a header do audio.c         *
 **************************************/

void ligar_carro(bool *pag, ALLEGRO_SAMPLE *start);

void efeito_sonoro(ALLEGRO_SAMPLE *som, float vol, float vel);

void atualizaSomPlayer(struct Player *PLAYER, ALLEGRO_AUDIO_STREAM *som);
