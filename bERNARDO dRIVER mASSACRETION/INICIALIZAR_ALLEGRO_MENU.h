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
    if (!al_reserve_samples(10))
        return -1;

	musica_menu = al_load_audio_stream("Sons\\Axel_Broke.ogg",4,1024);
	start_som = al_load_sample("Sons\\Engine_start.ogg");
	click = al_load_sample("Sons\\click.ogg");
	select = al_load_sample("Sons\\Select.ogg");

    al_attach_audio_stream_to_mixer(musica_menu, al_get_default_mixer());
    al_set_audio_stream_playmode(musica_menu, ALLEGRO_PLAYMODE_LOOP);

    ///FONTES-----------------------------------------------------------------------------
	font_menu_48 = al_load_font("Fontes\\arial.ttf",48,0);
	font_menu_40 = al_load_font("Fontes\\arial.ttf",40,0);

	///IMAGENS----------------------------------------------------------------------------
    imagem_menu = al_load_bitmap("Bitmaps\\menu.bmp");
    int imagem_menu_width = al_get_bitmap_width(imagem_menu);
    int imagem_menu_height = al_get_bitmap_height(imagem_menu);

    ///MOUSE------------------------------------------------------------------------------
	al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	play_button = al_create_bitmap(100,10);
	lore_button = al_create_bitmap(100,10);
	credit_button = al_create_bitmap(100,10);
	back_button = al_create_bitmap(55,55);

	///EVENTOS----------------------------------------------------------------------------
	event_queue = al_create_event_queue();
	timer = al_create_timer(0.0167);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);
