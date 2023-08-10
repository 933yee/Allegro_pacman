#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_gameover.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"

static ALLEGRO_BITMAP* gameover = NULL;
static int gameoverW;
static int gameoverH;

static void init() {
	gameover = load_bitmap("Assets/gameover.png");
	gameoverW = al_get_bitmap_width(gameover);
	gameoverH = al_get_bitmap_height(gameover);
}
static void draw(void) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	const float scale = 0.7;
	const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * gameoverW;
	const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * gameoverH;

	//draw title image
	al_draw_scaled_bitmap(
		gameover,
		0, 0,
		gameoverW, gameoverH,
		offset_w, offset_h,
		gameoverW * scale, gameoverH * scale,
		0
	);
}
static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {

}
static void on_mouse_down() {
}
static void destroy() {
}
static void on_key_down(int keycode) {
}
Scene scene_gameover_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.draw = &draw;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}