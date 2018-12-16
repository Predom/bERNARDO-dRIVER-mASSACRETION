    while(pag[MENU])
    {
        ALLEGRO_EVENT ev;                                                               // CRIA VARIAVEL DE EVENTO
        al_wait_for_event(event_queue, &ev);                                            // ESPERA POR UM EVENTO

        if(ev.type == ALLEGRO_EVENT_TIMER)                                              // EVENTO TIMER PARA ATUALIZAR A JANELA
        {
            redraw = true;
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)                                       // EVENTO DE FECHAMENTO DA JANELA
        {
            pag[MENU] = false
            ;
            pag[GAME] = false;
        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)                                     // EVENTO MOVIMENTO DO MOUSEE
        {
            if(pag[MENU]&&!pag[LORE]&&!pag[CREDIT])                                      // TESTA SE ESTÁ NA PAGINA MENU
            {
                if (ev.mouse.x >= Width / 2 - al_get_bitmap_width(play_button)&&
                ev.mouse.x <= Width / 2 + al_get_bitmap_width(play_button)&&
                ev.mouse.y >= Height / 2 + al_get_bitmap_height(play_button) * 11 &&
                ev.mouse.y <= Height / 2 + al_get_bitmap_height(play_button) * 18)
                {
                    if(!in_play_button)
                        al_play_sample(click,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    in_play_button = true;
                    selecty = 0;
                }
                else
                    in_play_button = false;

                if (ev.mouse.x >= Width / 2 - al_get_bitmap_width(lore_button) &&
                    ev.mouse.x <= Width / 2 + al_get_bitmap_width(lore_button) &&
                    ev.mouse.y >= Height / 2 + al_get_bitmap_height(lore_button) * 21 &&
                    ev.mouse.y <= Height / 2 + al_get_bitmap_height(lore_button) * 28)
                {
                    if(!in_lore_button)
                        al_play_sample(click,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    in_lore_button = true;
                    selecty = 1;
                }
                else
                    in_lore_button = false;

                if (ev.mouse.x >= Width / 2 - al_get_bitmap_width(credit_button) &&
                    ev.mouse.x <= Width / 2 + al_get_bitmap_width(credit_button) &&
                    ev.mouse.y >= Height / 2 + al_get_bitmap_height(credit_button) * 31 &&
                    ev.mouse.y <= Height / 2 + al_get_bitmap_height(credit_button) * 38)
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
                desenha_fundo(imagem_menu,imagem_menu_width,imagem_menu_height);
                desenha_botoes(font_menu_48,font_menu_40,selecty);
            }
            else if(pag[MENU]&&pag[LORE]&&!pag[CREDIT])
            {
                desenha_back_button(in_back_button);
                desenha_lore(font_menu_48,font_menu_40);
            }
            else if(pag[MENU]&&!pag[LORE]&&pag[CREDIT])
            {
                desenha_back_button(in_back_button);
                desenha_creditos(font_menu_48,font_menu_40);
            }

            al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
