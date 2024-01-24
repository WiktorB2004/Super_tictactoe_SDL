/**
 * @file game.h
 * @brief Header file containing declarations for a game implementation.
 */

#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "gameplay.h"

typedef struct Game Game;

/**
 * @defgroup Constants Constants
 * @{
 */

/** @brief Number of sign sprites. */
static const int sign_sprites = 4;

/** @brief Size of sign sprite. */
static const int sign_sprite_res = 128;

/** @brief Number of modes in the game. */
static const int mode_count = 2;

/** @brief Size of mode sprite. */
static const int mode_sprite_res = 256;

/** @brief Maximum number of cells in the game. */
static const int max_super_cells = 81;
static const int max_normal_cells = 9;

/** @} */

/**
 * @defgroup Paths Paths to Resources
 * @{
 */

/** @brief Path to the single arrow image resource. */
static const char *path_single_arrow = "resources/single_arrow.png";

/** @brief Path to the double arrow image resource. */
static const char *path_double_arrow = "./resources/double_arrow.png";

/** @brief Path to the X sign image resource. */
static const char *path_x = "resources/sign_x.png";

/** @brief Path to the O sign image resource. */
static const char *path_o = "resources/sign_o.png";

/** @brief Path to the modes image resource. */
static const char *path_modes = "resources/modes.png";

/** @brief Path to the field background image resource. */
static const char *path_field_background = "resources/field_background.png";

/** @brief Path to the logo image resource. */
static const char *path_logo = "resources/logo.png";

/** @brief Path to the font resource. */
static const char *path_font = "resources/font.ttf";

/** @} */

/**
 * @defgroup Limits Game Limits
 * @{
 */

/** @brief Maximum difficulty level for the bot. */
static const int max_diff = 3;

/** @brief Maximum game ID. */
static const int max_id = 100;

/** @brief Width of the game window. */
static const int window_width = 1280;

/** @brief Height of the game window. */
static const int window_height = 720;

/** @brief Font size used in the game. */
static const int font_size = 64;

/** @brief Number of buttons in the game menu. */
static const int menu_buttons = 11;

/** @brief Size of the game board. */
static const int board_size = 500;

/** @} */

/**
 * @defgroup GameBoard Game Board
 * @{
 */

/** @brief Two-dimensional array representing the game board. */
static int board[9][9];

/** @} */

/**
 * @defgroup Enumerations Enumerations
 * @{
 */

/** @brief Enumeration of menu buttons. */
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
	prev_o,
	switch_online
};

/** @} */

/**
 * @defgroup Structures Structures
 * @{
 */

/** @brief Structure representing a cell in the game board. */
typedef struct cell
{
	SDL_Rect rect; /**< Rectangle representing the cell. */
} Cell;

/** @brief Structure representing an object with background and content. */
typedef struct object
{
	SDL_Rect background_rect;	 /**< Rectangle representing the background. */
	SDL_Rect content_rect;		 /**< Rectangle representing the content. */
	SDL_Texture *background_txt; /**< Texture for the background. */
	SDL_Texture *content_txt;	 /**< Texture for the content. */
} Object;

/** @brief Structure representing a button with background and content. */
typedef struct button
{
	SDL_RendererFlip flip;		 /**< Renderer flip for the button. */
	SDL_Rect background_rect;	 /**< Rectangle representing the background. */
	SDL_Rect content_rect;		 /**< Rectangle representing the content. */
	SDL_Texture *background_txt; /**< Texture for the background. */
	SDL_Texture *content_txt;	 /**< Texture for the content. */
} Button;

/** @brief Structure representing the color palette used in the game. */
typedef struct pallete
{
	TTF_Font *font;			  /**< Font used in the game. */
	int sprite_x;			  /**< X sign sprite. */
	int sprite_o;			  /**< O sign sprite. */
	SDL_Color background;	  /**< Background color. */
	SDL_Color board_lines;	  /**< Board lines color. */
	SDL_Color spot_highlight; /**< Spot highlight color. */
	SDL_Color text;			  /**< Text color. */
} Pallete;

/** @brief Structure representing game textures. */
typedef struct textures
{
	SDL_Texture *single_arrow;	   /**< Texture for the single arrow. */
	SDL_Texture *double_arrow;	   /**< Texture for the double arrow. */
	SDL_Texture *sign_x;		   /**< Texture for the X sign. */
	SDL_Texture *sign_o;		   /**< Texture for the O sign. */
	SDL_Texture *modes;			   /**< Texture for the game modes. */
	SDL_Texture *field_background; /**< Texture for the field background. */
	SDL_Texture *logo;			   /**< Texture for the game logo. */
} Textures;

/** @brief Structure representing the game menu. */
typedef struct menu
{
	Object *logo;	  /**< Logo object. */
	Object *game_id;  /**< Game ID object. */
	Object *sign_x;	  /**< X sign object. */
	Object *sign_o;	  /**< O sign object. */
	Button **buttons; /**< Array of menu buttons. */
} Menu;

/** @brief Structure representing the playfield in the game. */
typedef struct playfield
{
	Object *background; 	/**< Background object. */
	Object *timer;			/**< Timer object. */
	Cell **super_cells;		/**< Array of 3x3 board cells in the playfield. */
	Cell **normal_cells;	/**< Array of 9x9 board cells in the playfield. */
	Button *put_sign;		/**< Button for putting a sign. */
	Button *forfeit;		/**< Button for forfeiting the game. */
} Playfield;

/** @brief Structure representing SDL-related data. */
typedef struct sdl_data
{
	Game *game;											  /**< Pointer to the game data. */
	bool super_mode;									  /**< Flag indicating super mode. */
	bool on_lan;										  /**< Flag indicating LAN mode. */
	bool in_game;										  /**< Flag indicating whether in-game. */
	int bot_difficulty;									  /**< Bot difficulty level. */
	int game_id;										  /**< Current game ID. */
	int last_time;										  /**< Last time left in the game. */
	int select_x;										  /**< X-coordinate of the selected cell. */
	int select_y;										  /**< Y-coordinate of the selected cell. */
	int select_board;									  /**< Selected game board. */
	SDL_Window *window;									  /**< SDL window. */
	SDL_Renderer *renderer;								  /**< SDL renderer. */
	Textures *textures;									  /**< Game textures. */
	Menu *menu;											  /**< Game menu. */
	void (**menu_functions)(struct sdl_data *);			  /**< Array of menu functions. */
	void (*select_cell)(struct sdl_data *, int x, int y); /**< Function for selecting a cell. */
	void (*put_sign)(struct sdl_data *);				  /**< Function for putting a sign. */
	void (*forfeit)(struct sdl_data *);					  /**< Function for forfeiting the game. */
	Playfield *playfield;								  /**< Game playfield. */
	Pallete *pallete;									  /**< Color palette. */
} Sdl_Data;

/** @} */

/**
 * @defgroup Functions Functions
 * @{
 */

/** @brief Initialize SDL and game data.
 *  @param sdl_data_ptr Pointer to the SDL data structure.
 *  @return True if initialization is successful, false otherwise.
 */
bool init_sdl(Sdl_Data **sdl_data_ptr);

/** @brief Load game media.
 *  @param sdl_data Pointer to the SDL data structure.
 *  @return True if loading is successful, false otherwise.
 */
bool load_media(Sdl_Data *sdl_data);

/** @brief Handle frame events.
 *  @param sdl_data Pointer to the SDL data structure.
 *  @param quit Pointer to the quit flag.
 */
void frame_events(Sdl_Data *sdl_data, bool *quit);

/** @brief Close SDL and free resources.
 *  @param sdl_data Pointer to the SDL data structure.
 */
void close_sdl(Sdl_Data *sdl_data);

/** @} */

#endif // GAME_H
