// [shared.c]
// you should define the shared variable declared in the header here.

#include "shared.h"
#include "utility.h"
#include "game.h"
// #include "scene_menu.h"

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;
ALLEGRO_SAMPLE* themeMusic = NULL;
ALLEGRO_SAMPLE* pacman_intermission = NULL;
ALLEGRO_SAMPLE* win_sound = NULL;
ALLEGRO_SAMPLE* PACMAN_MOVESOUND = NULL;
ALLEGRO_SAMPLE* eat_ghost = NULL;
ALLEGRO_SAMPLE* game_bgm= NULL;
ALLEGRO_SAMPLE* point_sound = NULL;
ALLEGRO_SAMPLE* PACMAN_DEATH_SOUND = NULL;
ALLEGRO_SAMPLE* GAMEOVER = NULL;
ALLEGRO_FONT* menuFont = NULL;
ALLEGRO_FONT* menuFont2 = NULL;
ALLEGRO_FONT* menuFont3 = NULL;
ALLEGRO_FONT* menuFont4 = NULL;
int fontSize = 30;
float music_volume = 0.5;
float effect_volume = 0.5;
bool gameDone = false;

/*
	A way to accelerate is load assets once.
	And delete them at the end.
	This method does provide you better management of memory.
	
*/
void shared_init(void) {
	
	menuFont = load_font("Assets/Minecraft.ttf", 30);
	menuFont2 = load_font("Assets/OpenSans-Regular.ttf", 40);
	menuFont4 = load_font("Assets/Minecraft.ttf", 40);
	menuFont3 = load_font("Assets/Minecraft.ttf", 37);
	themeMusic = load_audio("Assets/Music/original_theme.ogg");
	pacman_intermission = load_audio("Assets/Music/pacman_intermission.ogg");
	PACMAN_MOVESOUND = load_audio("Assets/Music/pacman-chomp.ogg");
	game_bgm = load_audio("Assets/Music/game_bgm.mp3");
	eat_ghost = load_audio("Assets/Music/pacman_eatghost.ogg");
	point_sound = load_audio("Assets/Music/pointsound.mp3");
	win_sound = load_audio("Assets/Music/win.mp3");
	PACMAN_DEATH_SOUND = load_audio("Assets/Music/pacman_death.ogg");
	GAMEOVER = load_audio("Assets/Music/undertale.ogg");
}

void shared_destroy(void) {
	al_destroy_font(menuFont);
	al_destroy_font(menuFont2);
	al_destroy_font(menuFont3);
	al_destroy_font(menuFont4);
	al_destroy_sample(themeMusic);
	al_destroy_sample(pacman_intermission);
	al_destroy_sample(PACMAN_MOVESOUND);
	al_destroy_sample(win_sound);
	al_destroy_sample(eat_ghost);
	al_destroy_sample(PACMAN_DEATH_SOUND);
	al_destroy_sample(point_sound);
	al_destroy_sample(GAMEOVER);
	al_destroy_sample(game_bgm);
}