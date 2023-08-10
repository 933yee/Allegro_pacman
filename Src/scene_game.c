#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "shared.h"
#include "utility.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "scene_gameover.h"
#include "pacman_obj.h"
#include "ghost.h"
#include "map.h"
#include "scene_menu_object.h"
#include "win.h"


// [HACKATHON 2-0]
// Just modify the GHOST_NUM to 1
#define GHOST_NUM 4 
int ghostnum = GHOST_NUM;
/* global variables*/
extern int level;
extern ALLEGRO_SAMPLE_ID PACMAN_MOVESOUND_ID;
extern const uint32_t GAME_TICK_CD;
extern uint32_t GAME_TICK;
extern ALLEGRO_TIMER* game_tick_timer;
ALLEGRO_SAMPLE_ID GAME_BGM;
extern ALLEGRO_SAMPLE* game_bgm;
int POWER = 0;
char string[100000];
int game_main_Score = 0;
bool game_over = false;
static Button volume;
static Button volume2;
static Button music1;
static Button music2;
static Button menu;
static Button choose;
static Button choose1;
static Button choose2;
static Button choose3;
/* Internal variables*/
ALLEGRO_TIMER* power_up_timer;
static ALLEGRO_TIMER* eat_ghost_timer;
ALLEGRO_SAMPLE_ID EAT_GHOST;
extern ALLEGRO_SAMPLE_ID menuBGM;
extern ALLEGRO_SAMPLE* eat_ghost;
static const int power_up_duration = 10;
static Pacman* pman;
static Map* basic_map;
static Ghost** ghosts;
int win = 0;

bool debug_mode = false;
bool cheat_mode = false;

/* Declare static function prototypes */
static void init(void);
static void step(void);
static void checkItem(void);
static void status_update(void);
static void update(void);
static void draw(void);
static void printinfo(void);
static void destroy(void);
static void on_key_down(int key_code);
static void on_mouse_down(void);
static void render_init_screen(void);
static void draw_hitboxes(void);

static void init(void) {
	eat_ghost_timer = al_create_timer(1.0f / 8);
	volume = button_create(720, 10, 40, 40, "Assets/volume2.png", "Assets/volume3.png");
	volume2 = button_create(720, 10, 40, 40, "Assets/volume.png", "Assets/volume1.png");
	music1 = button_create(660, 10, 40, 40, "Assets/music1.png", "Assets/music2.png");
	music2 = button_create(660, 10, 40, 40, "Assets/music3.png", "Assets/music4.png");
	menu = button_create(30, 700, 150, 70, "Assets/menu3.png", "Assets/menu4.png");
	choose = button_create(700, 700, 50, 50, "Assets/p_choose1.png", "Assets/p_choose2.png");
	choose1 = button_create(640, 700, 50, 50, "Assets/p_choose3.png", "Assets/p_choose4.png");
	choose2 = button_create(580, 700, 50, 50, "Assets/p_choose5.png", "Assets/p_choose6.png");
	choose3 = button_create(520, 700, 50, 50, "Assets/p_choose7.png", "Assets/p_choose8.png");
	game_over = false;
	game_main_Score = 0;
	// create map
	basic_map = create_map(NULL);
	// [TODO]
	// Create map from .txt file and design your own map !!
	// basic_map = create_map("Assets/map_nthu.txt");
	if (!basic_map) {
		game_abort("error on creating map");
	}	
	// create pacman
	pman = pacman_create();
	if (!pman) {
		game_abort("error on creating pacamn\n");
	}
	
	// allocate ghost memory
	// [HACKATHON 2-1]
	// TODO: Allocate dynamic memory for ghosts array.
	ghosts = (Ghost*)malloc(sizeof(Ghost) * GHOST_NUM);
	if(!ghosts){
		game_log("We haven't create any ghosts!\n");
	}
	else {
		// [HACKATHON 2-2]
		// TODO: create a ghost.
		// Try to look the definition of ghost_create and figure out what should be placed here.
		for (int i = 0; i < GHOST_NUM; i++) {
			game_log("creating ghost %d\n", i);
			ghosts[i] = ghost_create(i);
			if (!ghosts[i])
				game_abort("error creating ghost\n");

		}
	}
	GAME_TICK = 0;

	render_init_screen();
	power_up_timer = al_create_timer(1.0f); // 1 tick / sec
	if (!power_up_timer)
		game_abort("Error on create timer\n");
	return ;
}

static void step(void) {
	if (pman->objData.moveCD > 0)
		pman->objData.moveCD -= pman->speed;
	for (int i = 0; i < GHOST_NUM; i++) {
		// important for movement
		if (ghosts[i]->objData.moveCD > 0)
			ghosts[i]->objData.moveCD -= ghosts[i]->speed;
	}
}
static void checkItem(void) {
	int Grid_x = pman->objData.Coord.x, Grid_y = pman->objData.Coord.y;
	if (Grid_y >= basic_map->row_num - 1 || Grid_y <= 0 || Grid_x >= basic_map->col_num - 1 || Grid_x <= 0)
		return;
	// [HACKATHON 1-3]
	// TODO: check which item you are going to eat and use `pacman_eatItem` to deal with it.
	switch (basic_map->map[Grid_y][Grid_x])
	{
	case '.':
		pacman_eatItem(pman, '.');
		game_main_Score += 10;
		win++;
		break;
	case 'P':
		if (POWER == 1) {
			al_stop_timer(power_up_timer);
			al_set_timer_count(power_up_timer, 0);
			stop_bgm(GAME_BGM);
		}
		pacman_eatItem(pman, 'P');
		al_start_timer(power_up_timer);
		POWER = 1;
		if(!cheat_mode)pman->speed = 4;
		stop_bgm(menuBGM);
		GAME_BGM = play_bgm(game_bgm, effect_volume);
		pman->powerUp = true;
		for (int i = 0; i < GHOST_NUM; i++) {
			ghost_toggle_FLEE(ghosts[i], true);
		}
		game_main_Score += 50;
		break;
	default:
		break;
	}
	// [HACKATHON 1-4]
	// erase the item you eat from map
	// be careful no erasing the wall block.
		basic_map->map[Grid_y][Grid_x] = ' ';
}
extern int on2;
static void status_update(void) {
	for (int i = 0; i < GHOST_NUM; i++) {
		if (ghosts[i]->status == GO_IN)
			continue;
		if (cheat_mode && RecAreaOverlap(getDrawArea(pman->objData, GAME_TICK_CD), getDrawArea(ghosts[i]->objData, GAME_TICK_CD))) {
			ghosts[i]->status = FLEE;
			ghost_collided(ghosts[i]);
			game_main_Score += 200;
			if (on2) {
				stop_bgm(EAT_GHOST);
				al_start_timer(eat_ghost_timer);
				EAT_GHOST = play_bgm(eat_ghost, effect_volume);
			}
			game_log("ghost dies!\n");
		}
		else if (ghosts[i]->status == FREEDOM && RecAreaOverlap(getDrawArea(pman->objData, GAME_TICK_CD), getDrawArea(ghosts[i]->objData, GAME_TICK_CD))) {
			game_log("collide with ghost\n");
			pacman_die();
			game_over = true;
			break;
		}
		else if (pman->powerUp && RecAreaOverlap(getDrawArea(pman->objData, GAME_TICK_CD), getDrawArea(ghosts[i]->objData, GAME_TICK_CD))) {
			ghost_collided(ghosts[i]);
			game_main_Score += 200;
				if (on2) {	
					stop_bgm(EAT_GHOST);
					al_start_timer(eat_ghost_timer);			
					EAT_GHOST = play_bgm(eat_ghost, effect_volume);
				}
			game_log("ghost dies!\n");
		}
	}
}

static void update(void) {

	if (game_over) {
		POWER = 0;
		stop_bgm(menuBGM);
		stop_bgm(GAME_BGM);
		/*
			[TODO]
			start pman->death_anim_counter and schedule a game-over event (e.g change scene to menu) after Pacman's death animation finished
			game_change_scene(...);
		*/
		if (win == 382 && level == 0) {
			win = 0;
			game_change_scene(scene_win_create());
			return;
		}
		else if (win == 426 && level == 1) {
			win = 0;
			game_change_scene(scene_win_create());
			return;
		}
		else if (win == 582 && level == 2) {
			win = 0;
			game_change_scene(scene_win_create());
			return;
		}
		win = 0;
		al_start_timer(pman->death_anim_counter);
		if (al_get_timer_count((pman->death_anim_counter))>=132) {
			al_set_timer_count(pman->death_anim_counter, 0);
			game_change_scene(scene_gameover_create());
		}
		return;
	}

	step();
	checkItem();
	status_update();
	pacman_move(pman, basic_map);
	for (int i = 0; i < GHOST_NUM; i++) 
		ghosts[i]->move_script(ghosts[i], basic_map, pman);
}
int on = 1;
int on2 = 1;
static void draw(void) {
	if (win == 382 && level == 0) {
		POWER = 0;
		win = 0;
		game_change_scene(scene_win_create());
		return;
	}
	else if (win == 426 && level == 1) {
		POWER = 0;
		win = 0;
		game_change_scene(scene_win_create());
		return;
	}
	else if (win == 582 && level == 2) {
		POWER = 0;
		win = 0;
		game_change_scene(scene_win_create());
		return;
	}
	if(al_get_timer_count(power_up_timer)>10){
		if(!cheat_mode) pman->speed = 2;
		for (int i = 0; i < GHOST_NUM; i++) {
			ghost_toggle_FLEE(ghosts[i], false);
		}
		pman->powerUp = false;
		POWER = 0;
		al_stop_timer(power_up_timer);
		al_set_timer_count(power_up_timer,0);
		if (on) {
			stop_bgm(GAME_BGM);
			menuBGM = play_bgm(themeMusic, music_volume);
		}
	}
	if (al_get_timer_count((eat_ghost_timer)) > 2) {
		stop_bgm(EAT_GHOST);
		al_stop_timer(eat_ghost_timer);
		al_set_timer_count(eat_ghost_timer, 0);
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));
	if(on) drawButton(volume);
	else drawButton(volume2);
	if (on2) drawButton(music1);
	else drawButton(music2);
	drawButton(menu);
	drawButton(choose);
	drawButton(choose1);
	drawButton(choose2);
	drawButton(choose3);
	//	[TODO]
	//	Draw scoreboard, something your may need is sprinf();
	sprintf(string, "Score: %d", game_main_Score);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 200, 50),
		35,
		20,
		ALLEGRO_ALIGN_LEFT,
		string
	);
	if (cheat_mode) {
		
		al_draw_text(
			menuFont4,
			al_map_rgb(255, 0, 0),
			205,
			725,
			ALLEGRO_ALIGN_LEFT,
			"CHEATING!!"
		);
	}
	if (POWER) {
		char string2[15];
		sprintf(string2, "%d", 10 - al_get_timer_count(power_up_timer));
		if ((10 - al_get_timer_count(power_up_timer))%2==0) {
			al_draw_text(
				menuFont3,
				al_map_rgb(255, 255, 255),
				285,
				15,
				ALLEGRO_ALIGN_LEFT,
				"POWER!! "
			);
		}
		else {
			al_draw_text(
				menuFont3,
				al_map_rgb(255, 255, 255),
				475,
				15,
				ALLEGRO_ALIGN_LEFT,
				"POWER!! "
			);
		}
		al_draw_text(
			menuFont3,
			al_map_rgb(255, 0, 0),
			440,
			15,
			ALLEGRO_ALIGN_LEFT,
			string2
		);
	}
	draw_map(basic_map);

	pacman_draw(pman);
	if (game_over)
		return;
	// no drawing below when game over
	for (int i = 0; i < GHOST_NUM; i++)
		ghost_draw(ghosts[i]);
	
	//debugging mode
	if (debug_mode) {
		draw_hitboxes();
	}

}

static void draw_hitboxes(void) {
	RecArea pmanHB = getDrawArea(pman->objData, GAME_TICK_CD);
	al_draw_rectangle(
		pmanHB.x, pmanHB.y,
		pmanHB.x + pmanHB.w, pmanHB.y + pmanHB.h,
		al_map_rgb_f(1.0, 0.0, 0.0), 2
	);

	for (int i = 0; i < GHOST_NUM; i++) {
		RecArea ghostHB = getDrawArea(ghosts[i]->objData, GAME_TICK_CD);
		al_draw_rectangle(
			ghostHB.x, ghostHB.y,
			ghostHB.x + ghostHB.w, ghostHB.y + ghostHB.h,
			al_map_rgb_f(1.0, 0.0, 0.0), 2
		);
	}

}

static void printinfo(void) {
	game_log("pacman:\n");
	game_log("coord: %d, %d\n", pman->objData.Coord.x, pman->objData.Coord.y);
	game_log("PreMove: %d\n", pman->objData.preMove);
	game_log("NextTryMove: %d\n", pman->objData.nextTryMove);
	game_log("Speed: %f\n", pman->speed);
}


static void destroy(void) {
	al_destroy_bitmap(volume.default_img);
	al_destroy_bitmap(volume.hovered_img);
	al_destroy_bitmap(volume2.default_img);
	al_destroy_bitmap(volume2.hovered_img);
	al_destroy_bitmap(music1.default_img);
	al_destroy_bitmap(music1.hovered_img);
	al_destroy_bitmap(music2.default_img);
	al_destroy_bitmap(music2.hovered_img);
	al_destroy_bitmap(menu.default_img);
	al_destroy_bitmap(menu.hovered_img);
	al_destroy_bitmap(choose.default_img);
	al_destroy_bitmap(choose.hovered_img);
	al_destroy_bitmap(choose1.default_img);
	al_destroy_bitmap(choose1.hovered_img);
	al_destroy_bitmap(choose2.default_img);
	al_destroy_bitmap(choose2.hovered_img);
	al_destroy_bitmap(choose3.default_img);
	al_destroy_bitmap(choose3.hovered_img);
	free(pman);
	free(ghosts);
	free(basic_map);
	al_destroy_timer(eat_ghost_timer);
	al_destroy_timer(power_up_timer);
	/*
		[TODO]
		free map array, Pacman and ghosts
	*/
}
extern int level;
static void on_key_down(int key_code) {
	switch (key_code)
	{
		// [HACKATHON 1-1]	
		// TODO: Use allegro pre-defined enum ALLEGRO_KEY_<KEYNAME> to controll pacman movement
		// we provided you a function `pacman_NextMove` to set the pacman's next move direction.
	case ALLEGRO_KEY_W:
		pacman_NextMove(pman, UP);
		break;
	case ALLEGRO_KEY_A:
		pacman_NextMove(pman, LEFT);
		break;
	case ALLEGRO_KEY_S:
		pacman_NextMove(pman, DOWN);
		break;
	case ALLEGRO_KEY_D:
		pacman_NextMove(pman, RIGHT);
		break;
	case ALLEGRO_KEY_C:
		cheat_mode = !cheat_mode;
		if (cheat_mode) {	
			pman->speed = 5;
			printf("cheat mode on\n");
		}
		else {
			pman->speed = 2;
			printf("cheat mode off\n");
		}
		break;
	case ALLEGRO_KEY_G:
		debug_mode = !debug_mode;
		break;
	case ALLEGRO_KEY_Z:
		pacman_die();
		game_over = true;
		break;
	case ALLEGRO_KEY_X:
		stop_bgm(menuBGM);
		stop_bgm(GAME_BGM);
		stop_bgm(PACMAN_MOVESOUND_ID);
		if (level == 0) win = 382;
		if (level == 1) win = 426;
		if (level == 2) win = 582;
		game_over = true;
		break;
	default:
		break;
	}

}
extern int once;
static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	volume.hovered = buttonHover(volume, mouse_x, mouse_y);
	volume2.hovered = buttonHover(volume2, mouse_x, mouse_y);
	music1.hovered = buttonHover(music1, mouse_x, mouse_y);
	music2.hovered = buttonHover(music2, mouse_x, mouse_y);
	menu.hovered = buttonHover(menu, mouse_x, mouse_y);
	choose.hovered = buttonHover(choose, mouse_x, mouse_y);
	choose1.hovered = buttonHover(choose1, mouse_x, mouse_y);
	choose2.hovered = buttonHover(choose2, mouse_x, mouse_y);
	choose3.hovered = buttonHover(choose3, mouse_x, mouse_y);

}
static void on_mouse_down() {
	if (volume.hovered) {
		if (on == 1) {
			on = 0;
			if (POWER)stop_bgm(GAME_BGM);
			else stop_bgm(menuBGM);
		}
		else {
			on = 1;
			if(POWER) GAME_BGM = play_bgm(game_bgm, music_volume);
			else menuBGM = play_bgm(themeMusic, music_volume);
		}
	}
	if (music1.hovered) {
		if (on2 == 1) {
			on2 = 0;
			stop_bgm(PACMAN_MOVESOUND_ID);
		}
		else on2 = 1;
	}
	if (menu.hovered) {
		once = 0;
		stop_bgm(PACMAN_MOVESOUND_ID);
		stop_bgm(GAME_BGM);
		stop_bgm(menuBGM);
		game_change_scene(scene_menu_create());
	}
	if (choose.hovered) {
		pman->move_sprite = load_bitmap("Assets/pacman_move.png");
		pman->die_sprite = load_bitmap("Assets/pacman_die.png");
	}
	if (choose1.hovered) {
		pman->move_sprite = load_bitmap("Assets/pacman_move2.png");
		pman->die_sprite = load_bitmap("Assets/pacman_die2.png");
	}
	if (choose2.hovered) {
		pman->move_sprite = load_bitmap("Assets/pacman_move3.png");
		pman->die_sprite = load_bitmap("Assets/pacman_die3.png");
	}
	if (choose3.hovered) {
		pman->move_sprite = load_bitmap("Assets/pacman_move4.png");
		pman->die_sprite = load_bitmap("Assets/pacman_die4.png");
	}
}

static void render_init_screen(void) {
	al_clear_to_color(al_map_rgb(0, 0, 0));

	draw_map(basic_map);
	pacman_draw(pman);
	for (int i = 0; i < GHOST_NUM; i++) {
		ghost_draw(ghosts[i]);
	}

	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 0),
		400, 400,
		ALLEGRO_ALIGN_CENTER,
		"READY!"
	);

	al_flip_display();
	al_rest(2.0);

}
// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_main_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Start";
	scene.initialize = &init;
	scene.update = &update;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Start scene created");
	return scene;
}
