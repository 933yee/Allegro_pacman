
#include "rank.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"


static Button backbutton;

static void init() {
	backbutton = button_create(630, 20, 140, 70, "Assets/back.png", "Assets/back2.png");

}


static void draw() {

	al_clear_to_color(al_map_rgb(0, 0, 0));
	drawButton(backbutton);


}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	backbutton.hovered = buttonHover(backbutton, mouse_x, mouse_y);
}

static void on_mouse_down() {
	if (backbutton.hovered) {
		game_change_scene(scene_menu_create());
	}
}

static void destroy() {
	al_destroy_bitmap(backbutton.default_img);
	al_destroy_bitmap(backbutton.hovered_img);
}

static void on_key_down(int keycode) {

	switch (keycode) {
	case ALLEGRO_KEY_ENTER:
		break;
	default:
		break;
	}
}

// TODO: Add more event callback functions such as update, ...

// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_rank_create(void) {

	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Menu";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	game_log("rank scene created");
	return scene;
}