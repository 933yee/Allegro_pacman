// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.

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
// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
static Button backbutton;
static Button setting;
static Button volume1, volume2, volume3, volume4, volume5, volume6, volume7, volume8, volume9, volume10;
static Button volume11, volume12, volume13, volume14, volume15, volume16, volume17, volume18, volume19, volume20,volume21;
static Button volumeX1, volumeX2, volumeX3, volumeX4, volumeX5, volumeX6, volumeX7, volumeX8, volumeX9, volumeX10;
static Button volumeX11, volumeX12, volumeX13, volumeX14, volumeX15, volumeX16, volumeX17, volumeX18, volumeX19, volumeX20,volumeX21;
extern ALLEGRO_SAMPLE_ID menuBGM;
extern ALLEGRO_SAMPLE* point_sound;
static ALLEGRO_SAMPLE_ID POINT;
static Button sound;
static Button effect;
static Button white;
static Button white2;
static Button white3;
static Button white4;
static Button black;
extern float music_volume;
extern float effect_volume;
int tmpvol=50;
int tmpvol2=50;
int keysound = 0;
int keyeffect = 0;
static void init() {
	black = button_create(0, 0, 800, 800, "Assets/black.png", "Assets/black.png");
	backbutton = button_create(630, 20, 140, 70, "Assets/back.png", "Assets/back2.png");
	setting = button_create(20, 20, 200, 70, "Assets/setting.png", "Assets/setting.png");
	volume1 = button_create(150, 250, 500, 130, "Assets/setting/0%.png", "Assets/setting/0%.png");
	volume2 = button_create(150, 250, 500, 130, "Assets/setting/5%.png", "Assets/setting/5%.png");
	volume3 = button_create(150, 250, 500, 130, "Assets/setting/10%.png", "Assets/setting/10%.png");
	volume4 = button_create(150, 250, 500, 130, "Assets/setting/15%.png", "Assets/setting/15%.png");
	volume5 = button_create(150, 250, 500, 130, "Assets/setting/20%.png", "Assets/setting/20%.png");
	volume6 = button_create(150, 250, 500, 130, "Assets/setting/25%.png", "Assets/setting/25%.png");
	volume7 = button_create(150, 250, 500, 130, "Assets/setting/30%.png", "Assets/setting/30%.png");
	volume8 = button_create(150, 250, 500, 130, "Assets/setting/35%.png", "Assets/setting/35%.png");
	volume9 = button_create(150, 250, 500, 130, "Assets/setting/40%.png", "Assets/setting/40%.png");
	volume10 = button_create(150, 250, 500, 130, "Assets/setting/45%.png", "Assets/setting/45%.png");
	volume11 = button_create(150, 250, 500, 130, "Assets/setting/50%.png", "Assets/setting/50%.png");
	volume12 = button_create(150, 250, 500, 130, "Assets/setting/55%.png", "Assets/setting/55%.png");
	volume13 = button_create(150, 250, 500, 130, "Assets/setting/60%.png", "Assets/setting/60%.png");
	volume14 = button_create(150, 250, 500, 130, "Assets/setting/65%.png", "Assets/setting/65%.png");
	volume15 = button_create(150, 250, 500, 130, "Assets/setting/70%.png", "Assets/setting/70%.png");
	volume16 = button_create(150, 250, 500, 130, "Assets/setting/75%.png", "Assets/setting/75%.png");
	volume17 = button_create(150, 250, 500, 130, "Assets/setting/80%.png", "Assets/setting/80%.png");
	volume18 = button_create(150, 250, 500, 130, "Assets/setting/85%.png", "Assets/setting/85%.png");
	volume19 = button_create(150, 250, 500, 130, "Assets/setting/90%.png", "Assets/setting/90%.png");
	volume20 = button_create(150, 250, 500, 130, "Assets/setting/95%.png", "Assets/setting/95%.png");
	volume21 = button_create(150, 250, 500, 130, "Assets/setting/100%.png", "Assets/setting/100%.png");
	volumeX1 = button_create(150, 445, 500, 130, "Assets/setting/0%.png", "Assets/setting/0%.png");
	volumeX2 = button_create(150, 445, 500, 130, "Assets/setting/5%.png", "Assets/setting/5%.png");
	volumeX3 = button_create(150, 445, 500, 130, "Assets/setting/10%.png", "Assets/setting/10%.png");
	volumeX4 = button_create(150, 445, 500, 130, "Assets/setting/15%.png", "Assets/setting/15%.png");
	volumeX5 = button_create(150, 445, 500, 130, "Assets/setting/20%.png", "Assets/setting/20%.png");
	volumeX6 = button_create(150, 445, 500, 130, "Assets/setting/25%.png", "Assets/setting/25%.png");
	volumeX7 = button_create(150, 445, 500, 130, "Assets/setting/30%.png", "Assets/setting/30%.png");
	volumeX8 = button_create(150, 445, 500, 130, "Assets/setting/35%.png", "Assets/setting/35%.png");
	volumeX9 = button_create(150, 445, 500, 130, "Assets/setting/40%.png", "Assets/setting/40%.png");
	volumeX10 = button_create(150, 445, 500, 130, "Assets/setting/45%.png", "Assets/setting/45%.png");
	volumeX11 = button_create(150, 445, 500, 130, "Assets/setting/50%.png", "Assets/setting/50%.png");
	volumeX12 = button_create(150, 445, 500, 130, "Assets/setting/55%.png", "Assets/setting/55%.png");
	volumeX13 = button_create(150, 445, 500, 130, "Assets/setting/60%.png", "Assets/setting/60%.png");
	volumeX14 = button_create(150, 445, 500, 130, "Assets/setting/65%.png", "Assets/setting/65%.png");
	volumeX15 = button_create(150, 445, 500, 130, "Assets/setting/70%.png", "Assets/setting/70%.png");
	volumeX16 = button_create(150, 445, 500, 130, "Assets/setting/75%.png", "Assets/setting/75%.png");
	volumeX17 = button_create(150, 445, 500, 130, "Assets/setting/80%.png", "Assets/setting/80%.png");
	volumeX18 = button_create(150, 445, 500, 130, "Assets/setting/85%.png", "Assets/setting/85%.png");
	volumeX19 = button_create(150, 445, 500, 130, "Assets/setting/90%.png", "Assets/setting/90%.png");
	volumeX20 = button_create(150, 445, 500, 130, "Assets/setting/95%.png", "Assets/setting/95%.png");
	volumeX21 = button_create(150, 445, 500, 130, "Assets/setting/100%.png", "Assets/setting/100%.png");	
	sound = button_create(30, 305, 115, 50, "Assets/sound.png", "Assets/sound.png");
	effect = button_create(30, 500, 115, 50, "Assets/effect.png", "Assets/effect.png");
	white = button_create(15, 230, 750, 190, "Assets/white.png", "Assets/white2.png");
	white2 = button_create(15, 425, 750, 190, "Assets/white.png", "Assets/white2.png");
	white3 = button_create(15, 230, 750, 190, "Assets/white3.png", "Assets/white3.png");
	white4 = button_create(15, 425, 750, 190, "Assets/white3.png", "Assets/white3.png");
}
static void draw(void ){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	drawButton(black);
	if (keysound) {
		drawButton(white3);
	}
	else {
		drawButton(white);
	}
	if (keyeffect) {
		drawButton(white4);
	}
	else {
		drawButton(white2);
	}
	drawButton(backbutton);
	drawButton(setting);
	tmpvol = round(music_volume * 100.0);
	tmpvol2 = round(effect_volume * 100.0);
	switch (tmpvol) {
	case 0:
		drawButton(volume1);
		break;
	case 5:
		drawButton(volume2);
		break;
	case 10:
		drawButton(volume3);
		break;
	case 15:
		drawButton(volume4);
		break;
	case 20:
		drawButton(volume5);
		break;
	case 25:
		drawButton(volume6);
		break;
	case 30:
		drawButton(volume7);
		break;
	case 35:
		drawButton(volume8);
		break;
	case 40:
		drawButton(volume9);
		break;
	case 45:
		drawButton(volume10);
		break;
	case 50:
		drawButton(volume11);
		break;
	case 55:
		drawButton(volume12);
		break;
	case 60:
		drawButton(volume13);
		break;
	case 65:
		drawButton(volume14);
		break;
	case 70:
		drawButton(volume15);
		break;
	case 75:
		drawButton(volume16);
		break;
	case 80:
		drawButton(volume17);
		break;
	case 85:
		drawButton(volume18);
		break;
	case 90:
		drawButton(volume19);
		break;
	case 95:
		drawButton(volume20);
		break;
	case 100:
		drawButton(volume21);
		break;
	}
	switch (tmpvol2) {
	case 0:
		drawButton(volumeX1);
		break;
	case 5:
		drawButton(volumeX2);
		break;
	case 10:
		drawButton(volumeX3);
		break;
	case 15:
		drawButton(volumeX4);
		break;
	case 20:
		drawButton(volumeX5);
		break;
	case 25:
		drawButton(volumeX6);
		break;
	case 30:
		drawButton(volumeX7);
		break;
	case 35:
		drawButton(volumeX8);
		break;
	case 40:
		drawButton(volumeX9);
		break;
	case 45:
		drawButton(volumeX10);
		break;
	case 50:
		drawButton(volumeX11);
		break;
	case 55:
		drawButton(volumeX12);
		break;
	case 60:
		drawButton(volumeX13);
		break;
	case 65:
		drawButton(volumeX14);
		break;
	case 70:
		drawButton(volumeX15);
		break;
	case 75:
		drawButton(volumeX16);
		break;
	case 80:
		drawButton(volumeX17);
		break;
	case 85:
		drawButton(volumeX18);
		break;
	case 90:
		drawButton(volumeX19);
		break;
	case 95:
		drawButton(volumeX20);
		break;
	case 100:
		drawButton(volumeX21);
		break;
	}
	drawButton(sound);
	drawButton(effect);
	char tmp[10];
	char tmp2[10];
	sprintf(tmp, "%d%%", tmpvol);
	sprintf(tmp2, "%d%%", tmpvol2);
	al_draw_text(
		menuFont2,
		al_map_rgb(255, 255, 255),
		645,
		300,
		ALLEGRO_ALIGN_LEFT,
		tmp
	);
	al_draw_text(
		menuFont2,
		al_map_rgb(255, 255, 255),
		645,
		495,
		ALLEGRO_ALIGN_LEFT,
		tmp2
	);
	
}
static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	backbutton.hovered = buttonHover(backbutton, mouse_x, mouse_y);
	white.hovered = buttonHover(white, mouse_x, mouse_y);
	white2.hovered = buttonHover(white2, mouse_x, mouse_y);
	black.hovered = buttonHover(black, mouse_x, mouse_y);
}
static void on_mouse_down() {
	if (backbutton.hovered) {
		keysound = 0;
		game_change_scene(scene_menu_create());
	}
	if (keysound==0 && white.hovered) {
		game_log("key sound clicked (on)");
		keysound = 1;
		if (keyeffect == 1) {
			menuBGM = play_bgm(themeMusic, music_volume);
			keyeffect = 0;
		}
	}
	else if(keysound == 1 && white.hovered) {
		keysound = 0;
		game_log("key sound clicked (off)");
	}
	else if (keyeffect == 0 && white2.hovered) {
		stop_bgm(menuBGM);
		keyeffect = 1;
		keysound = 0;
		game_log("key effect clicked (on)");
	}
	else if (keyeffect == 1 && white2.hovered) {
		keyeffect = 0;
		menuBGM = play_bgm(themeMusic, music_volume);
		game_log("key effect clicked (off)");
	}
	else if (black.hovered ) {
		game_log("keysound and keyeffect(off)");
		keysound = 0;
		if (keyeffect == 1) {
			menuBGM = play_bgm(themeMusic, music_volume);
			keyeffect = 0;
		}
	}
}
static void destroy() {
	al_destroy_bitmap(backbutton.default_img);
	al_destroy_bitmap(backbutton.hovered_img);
	al_destroy_bitmap(white.default_img);
	al_destroy_bitmap(white.hovered_img);
	al_destroy_bitmap(white2.default_img);
	al_destroy_bitmap(white2.hovered_img);
	al_destroy_bitmap(white3.default_img);
	al_destroy_bitmap(white3.hovered_img);
	al_destroy_bitmap(white4.default_img);
	al_destroy_bitmap(white4.hovered_img);
	al_destroy_bitmap(black.hovered_img);
	al_destroy_bitmap(black.default_img);
	al_destroy_bitmap(setting.default_img);
	al_destroy_bitmap(setting.hovered_img);
	al_destroy_bitmap(volume1.default_img);
	al_destroy_bitmap(volume1.hovered_img);
	al_destroy_bitmap(volume2.default_img);
	al_destroy_bitmap(volume2.hovered_img);
	al_destroy_bitmap(volume3.default_img);
	al_destroy_bitmap(volume3.hovered_img);
	al_destroy_bitmap(volume4.default_img);
	al_destroy_bitmap(volume4.hovered_img);
	al_destroy_bitmap(volume5.default_img);
	al_destroy_bitmap(volume5.hovered_img);
	al_destroy_bitmap(volume6.default_img);
	al_destroy_bitmap(volume6.hovered_img);
	al_destroy_bitmap(volume7.default_img);
	al_destroy_bitmap(volume7.hovered_img);
	al_destroy_bitmap(volume8.default_img);
	al_destroy_bitmap(volume8.hovered_img);
	al_destroy_bitmap(volume9.default_img);
	al_destroy_bitmap(volume9.hovered_img);
	al_destroy_bitmap(volume10.default_img);
	al_destroy_bitmap(volume10.hovered_img);
	al_destroy_bitmap(volume11.default_img);
	al_destroy_bitmap(volume11.hovered_img);
	al_destroy_bitmap(volume12.default_img);
	al_destroy_bitmap(volume12.hovered_img);
	al_destroy_bitmap(volume13.default_img);
	al_destroy_bitmap(volume13.hovered_img);
	al_destroy_bitmap(volume14.default_img);
	al_destroy_bitmap(volume14.hovered_img);
	al_destroy_bitmap(volume15.default_img);
	al_destroy_bitmap(volume15.hovered_img);
	al_destroy_bitmap(volume16.default_img);
	al_destroy_bitmap(volume16.hovered_img);
	al_destroy_bitmap(volume17.default_img);
	al_destroy_bitmap(volume17.hovered_img);
	al_destroy_bitmap(volume18.default_img);
	al_destroy_bitmap(volume18.hovered_img);
	al_destroy_bitmap(volume19.default_img);
	al_destroy_bitmap(volume19.hovered_img);
	al_destroy_bitmap(volume20.default_img);
	al_destroy_bitmap(volume20.hovered_img);
	al_destroy_bitmap(volume21.default_img);
	al_destroy_bitmap(volume21.hovered_img);
	al_destroy_bitmap(volumeX1.default_img);
	al_destroy_bitmap(volumeX1.hovered_img);
	al_destroy_bitmap(volumeX2.default_img);
	al_destroy_bitmap(volumeX2.hovered_img);
	al_destroy_bitmap(volumeX3.default_img);
	al_destroy_bitmap(volumeX3.hovered_img);
	al_destroy_bitmap(volumeX4.default_img);
	al_destroy_bitmap(volumeX4.hovered_img);
	al_destroy_bitmap(volumeX5.default_img);
	al_destroy_bitmap(volumeX5.hovered_img);
	al_destroy_bitmap(volumeX6.default_img);
	al_destroy_bitmap(volumeX6.hovered_img);
	al_destroy_bitmap(volumeX7.default_img);
	al_destroy_bitmap(volumeX7.hovered_img);
	al_destroy_bitmap(volumeX8.default_img);
	al_destroy_bitmap(volumeX8.hovered_img);
	al_destroy_bitmap(volumeX9.default_img);
	al_destroy_bitmap(volumeX9.hovered_img);
	al_destroy_bitmap(volumeX10.default_img);
	al_destroy_bitmap(volumeX10.hovered_img);
	al_destroy_bitmap(volumeX11.default_img);
	al_destroy_bitmap(volumeX11.hovered_img);
	al_destroy_bitmap(volumeX12.default_img);
	al_destroy_bitmap(volumeX12.hovered_img);
	al_destroy_bitmap(volumeX13.default_img);
	al_destroy_bitmap(volumeX13.hovered_img);
	al_destroy_bitmap(volumeX14.default_img);
	al_destroy_bitmap(volumeX14.hovered_img);
	al_destroy_bitmap(volumeX15.default_img);
	al_destroy_bitmap(volumeX15.hovered_img);
	al_destroy_bitmap(volumeX16.default_img);
	al_destroy_bitmap(volumeX16.hovered_img);
	al_destroy_bitmap(volumeX17.default_img);
	al_destroy_bitmap(volumeX17.hovered_img);
	al_destroy_bitmap(volumeX18.default_img);
	al_destroy_bitmap(volumeX18.hovered_img);
	al_destroy_bitmap(volumeX19.default_img);
	al_destroy_bitmap(volumeX19.hovered_img);
	al_destroy_bitmap(volumeX20.default_img);
	al_destroy_bitmap(volumeX20.hovered_img);
	al_destroy_bitmap(volumeX21.default_img);
	al_destroy_bitmap(volumeX21.hovered_img);
	al_destroy_bitmap(sound.default_img);
	al_destroy_bitmap(sound.hovered_img);
	al_destroy_bitmap(effect.default_img);
	al_destroy_bitmap(effect.hovered_img);
}
static void on_key_down(int keycode) {

	if(keysound) {
		switch (keycode) {
		case ALLEGRO_KEY_D:
			if (music_volume >= 1.0) return;
			stop_bgm(menuBGM);
			menuBGM = play_bgm(themeMusic, music_volume);
			music_volume += 0.05;
			printf("sound volume = %f\n", music_volume);
			break;
		case ALLEGRO_KEY_A:
			if (music_volume <= 0.0) return;
			stop_bgm(menuBGM);
			music_volume -= 0.05;
			menuBGM = play_bgm(themeMusic, music_volume);
			printf("sound volume = %f\n", music_volume);
			break;
		default:
			break;
		}
	}
	else if (keyeffect) {
		switch (keycode) {
			case ALLEGRO_KEY_D:
				if (effect_volume >= 1.0) return;
				stop_bgm(POINT);
				effect_volume += 0.05;
				POINT = play_audio(point_sound, effect_volume);
				printf("effect volume = %f\n", effect_volume);
				break;
			case ALLEGRO_KEY_A:
				if (effect_volume <= 0.0) return;
				stop_bgm(POINT);
				effect_volume -= 0.05;
				POINT = play_audio(point_sound, effect_volume);
				printf("effect volume = %f\n", effect_volume);
				break;
			default:
				break;
			}
	}
}

// The only function that is shared across files.
Scene scene_settings_create(void) {
	
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	
	return scene;
}
