#include <stdio.h>
#include <stdlib.h>
#include "fisica.h"
#include "desenho.h"
#include "entidades.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_image.h>
#undef x
#undef y

//este comentário é um teste


//GLOBALS
const int WIDTH = 1300;
const int HEIGHT = 800;
const int windowX = 100;
const int windowY = 0;
int p, o = 0;

#define bool int
#define true !0
#define false 0

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

    //testando a edição simultânea
    printf("\nBerardo Piranha 3.0\n");

    if(!TestCheckPenetration())
        printf("\nA colisao de poligonos esta funcionando corretamente\n");
    else
        printf("\nHouve algum erro! A colisao de poligonos nao esta funcionando corretamente\n");

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *play_button = NULL, *config_button = NULL, *credit_button = NULL;
    ALLEGRO_BITMAP *imagem_menu = NULL;


    if(!al_init())										//initialize Allegro
		return -1;

    //START MENU =======================================================================================

    display = al_create_display(WIDTH, HEIGHT);			//create our display object

    if(!display)										//test display object
		return -1;

    al_set_window_position(display, windowX, windowY);



	al_init_primitives_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();

    imagem_menu = al_load_bitmap("menu.bmp");

    int imagem_menu_width = al_get_bitmap_width(imagem_menu);
    int imagem_menu_height = al_get_bitmap_height(imagem_menu);

	al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	play_button = al_create_bitmap(100,10);
	config_button = al_create_bitmap(100,70);
	credit_button = al_create_bitmap(100,80);

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
                ev.mouse.y >= HEIGHT / 2 - al_get_bitmap_height(play_button) * 2 &&
                ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(play_button) * 5)
            {
                in_play_button = true;
                selecty = 0;
            }
            else
                in_play_button = false;

            if (ev.mouse.x >= WIDTH / 2 - al_get_bitmap_width(config_button) &&
                ev.mouse.x <= WIDTH / 2 + al_get_bitmap_width(config_button) &&
                ev.mouse.y >= HEIGHT / 2 + al_get_bitmap_height(config_button) &&
                ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(config_button) * 2)
            {
                in_config_button = true;
                selecty = 1;
            }
            else
                in_config_button = false;

            if (ev.mouse.x >= WIDTH / 2 - al_get_bitmap_width(credit_button) &&
                ev.mouse.x <= WIDTH / 2 + al_get_bitmap_width(credit_button) &&
                ev.mouse.y >= HEIGHT / 2 + al_get_bitmap_height(credit_button) * 2 &&
                ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(credit_button) * 2.875)
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
                ev.mouse.y >= HEIGHT / 2 - al_get_bitmap_height(play_button) * 2 &&
                ev.mouse.y <= HEIGHT / 2 + al_get_bitmap_height(play_button) * 5)
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

                al_draw_filled_rounded_rectangle(WIDTH/2-100,HEIGHT/2-20,WIDTH/2+100,HEIGHT/2+50,10,10,al_map_rgb(255,0,0));
                al_draw_filled_rounded_rectangle(WIDTH/2-100,HEIGHT/2+70,WIDTH/2+100,HEIGHT/2+140,10,10,al_map_rgb(255,0,0));
                al_draw_filled_rounded_rectangle(WIDTH/2-100,HEIGHT/2+160,WIDTH/2+100,HEIGHT/2+230,10,10,al_map_rgb(255,0,0));

                al_draw_rounded_rectangle(WIDTH/2-100,selecty*90+HEIGHT/2-20,WIDTH/2+100,selecty*90+HEIGHT/2+50,10,10,al_map_rgb(255,255,0), 5);
            }

            al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
        }

    }

    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);

    //START GAME ========================================================================================

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

    al_set_window_position(display, windowX, windowY);

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();
	timer = al_create_timer(0.0167);

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

            if(keys[UP])
                o-=3;            //FALTA A FUNÇÃO PRA MOVIMENTAR PARA FRENTE
            if(keys[DOWN])
                o+=3;            //FALTA A FUNÇÃO PRA FREAR
            if(keys[RIGHT])
                p+=3;            //FALTA A FUNÇÃO PRA VIRAR PARA A DIREITA
            if(keys[LEFT])
                p-=3;            //FALTA A FUNÇÃO PRA VIRAR PARA A ESQUERDA
            if(keys[SPACE])
                printf(" _ KEY SCAPE ");    //FALTA A FUNÇÃO PRA MOVIMENTAR PARA BOZINAR(?)

            if(!isGameOver)
            {
                printf("atualizacooes dos corpos na tela e teste de game over\n");
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
                al_draw_filled_circle(300+p,300+o,20,al_map_rgb(255,255,0));
                //DESENHA TUDO
            }
            else
            {
                printf("GAME OVER");
                //DESENHA A TELA DE GAME OVER
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
