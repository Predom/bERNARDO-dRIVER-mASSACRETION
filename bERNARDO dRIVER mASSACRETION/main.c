#include <stdio.h>
#include <stdlib.h>
#include "fisica.h"
#include "desenho.h"
#include "entidades.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

//GLOBALS
const int WIDTH = 1300;
const int HEIGHT = 800;
const int windowX = 100;
const int windowY = 0;
enum KEYS {UP, DOWN, RIGHT, LEFT, SPACE};
bool keys[5] = {false, false, false, false, false};

int main()
{
    bool done = false;
	bool redraw = true;
	const int FPS = 60;
	bool isGameOver = false;

    //testando a edição simultânea
    printf("\nBerardo Piranha 3.0\n");

    if(!TestCheckPenetration())
        printf("\nA colisao de poligonos esta funcionando corretamente\n");
    else
        printf("\nHouve algum erro! A colisao de poligonos nao esta funcionando corretamente\n");

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    //ALLEGRO_TIMER *timer = NULL;

    if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

    al_set_window_position(display, windowX, windowY);

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();
	//timer = al_create_timer(1 / FPS);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    //al_start_timer(timer);
    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        /*if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            if(keys[UP])
                printf(" ^ KEY UP ");       //FALTA A FUNÇÃO PRA MOVIMENTAR PARA FRENTE
            if(keys[DOWN])
                printf(" | KEY DOWN ");     //FALTA A FUNÇÃO PRA FREAR
            if(keys[RIGHT])
                printf(" -> KEY RIGHT ");   //FALTA A FUNÇÃO PRA VIRAR PARA A DIREITA
            if(keys[LEFT])
                printf(" <- KEY LEFT ");    //FALTA A FUNÇÃO PRA VIRAR PARA A ESQUERDA
            if(keys[SPACE])
                printf(" _ KEY SCAPE ");    //FALTA A FUNÇÃO PRA MOVIMENTAR PARA BOZINAR(?)

            if(!isGameOver)
            {
                printf("atualizacooes dos corpos na tela\ne teste de game over\n");
                //CRIA NOVOS CARROS NA PISTA
                //ATUALIZÃO TUDO
                //TESTA COLISÕES
                //TESTE SE DEU GAME OVER
            }
        }*/

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }

        /*else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
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
				done = true;
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
            //redraw = false;

            if(!isGameOver)
            {
                al_draw_line(300,300,700,700,al_map_rgb(255,255,0),3);
                //DESENHA TUDO
            }
            else
            {
                printf("GAME OVER");
                //DESENHA A TELA DE GAME OVER
            }

            al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
        }*/

        al_destroy_event_queue(event_queue);
        //al_destroy_timer(timer);
        al_destroy_display(display);
    }

    return 0;
}
