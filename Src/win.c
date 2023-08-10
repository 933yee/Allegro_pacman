#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"
static Button win;
static ALLEGRO_SAMPLE_ID WIN;
extern ALLEGRO_SAMPLE_ID menuBGM;
extern ALLEGRO_SAMPLE* win_sound;
extern ALLEGRO_SAMPLE_ID PACMAN_MOVESOUND_ID;
extern ALLEGRO_SAMPLE_ID GAME_BGM;
extern int game_main_Score;
static void init() {
	stop_bgm(menuBGM);
	stop_bgm(GAME_BGM);
	stop_bgm(PACMAN_MOVESOUND_ID);
	win = button_create(50, 10, 700, 700, "Assets/win.png", "Assets/win.png");
	WIN = play_bgm(win_sound, effect_volume);
	FILE* rk = fopen("Assets/score.txt", "a");
	fprintf(rk, "%d\n", game_main_Score);
	fclose(rk);
}


static void draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	drawButton(win);	
	char temp[300];
	sprintf(temp, "YOUR SCORE: %d", game_main_Score);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 200, 50),
		370,
		450,
		1,
		temp
	);
	
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2-20,
		SCREEN_H - 140,
		ALLEGRO_ALIGN_CENTER,
		"PRESS  \"ENTER\"  TO  CONTINUE"
	);
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {

}
static void destroy() {
	al_destroy_bitmap(win.default_img);
	al_destroy_bitmap(win.hovered_img);
}

static void on_key_down(int keycode) {

	switch (keycode) {
		case ALLEGRO_KEY_ENTER:
			stop_bgm(WIN);
			menuBGM = play_bgm(themeMusic, music_volume);
			game_change_scene(scene_menu_create());
			break;
		default:
			break;
	}
}
static void on_mouse_down() {

}
Scene scene_win_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Game Over";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	game_log("win scene created");
	return scene;
}