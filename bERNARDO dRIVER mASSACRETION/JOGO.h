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
                 //FALTA A FUN��O A PARA BOZINAR(?)
            }

            if(keys[LEFT]&&keys[DOWN]&&keys[RIGHT])
            {
                driftOn(&PLAYER);
                TokyoDrift(tokyo_drift,true);
            }
            else
            {
                if(al_get_audio_stream_playing(tokyo_drift))
                {
                    driftOff();
                    TokyoDrift(tokyo_drift,false);
                }
            }

            if(!isGameOver)
            {
                #include "ATUALIZALOOP.h"
                //CRIA NOVOS CARROS NA PISTA
                //ATUALIZ�O TUDO
                //TESTA COLIS�ES
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
                #include "DESENHOLOOP.h"
                ///DESENHA TUDO
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
