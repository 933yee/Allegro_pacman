
#include "mappp.h"
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

extern int level;
static Button backbutton;
static Button n1;
static Button n2;
static Button n3;

static void init() {
	backbutton = button_create(630, 20, 140, 70, "Assets/back.png", "Assets/back2.png");
	n1 = button_create(50, 300, 230, 230, "Assets/map0.5.png", "Assets/map1.png");
	n2 = button_create(300, 300, 230, 230, "Assets/map1.05.png", "Assets/map1.1.png");
	n3 = button_create(550, 300, 230, 230, "Assets/map1.15.png", "Assets/map1.2.png");
}


static void draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	drawButton(backbutton);
	drawButton(n1);
	drawButton(n2);
	drawButton(n3);
	al_draw_text(
		menuFont3,
		al_map_rgb(0, 255, 0),
		110,
		250,
		ALLEGRO_ALIGN_LEFT,
		"EASY"
	);
	al_draw_text(
		menuFont3,
		al_map_rgb(0, 0, 255),
		335,
		250,
		ALLEGRO_ALIGN_LEFT,
		"MEDIUM"
	);
	al_draw_text(
		menuFont3,
		al_map_rgb(255, 0, 0),
		605,
		250,
		ALLEGRO_ALIGN_LEFT,
		"HARD"
	);
	al_draw_text(
		menuFont3,
		al_map_rgb(255, 255, 255),
		135,
		600,
		ALLEGRO_ALIGN_LEFT,
		"DIFFICULTY: "
	);
	if (level == 0) {
		al_draw_text(
			menuFont3,
			al_map_rgb(0, 255, 0),
			450,
			600,
			ALLEGRO_ALIGN_LEFT,
			"EASY"
		);
	}
	else if (level == 1) {
		al_draw_text(
			menuFont3,
			al_map_rgb(0, 0, 255),
			450,
			600,
			ALLEGRO_ALIGN_LEFT,
			"MEDIUM"
		);
	}
	else if (level == 2) {
		al_draw_text(
			menuFont3,
			al_map_rgb(255, 0, 0),
			450,
			600,
			ALLEGRO_ALIGN_LEFT,
			"HARD"
		);
	}
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	backbutton.hovered = buttonHover(backbutton, mouse_x, mouse_y);
	n1.hovered = buttonHover(n1, mouse_x, mouse_y);
	n2.hovered = buttonHover(n2, mouse_x, mouse_y);
	n3.hovered = buttonHover(n3, mouse_x, mouse_y);
}

static void on_mouse_down() {
	if (backbutton.hovered) {
		game_change_scene(scene_menu_create());
	}
	if (n1.hovered) {
		level = 0;
	}
	if (n2.hovered) {
		level = 1;
	}
	if (n3.hovered) {
		level = 2;
	}
}

static void destroy() {
	al_destroy_bitmap(backbutton.default_img);
	al_destroy_bitmap(backbutton.hovered_img);
	al_destroy_bitmap(n1.default_img);
	al_destroy_bitmap(n1.hovered_img);
	al_destroy_bitmap(n2.default_img);
	al_destroy_bitmap(n2.hovered_img);
	al_destroy_bitmap(n3.default_img);
	al_destroy_bitmap(n3.hovered_img);
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
Scene scene_map_create(void) {

	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "MAP";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	game_log("map scene created");
	return scene;
}