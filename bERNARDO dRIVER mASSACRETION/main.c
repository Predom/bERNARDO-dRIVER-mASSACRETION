#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "fisica.h"
#include "desenho.h"
#include "entidades.h"
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
    bool play = false;
    bool quit = false;
	bool redraw = true;
	bool isGameOver = false;
	int selecty = 0;
	bool in_display = true;
	bool in_play_button = false;
	bool in_config_button = false;
	bool in_credit_button = false;
    int vx_1 = 0;
    int vx_2 = WIDTH;
    int vy = 0;
    float x = 1;
    int vet_linhas[] = {0,WIDTH-1000,WIDTH-700,WIDTH-400,WIDTH-100};
    struct Ponto2D vert_car[4] = {{200,200},{450,200},{450,350},{200,350}};


    setlocale(LC_ALL,"portuguese");

    //testando a edição simultânea
    printf("\nBerardo Piranha 3.0\n");

    if(!TestCheckPenetration())
        printf("\nA colisão de polígonos está funcionando corretamente\n");
    else
        printf("\nHouve algum erro! A colisão de polígonos não está funcionando corretamente\n");

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *play_button = NULL, *config_button = NULL, *credit_button = NULL;
    ALLEGRO_BITMAP *imagem_menu = NULL;
    ALLEGRO_BITMAP *rua_vazia = NULL;
    ALLEGRO_BITMAP *rua_vazia_180 = NULL;
    ALLEGRO_BITMAP *rua_bus = NULL;
    ALLEGRO_BITMAP *rua_lojas = NULL;
    ALLEGRO_BITMAP *rua_obstaculo = NULL;
    ALLEGRO_FONT *font_menu_48 = NULL;
    ALLEGRO_FONT *font_menu_40 = NULL;
    ALLEGRO_AUDIO_STREAM *musica_menu = NULL;
    ALLEGRO_AUDIO_STREAM *vrum = NULL;
    ALLEGRO_SAMPLE *start_som = NULL;


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
    if (!al_reserve_samples(5)){
        error_msg("Falha ao reservar amostrar de audio");
        return 0;
    }

	musica_menu = al_load_audio_stream("Sons\\Axel_Broke.ogg",4,1024);
	start_som = al_load_sample("Sons\\Engine_start.ogg");

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
	config_button = al_create_bitmap(100,10);
	credit_button = al_create_bitmap(100,10);

	///EVENTOS
	event_queue = al_create_event_queue();
	timer = al_create_timer(0.0167);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);

    while(!play)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            play = true;
            quit = true;
        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            if (ev.mouse.x >= WIDTH / 2 - al_get_bitmap_width(play_button)&&
                ev.mouse.x <= WIDTH / 2 + al_get_bitmap_width(play_button)&&
                ev.mouse.y >= HEIGHT / 2 + al_get_bitmap_height(play_button) * 11 &&
                ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(play_button) * 18)
            {
                in_play_button = true;
                selecty = 0;
            }
            else
                in_play_button = false;

            if (ev.mouse.x >= WIDTH / 2 - al_get_bitmap_width(config_button) &&
                ev.mouse.x <= WIDTH / 2 + al_get_bitmap_width(config_button) &&
                ev.mouse.y >= HEIGHT / 2 + al_get_bitmap_height(config_button) * 21 &&
                ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(config_button) * 28)
            {
                in_config_button = true;
                selecty = 1;
            }
            else
                in_config_button = false;

            if (ev.mouse.x >= WIDTH / 2 - al_get_bitmap_width(credit_button) &&
                ev.mouse.x <= WIDTH / 2 + al_get_bitmap_width(credit_button) &&
                ev.mouse.y >= HEIGHT / 2 + al_get_bitmap_height(credit_button) * 31 &&
                ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(credit_button) * 38)
            {
                in_credit_button = true;
                selecty = 2;
            }
            else
                in_credit_button = false;
        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if (ev.mouse.x >= WIDTH / 2 - al_get_bitmap_width(play_button)&&
                ev.mouse.x <= WIDTH / 2 + al_get_bitmap_width(play_button)&&
                ev.mouse.y >= HEIGHT / 2 - al_get_bitmap_height(play_button) * 11 &&
                ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(play_button) * 18)
            {
                play = true;

            }
        }

        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    {
                        play = true;
                        quit = true;

                    }break;
                case ALLEGRO_KEY_UP:
                    {
                        if(selecty==0)
                            selecty = 2;
                        else
                            selecty--;
                    }break;
                case ALLEGRO_KEY_DOWN:
                    {
                        if(selecty==2)
                            selecty = 0;
                        else
                            selecty++;
                    }break;
                case ALLEGRO_KEY_ENTER:
                    {
                        if(selecty==0)
                            play = true;
                    }break;
                case ALLEGRO_KEY_SPACE:
                    {
                        if(selecty==0)
                            play = true;
                    }break;
            }
        }

		if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            if(!play)
            {
                //DESENHA TUDO
                al_draw_scaled_bitmap(imagem_menu,0,0,imagem_menu_width,imagem_menu_height,0,0,WIDTH,HEIGHT,0);

                for(int k=110; k<=310; k+=100)
                {
                    al_draw_filled_rounded_rectangle(WIDTH/2-100,HEIGHT/2+k,WIDTH/2+100,HEIGHT/2+k+70,10,10,al_map_rgb(34,31,117));
                    al_draw_rounded_rectangle(WIDTH/2-100,HEIGHT/2+k,WIDTH/2+100,HEIGHT/2+k+70,10,10,al_map_rgb(0,0,0), 5);
                }

                al_draw_text(font_menu_48, al_map_rgb(0,0,0),WIDTH/2,HEIGHT/2+120,ALLEGRO_ALIGN_CENTRE,"Play");
                al_draw_text(font_menu_40, al_map_rgb(0,0,0),WIDTH/2,HEIGHT/2+220,ALLEGRO_ALIGN_CENTRE,"Options");
                al_draw_text(font_menu_40, al_map_rgb(0,0,0),WIDTH/2,HEIGHT/2+320,ALLEGRO_ALIGN_CENTRE,"Credits");
                al_draw_rounded_rectangle(WIDTH/2-100,selecty*100+HEIGHT/2+110,WIDTH/2+100,selecty*100+HEIGHT/2+180,10,10,al_map_rgb(255,255,255), 5);
            }

            al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
        }

        if(play)
            al_play_sample(start_som,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

    }

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
	rua_vazia = al_load_bitmap("Bitmaps\\Rua_vazia.bmp");
	rua_bus = al_load_bitmap("Bitmaps\\Rua_bus.bmp");
	rua_lojas = al_load_bitmap("Bitmaps\\Rua_lojas.bmp");
	rua_obstaculo = al_load_bitmap("Bitmaps\\Rua_obstaculo.bmp");//NÃO USAR

	int rua_width = al_get_bitmap_width(rua_vazia);
	int rua_height = al_get_bitmap_height(rua_vazia);

    ///EVENTOS-----------------------------------------------------------------------------
	event_queue = al_create_event_queue();
	timer = al_create_timer(0.008);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
    while(!quit)
    {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            if(keys[UP])                    //FALTA A FUNÇÃO PARA VIRAR PARA A ESQUERDA
                vy--;
            if(keys[DOWN])                  //FALTA A FUNÇÃO PARA VIRAR PARA A DIREITA
                vy++;
            if(keys[RIGHT])                 //FALTA A FUNÇÃO PARA MOVIMENTAR PARA FRENTE
            {
                if(x<3)
                    x+=0.001;
                al_set_audio_stream_gain(vrum,x);
                al_set_audio_stream_speed(vrum,x);
                if(vx_1<-WIDTH+6)
                {
                     vx_1=WIDTH;
                }

                else
                    vx_1-=3;
                if(vx_2<-WIDTH+6)
                {
                     vx_2=WIDTH;
                }
                else
                    vx_2-=3;
            }

            if(keys[LEFT])                  //FALTA A FUNÇÃO PARA FREAR
            {
                if(x>1)
                    x-=0.01;
                al_set_audio_stream_gain(vrum,x);
                al_set_audio_stream_speed(vrum,x);
            }

            if(keys[SPACE])                 //FALTA A FUNÇÃO A PARA BOZINAR(?)
                ;
            if(!isGameOver)
            {
                //CRIA NOVOS CARROS NA PISTA
                //ATUALIZÃO TUDO
                //TESTA COLISÕES
                //TESTE SE DEU GAME OVER
            }
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            quit = true;
        }

        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    quit = true;
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
				quit = true;
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
                    al_draw_scaled_bitmap(rua_bus,0,0,rua_width,rua_height,vx_1,0,WIDTH,HEIGHT,0);
                    al_draw_scaled_bitmap(rua_bus,0,0,rua_width,rua_height,vx_2,0,WIDTH,HEIGHT,0);

                al_draw_filled_rectangle(vert_car[0].coord[0],vert_car[0].coord[1]+vy,vert_car[2].coord[0],vert_car[2].coord[1]+vy,al_map_rgb(255,0,0));
            }
            else
            {
                ///DESENHA A TELA DE GAME OVER
                printf("GAME OVER");
            }

            al_flip_display();
			al_clear_to_color(al_map_rgb(100,100,100));
        }

    }

    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);

    //teste
    return 0;
}
