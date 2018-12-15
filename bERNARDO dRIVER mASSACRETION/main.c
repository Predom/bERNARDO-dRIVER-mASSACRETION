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


void error_msg(char *text){
	al_show_native_message_box(NULL,"ERRO",
		"Ocorreu o seguinte erro e o programa sera finalizado:",
		text,NULL,ALLEGRO_MESSAGEBOX_ERROR);
}


//GLOBALS
const int WIDTH = 1300;
const int HEIGHT = 800;
const int windowX = 100;
const int windowY = 0;


enum KEYS {UP, DOWN, RIGHT, LEFT, SPACE, ENTER};
bool keys[6] = {false, false, false, false, false, false};

int main()
{
    enum PAGES {GAME, MENU, LORE, CREDIT};
    bool pag[4] = {true, true, false, false};
	bool redraw = true;
	bool isGameOver = false;
	int selecty = 0;
	bool in_display = true;
	bool in_play_button = false;
	bool in_lore_button = false;
	bool in_credit_button = false;
	bool in_back_button = false;
    float vx_1 = 0;
    float vx_2 = WIDTH;
    float vy = 0;
    float x = 0.5;

    setlocale(LC_ALL,"portuguese");

    if(!TestCheckPenetration())
        printf("\nA colisão de polígonos está funcionando corretamente\n");
    else
        printf("\nHouve algum erro! A colisão de polígonos não está funcionando corretamente\n");

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

    if(!al_init())										//initialize Allegro
		return -1;

    ///START MENU =======================================================================================

    ///DISPLAY-------------------------------------------------------------------------
    display = al_create_display(WIDTH, HEIGHT);			//create our display object

    if(!display)										//test display object
		return -1;

    al_set_window_position(display, windowX, windowY);

    ///INICIALIZAÇÕES E INSTALAÇÕES-----------------------------------------------------
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_acodec_addon();
	al_install_audio();

	///AUDIO-----------------------------------------------------------------------------
    if (!al_reserve_samples(10)){
        error_msg("Falha ao reservar amostrar de audio");
        return 0;
    }

	musica_menu = al_load_audio_stream("Sons\\Axel_Broke.ogg",4,1024);
	start_som = al_load_sample("Sons\\Engine_start.ogg");
	click = al_load_sample("Sons\\click.ogg");
	select = al_load_sample("Sons\\Select.ogg");

	if(!musica_menu)
	{
	    error_msg( "Audio nao carregado" );
	    return -1;
	}

    al_attach_audio_stream_to_mixer(musica_menu, al_get_default_mixer());
    al_set_audio_stream_playmode(musica_menu, ALLEGRO_PLAYMODE_LOOP);

    ///FONTES-----------------------------------------------------------------------------
	font_menu_48 = al_load_font("Fontes\\arial.ttf",48,0);
	font_menu_40 = al_load_font("Fontes\\arial.ttf",40,0);

	///IMAGENS----------------------------------------------------------------------------
    imagem_menu = al_load_bitmap("Bitmaps\\menu.bmp");
    int imagem_menu_width = al_get_bitmap_width(imagem_menu);
    int imagem_menu_height = al_get_bitmap_height(imagem_menu);

    ///MOUSE
	al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	play_button = al_create_bitmap(100,10);
	lore_button = al_create_bitmap(100,10);
	credit_button = al_create_bitmap(100,10);
	back_button = al_create_bitmap(55,55);

	///EVENTOS
	event_queue = al_create_event_queue();
	timer = al_create_timer(0.0167);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);

    while(pag[MENU])
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            pag[MENU] = false;
            pag[GAME] = false;
        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            if(pag[MENU]&&!pag[LORE]&&!pag[CREDIT])
            {
                if (ev.mouse.x >= WIDTH / 2 - al_get_bitmap_width(play_button)&&
                ev.mouse.x <= WIDTH / 2 + al_get_bitmap_width(play_button)&&
                ev.mouse.y >= HEIGHT / 2 + al_get_bitmap_height(play_button) * 11 &&
                ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(play_button) * 18)
                {
                    if(!in_play_button)
                        al_play_sample(click,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    in_play_button = true;
                    selecty = 0;
                }
                else
                    in_play_button = false;

                if (ev.mouse.x >= WIDTH / 2 - al_get_bitmap_width(lore_button) &&
                    ev.mouse.x <= WIDTH / 2 + al_get_bitmap_width(lore_button) &&
                    ev.mouse.y >= HEIGHT / 2 + al_get_bitmap_height(lore_button) * 21 &&
                    ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(lore_button) * 28)
                {
                    if(!in_lore_button)
                        al_play_sample(click,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    in_lore_button = true;
                    selecty = 1;
                }
                else
                    in_lore_button = false;

                if (ev.mouse.x >= WIDTH / 2 - al_get_bitmap_width(credit_button) &&
                    ev.mouse.x <= WIDTH / 2 + al_get_bitmap_width(credit_button) &&
                    ev.mouse.y >= HEIGHT / 2 + al_get_bitmap_height(credit_button) * 31 &&
                    ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(credit_button) * 38)
                {
                    if(!in_credit_button)
                        al_play_sample(click,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    in_credit_button = true;
                    selecty = 2;
                }
                else
                    in_credit_button = false;
            }
            else if(pag[MENU]&&pag[LORE]&&!pag[CREDIT])
            {
                if (ev.mouse.x >= 5 && ev.mouse.x <= 60 &&
                    ev.mouse.y >= 5 && ev.mouse.y <= 60)
                {
                    if(!in_back_button)
                        al_play_sample(click,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                      in_back_button = true;
                }
                else
                    in_back_button = false;
            }
            else if(pag[MENU]&&!pag[LORE]&&pag[CREDIT])
            {
                if (ev.mouse.x >= 5 && ev.mouse.x <= 60 &&
                    ev.mouse.y >= 5 && ev.mouse.y <= 60)
                {
                    if(!in_back_button)
                        al_play_sample(click,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                      in_back_button = true;
                }
                else
                    in_back_button = false;
            }
        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if(pag[MENU]&&!pag[LORE]&&!pag[CREDIT])
            {
                if (in_play_button)
                {
                    al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    pag[MENU] = false;
                }
                else if (in_lore_button)
                {
                    al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    pag[LORE] = true;
                }
                else if (in_credit_button)
                {
                    al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    pag[CREDIT] = true;
                }
            }
            else if(pag[MENU]&&pag[LORE]&&!pag[CREDIT])
            {
                if(in_back_button)
                {
                    al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    pag[LORE] = false;
                }

            }
            else if(pag[MENU]&&!pag[LORE]&&pag[CREDIT])
            {
                if(in_back_button)
                {
                    al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    pag[CREDIT] = false;
                }
            }
        }

        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(pag[MENU]&&!pag[LORE]&&!pag[CREDIT])
            {
                switch(ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ESCAPE:
                    {
                        al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                        pag[MENU] = false;
                        pag[GAME] = false;
                    }break;
                    case ALLEGRO_KEY_UP:
                    {
                        if(selecty==0)
                            selecty = 2;
                        else
                            selecty--;
                        al_play_sample(click,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    }break;
                    case ALLEGRO_KEY_DOWN:
                    {
                        if(selecty==2)
                            selecty = 0;
                        else
                            selecty++;
                        al_play_sample(click,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    }break;
                    case ALLEGRO_KEY_ENTER:
                    {
                        if(selecty==0)
                        {
                            pag[MENU] = false;
                            al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                        }
                        else if(selecty==1)
                        {
                            pag[LORE] = true;
                            al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                        }
                        else if (selecty==2)
                        {
                            pag[CREDIT] = true;
                            al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                        }
                    }break;
                    case ALLEGRO_KEY_SPACE:
                    {
                        if(selecty==0)
                        {
                            pag[MENU] = false;
                            al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                        }
                        else if(selecty==1)
                        {
                            pag[LORE] = true;
                            al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                        }
                        else if (selecty==2)
                        {
                            pag[CREDIT] = true;
                            al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                        }
                    }break;
                }
            }
            else if(pag[MENU]&&pag[LORE]&&!pag[CREDIT])
            {
                switch(ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ESCAPE:
                    {
                        pag[LORE] = false;
                        al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    }break;
                }
            }
            else if(pag[MENU]&&!pag[LORE]&&pag[CREDIT])
            {
                switch(ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ESCAPE:
                    {
                        pag[CREDIT] = false;
                        al_play_sample(select,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    }break;
                }
            }
        }

		if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            if(pag[MENU]&&!pag[LORE]&&!pag[CREDIT])
            {
                desenha_fundo(imagem_menu,imagem_menu_width,imagem_menu_height,WIDTH,HEIGHT);
                desenha_botoes(font_menu_48,font_menu_40,selecty,WIDTH,HEIGHT);
            }
            else if(pag[MENU]&&pag[LORE]&&!pag[CREDIT])
            {
                desenha_back_button(in_back_button);
                desenha_lore(font_menu_48,font_menu_40,WIDTH,HEIGHT);
            }
            else if(pag[MENU]&&!pag[LORE]&&pag[CREDIT])
            {
                desenha_back_button(in_back_button);
                desenha_creditos(font_menu_48,font_menu_40,WIDTH,HEIGHT);
            }

            al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

    if(pag[GAME]&&!pag[MENU])
        al_play_sample(start_som,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

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
                mudaOtimeRate(0.25); //FALTA A FUNÇÃO A PARA BOZINAR(?)
            }else mudaOtimeRate(1);
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
                    keys[SPACE] = true;
                    break;
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
				keys[SPACE] = false;
				break;
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

                //printf("Velocidade\n x: %f      y: %f      direcao: %f     velocidade_modulo\n",PLAYER.velocidade.coord[0],PLAYER.velocidade.coord[1],PLAYER.angulo,PLAYER.velocidadeModulo);

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
