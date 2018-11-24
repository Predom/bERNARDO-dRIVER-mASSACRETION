#include <stdio.h>
#include <stdlib.h>
#include "fisica.h"
#include "desenho.h"
#include "entidades.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

int main()
{
    int WIDTH = 1000;
    int HEIGHT = 800;
    int windowX = 200;
    int windowY = 0;
    bool done = false;
    //testando a edição simultânea
    printf("\nBerardo Piranha 2.0\n");

    if(!TestCheckPenetration())
        printf("\nA colisao de poligonos esta funcionando corretamente\n");
    else
        printf("\nHouve algum erro! A colisao de poligonos nao esta funcionando corretamente\n");

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

    al_set_window_position(display, windowX, windowY);

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();

	//al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
    }

    return 0;
}
