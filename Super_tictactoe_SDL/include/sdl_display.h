#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define sign_sprites 4
#define sign_sprite_res 128
#define mode_count 2
#define mode_sprite_res 256
#define max_cells 81

static const char *path_single_arrow = "../resources/single_arrow.png";
static const char *path_double_arrow = "../resources/double_arrow.png";
static const char *path_x = "../resources/sign_x.png";
static const char *path_o = "../resources/sign_o.png";
static const char *path_modes = "../resources/modes.png";
static const char *path_field_background = "../resources/field_background.png";
static const char *path_logo = "../resources/logo.png";
static const char *path_font = "../resources/font.ttf";

static const int max_id = 100;
static const int window_width = 1280;
static const int window_height = 720;
static const int font_size = 64;

static const int menu_buttons = 10;
static const int board_size = 500;

static int board[9][9];

enum Menu_Buttons
{
	mode,
	play,
	add_id,
	sub_id,
	add_mult_id,
	sub_mult_id,
	next_x,
	prev_x,
	next_o,
	prev_o
};

typedef struct cell
{
	SDL_Rect rect;
} Cell;

typedef struct object
{
	SDL_Rect background_rect;
	SDL_Rect content_rect;
	SDL_Texture *background_txt;
	SDL_Texture *content_txt;
} Object;

typedef struct button
{
	SDL_RendererFlip flip;
	SDL_Rect background_rect;
	SDL_Rect content_rect;
	SDL_Texture *background_txt;
	SDL_Texture *content_txt;
} Button;

typedef struct pallete
{
	TTF_Font *font;
	int sprite_x;
	int sprite_o;
	SDL_Color background;
	SDL_Color board_lines;
	SDL_Color spot_highlight;
	SDL_Color text;
} Pallete;

typedef struct textures
{
	SDL_Texture *single_arrow;
	SDL_Texture *double_arrow;
	SDL_Texture *sign_x;
	SDL_Texture *sign_o;
	SDL_Texture *modes;
	SDL_Texture *field_background;
	SDL_Texture *logo;
} Textures;

typedef struct menu
{
	Object *logo;
	Object *game_id;
	Object *sign_x;
	Object *sign_o;
	Button **buttons;
} Menu;

typedef struct playfield
{
	Object *background;
	Object *timer;
	Cell **cells;
	Button *put_sign;
	Button *forfeit;
} Playfield;

typedef struct sdl_data
{
	bool super_mode;
	bool in_game;
	int game_id;
	int time_left;
	int select_x;
	int select_y;
	SDL_Window *window;
	SDL_Renderer *renderer;
	Textures *textures;
	Menu *menu;
	void (**menu_functions)(struct sdl_data*);
	void (*select_cell)(struct sdl_data*, int x, int y);
	void (*put_sign)(struct sdl_data*);
	void (*forfeit)(struct sdl_data*);
	Playfield *playfield;
	Pallete *pallete;
} Sdl_Data;

bool init_sdl(Sdl_Data **sdl_data_ptr);
bool load_media(Sdl_Data *sdl_data);
void frame_events(Sdl_Data *sdl_data);
void close_sdl(Sdl_Data *sdl_data);