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
#include "rank.h"
#include "mappp.h"

int key = 0;
/* Internal Variables*/
static ALLEGRO_BITMAP* gameTitle = NULL;
ALLEGRO_SAMPLE_ID menuBGM;
static int gameTitleW ;
static int gameTitleH ;

// [HACKATHON 3]
// TARGET : use a clickable button to enter setting scene.
// For `Button` struct(object) is defined in `scene_menu_object.h` and `scene_menu_object.c`
// STRONGLY recommend you trace both of them first. 

//	[HACKATHON 3-1]
//	TODO: Declare variable for button
//	Uncomment and fill the code below
// static ... btnSettings;
static Button btnSettings;
static Button question_mark;
static Button square;
static Button rank;
static Button map;
int once = 0;

static void init() {

	// [HACKATHON 3-2]
	// TODO: Create button to settings
	//	Uncomment and fill the code below
	//btnSettings = button_create(730, 20, 50, 50, "...", "...");
	btnSettings = button_create(710, 20, 70, 70, "Assets/settings.png", "Assets/settings2.png");
	rank = button_create(610, 20, 70, 70, "Assets/rank.png", "Assets/rank2.png");
	map = button_create(510, 20, 70, 70, "Assets/map.png", "Assets/map2.png");
	question_mark = button_create(720, 720, 60, 60, "Assets/question_mark.png", "Assets/question_mark2.png");
	square = button_create(600, 480, 200, 250, "Assets/square.png", "Assets/square.png");
	gameTitle = load_bitmap("Assets/title.png");
	gameTitleW = al_get_bitmap_width(gameTitle);
	gameTitleH = al_get_bitmap_height(gameTitle);
	if (once == 0) {
		menuBGM = play_bgm(themeMusic, music_volume);
		once++;
	}

}


static void draw() {
	
	al_clear_to_color(al_map_rgb(0, 0, 0));
	const float scale = 0.7;
	const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * gameTitleW;
	const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * gameTitleH;

	//draw title image
	al_draw_scaled_bitmap(
		gameTitle,
		0, 0,
		gameTitleW, gameTitleH,
		offset_w, offset_h,
		gameTitleW * scale, gameTitleH * scale,
		0
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2,
		SCREEN_H - 150,
		ALLEGRO_ALIGN_CENTER,
		"PRESS \"ENTER\""
	);

		// [HACKATHON 3-3]
		// TODO: Draw button
		// Uncomment and fill the code below
		// drawButton(...);
	if (key) drawButton(square);
	drawButton(btnSettings);
	drawButton(question_mark);	
	drawButton(rank);	
	drawButton(map);	
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	//	[HACKATHON 3-7]
	//	TODO: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
	//	Uncomment and fill the code below
	btnSettings.hovered = buttonHover(btnSettings, mouse_x, mouse_y);
	question_mark.hovered = buttonHover(question_mark, mouse_x, mouse_y);
	rank.hovered = buttonHover(rank, mouse_x, mouse_y);
	map.hovered = buttonHover(map, mouse_x, mouse_y);
	if (buttonHover(question_mark, mouse_x, mouse_y)) key = 1;
	else key = 0;
}


//	[HACKATHON 3-8]
//	TODO: When btnSettings clicked, switch to settings scene
//  `game_change_scene` is defined in `game.h`.
//  You can check line 121 `scene_menu.c` to see how to use this function.
// 	Utilize the member defined in struct `Button`.
//  The logic here is 
//  `if clicked the mouse` && `mouse position is in the area of button`
// 	      `Enter the setting scene`
//	Uncomment and fill the code below

static void on_mouse_down() {
	if (btnSettings.hovered) {
		game_change_scene(scene_settings_create());
	}	
	if (rank.hovered) {
		game_change_scene(scene_rank_create());
	}
	if (map.hovered) {
		game_change_scene(scene_map_create());
	}
}

static void destroy() {
	al_destroy_bitmap(gameTitle);
	//	[HACKATHON 3-10]
	//	TODO: Destroy button images
	//	Uncomment and fill the code below
	al_destroy_bitmap(btnSettings.default_img);
	al_destroy_bitmap(btnSettings.hovered_img);
	al_destroy_bitmap(question_mark.default_img);
	al_destroy_bitmap(question_mark.hovered_img);
	al_destroy_bitmap(square.default_img);
	al_destroy_bitmap(square.hovered_img);
	al_destroy_bitmap(rank.default_img);
	al_destroy_bitmap(rank.hovered_img);
	al_destroy_bitmap(map.default_img);
	al_destroy_bitmap(map.hovered_img);
}

static void on_key_down(int keycode) {
	switch (keycode) {
		case ALLEGRO_KEY_ENTER:
			game_change_scene(scene_main_create());
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
Scene scene_menu_create(void) {

	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Menu";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	// [HACKATHON 3-9]
	// TODO: Register on_mouse_down.
	// Uncomment the code below.
	scene.on_mouse_down = &on_mouse_down;
	// -------------------------------------



	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Menu scene created");
	return scene;
}