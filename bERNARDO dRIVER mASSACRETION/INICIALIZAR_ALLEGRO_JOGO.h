    ///DISPLAY-----------------------------------------------------------------------------
	display = al_create_display(WIDTH,HEIGHT);			//create our display object

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
    //al_set_audio_stream_playmode(vrum, ALLEGRO_PLAYMODE_LOOP);

	///IMAGENS-----------------------------------------------------------------------------
	rua_bus = al_load_bitmap("Bitmaps\\sem_nada.bmp");

	ALLEGRO_COLOR grama = al_map_rgb(32,192,64);

	int rua_width = al_get_bitmap_width(rua_bus);
	int rua_height = al_get_bitmap_height(rua_bus);

    PLAYER.sprite_player = al_load_bitmap("Bitmaps\\sprite_player.bmp");

    TESTER.sprite_carro = al_load_bitmap("Bitmaps\\sprite_player.bmp");

    int playerWidth = al_get_bitmap_width(PLAYER.sprite_player);
    int playerHeight = al_get_bitmap_height(PLAYER.sprite_player);

    atualizaCarroDimensoes(playerWidth,playerHeight);

    ///EVENTOS-----------------------------------------------------------------------------
	event_queue = al_create_event_queue();
	timer = al_create_timer(0.01);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
