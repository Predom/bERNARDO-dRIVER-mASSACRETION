#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "matematica.h"
#include "fisica.h"
#include "audio.h"
#include "entidades.h"

/****************************************************
 *  Este arquivo deve conter as funções de audio.   *
 ***************************************************/
void ligar_carro(bool *pag, ALLEGRO_SAMPLE *start)
{
    if(pag[0]&&!pag[1])
        al_play_sample(start,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

void efeito_sonoro(ALLEGRO_SAMPLE *som, float volume, float veloc)
{
    al_play_sample(som,volume,0,veloc,ALLEGRO_PLAYMODE_ONCE,NULL);
}

void atualizaSomPlayer(struct Player *PLAYER, ALLEGRO_AUDIO_STREAM *som)
{
    al_set_audio_stream_gain(som,calcNovoVolume(PLAYER));
    al_set_audio_stream_speed(som,calcNovaVeloc(PLAYER));
}

void TokyoDrift(ALLEGRO_AUDIO_STREAM *som, bool val)
{
    al_set_audio_stream_playing(som, val);
}
