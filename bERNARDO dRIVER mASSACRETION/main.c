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

///GLOBALS
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

	struct Ponto2D localRua;

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

    srand(time(NULL));

    if(!al_init())										//initialize Allegro
		return -1;

    #include "INICIALIZAR_ALLEGRO_MENU.h"

    importa_width_height(WIDTH,HEIGHT);

    ///START MENU =======================================================================================
    #include "MENU.h"

    #include  "DESTRUIR_MENU.h"

    ligar_carro(pag,start_som);

    ///IN GAME ==========================================================================================
    #include "INICIALIZAR_ENTIDADES.h"

    #include "INICIALIZAR_ALLEGRO_JOGO.h"

    #include "JOGO.h"

    #include "DESTRUIR_JOGO.h"

    return 0;
}
