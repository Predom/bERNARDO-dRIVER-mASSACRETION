#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "fisica.h"
#include "desenho.h"
#include "entidades.h"
#include "audio.h"
#undef x
#undef y
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//GLOBALS
const int WIDTH = 1300;
const int HEIGHT = 800;
const int windowX = 100;
const int windowY = 0;

int main()
{
    enum KEYS {UP, DOWN, RIGHT, LEFT, SPACE, ENTER};
    bool keys[6] = {false, false, false, false, false, false};

    enum PAGES {GAME, MENU, LORE, CREDIT};
    bool pag[4] = {true, true, false, false};

	bool redraw = true;
	bool isGameOver = false;

	bool in_display = true;
	bool in_play_button = false;
	bool in_lore_button = false;
	bool in_credit_button = false;
	bool in_back_button = false;

	int selecty = 0;

    float vx_1 = 0;
    float vx_2 = WIDTH;
    float vy = 0;
    float x = 0.5;

    setlocale(LC_ALL,"portuguese");

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *play_button = NULL;
    ALLEGRO_BITMAP *lore_button = NULL;
    ALLEGRO_BITMAP *credit_button = NULL;
    ALLEGRO_BITMAP *back_button = NULL;
    ALLEGRO_BITMAP *imagem_menu = NULL;
    ALLEGRO_BITMAP *rua_bus = NULL;
    ALLEGRO_FONT *font_menu_48 = NULL;
    ALLEGRO_FONT *font_menu_40 = NULL;
    ALLEGRO_AUDIO_STREAM *musica_menu = NULL;
    ALLEGRO_AUDIO_STREAM *vrum = NULL;
    ALLEGRO_SAMPLE *start_som = NULL;
    ALLEGRO_SAMPLE *click = NULL;
    ALLEGRO_SAMPLE *select = NULL;

    ///player declaração e init
    struct Ponto2D PLAYERMODELSOURCE[4]={{-200,-100},{-200,100},{200,100},{200,-100}};

    struct CONVEXPOLYGON PLAYERMODEL={PLAYERMODELSOURCE, 4};
    struct Ponto2D PLAYERMODELCACHE[4];
    struct Player PLAYER={{&PLAYERMODEL,{PLAYERMODELCACHE,4},0,0,0,0,0,10},1,1,1};

    srand(time(NULL));

    #include "INICIALIZAR_ALLEGRO.h"

    ///START MENU =======================================================================================

    #include "MENU.h"

    ligar_carro(pag,start_som);

    al_destroy_audio_stream(musica_menu);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);

    ///IN GAME ==========================================================================================

    ///DISPLAY-----------------------------------------------------------------------------
	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

    al_set_window_position(display, windowX, windowY);

    ///INICIALIZAÇÕES E INSTALAÇÕES--------------------------------------------------------
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();


	///AUDIO-------------------------------------------------------------------------------
    vrum = al_load_audio_stream("Sons\\Brum.ogg",255,100);
    al_attach_audio_stream_to_mixer(vrum, al_get_default_mixer());
    al_set_audio_stream_playmode(vrum, ALLEGRO_PLAYMODE_LOOP);

	///IMAGENS-----------------------------------------------------------------------------
	rua_bus = al_load_bitmap("Bitmaps\\Rua_bus.bmp");

	int rua_width = al_get_bitmap_width(rua_bus);
	int rua_height = al_get_bitmap_height(rua_bus);

    PLAYER.sprite_player = al_load_bitmap("Bitmaps\\sprite_player.bmp");

    int player_width = al_get_bitmap_width(PLAYER.sprite_player);
    int player_height = al_get_bitmap_height(PLAYER.sprite_player);

    ///EVENTOS-----------------------------------------------------------------------------
	event_queue = al_create_event_queue();
	timer = al_create_timer(0.008);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
    while(pag[GAME])
    {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            if(keys[UP])
                viraPraEsquerda(&PLAYER);
            if(keys[DOWN])
                viraPraDireita(&PLAYER);
            if(keys[RIGHT])
            {
                aceleraPlayer(&PLAYER);
            }

            if(keys[LEFT])
            {
                RePlayer(&PLAYER);
            }

            if(keys[SPACE])
            {
                 //FALTA A FUNÇÃO A PARA BOZINAR(?)
            }

            if(!isGameOver)
            {
                vy+=PLAYER.corpo.velocidade.coord[1];
                x+=PLAYER.corpo.velocidade.coord[0];
                atualizarPlayer(&PLAYER);
                if(vx_1-PLAYER.corpo.velocidade.coord[0]<=-WIDTH)
                {
                     vx_1=WIDTH+WIDTH+vx_1-PLAYER.corpo.velocidade.coord[0];
                }
                else
                    vx_1-=PLAYER.corpo.velocidade.coord[0];
                if(vx_2-PLAYER.corpo.velocidade.coord[0]<=-WIDTH)
                {
                     vx_2=WIDTH+WIDTH+vx_2-PLAYER.corpo.velocidade.coord[0];
                }
                else
                    vx_2-=PLAYER.corpo.velocidade.coord[0];
                //CRIA NOVOS CARROS NA PISTA
                //ATUALIZÃO TUDO
                //TESTA COLISÕES
                //TESTE SE DEU GAME OVER
            }
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            pag[GAME] = false;
        }

        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    pag[GAME] = false;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                {
                    mudaOtimeRate(0.25);
                    keys[SPACE] = true;
                }break;
            }
        }

        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				pag[GAME] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				{
                    mudaOtimeRate(1);
                    keys[SPACE] = true;
                }break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            if(!isGameOver)
            {
                ///DESENHA TUDO
                desenha_ruas(rua_bus,rua_width,rua_height,vx_1,vx_2,vy,WIDTH,HEIGHT);
                desenhaPlayer(&PLAYER,WIDTH,HEIGHT,0,player_width,player_height);

                printf("Velocidade\n x: %f      y: %f      direcao: %f    TMR: %f\n",PLAYER.corpo.velocidade.coord[0],PLAYER.corpo.velocidade.coord[1],PLAYER.corpo.angulo,retornaOtimeRate());

            }
            else
            {
                ///DESENHA A TELA DE GAME OVER
                printf("GAME OVER");
            }

            al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
        }

    }

    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);

    return 0;
}
