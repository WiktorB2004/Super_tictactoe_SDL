#ifndef GAME_H
#define GAME_H
#include "./sdl_display.h"

typedef struct sdl_data Sdl_Data;
typedef long long Timer;

/** @brief Maximum time for a single game in seconds. */
static const int max_round_time = 900;

/*!
 * \brief Enumerates all the statuses of the board.
 *
 * This enumeration represents game status on single board, helps to manage online game hosting
 * and score tracking on boards bigger than 3x3.
 */
typedef enum
{
    IN_PROGRESS, /**< Game in progress - 0 */
    X_WON,       /**< X won - 1 */
    O_WON,       /**< O won  - 2 */
    DRAW,        /**< Draw  - 3 */
    NOT_STARTED, /**< Game waiting for the start  - 4 */
} GameStatus;

/*!
 * \brief Enumerates the turns of players.
 *
 * This enumeration represents which player is about to place next move and
 * is used as indicators in the Board values
 */
typedef enum
{
    EMPTY, /**< Empty space - 0 */
    X,     /**< X - 1 */
    O,     /**< O - 2 */
} Player;

/*!
 * \brief Represents a single tictactoe board.
 *
 * This structure defines tictactoe board. It keeps game status and board as 3x3 matrix,
 * with X and O as player moves.
 */
typedef struct
{
    GameStatus status;  /**< Status of the game on the board */
    int moves_count;    /**< Number of moves played on the board */
    Player value[3][3]; /**< Matrix representing the board */
} Board;

/*!
 * \brief Represents any board of the size NxN.
 *
 * This structure defines tictactoe board. It keeps NxN game status and boards,
 * allowing to play on the boards of any (correct) size.
 */
typedef struct Game
{
    int round_time;    /**< Max time for a round in seconds */
    Timer timer;       /**< The end value of a timer */
    Board **board;     /**< Pointer to the pointer of board - linear representation of NxN board */
    int board_size;    /**< boards are board_size x board_size */
    int moves_count;   /**< Numbers of the moves played in the game */
    GameStatus status; /**< Status of the game */
    Player turn;       /**< X or O indicating which player is about to move next */
} Game;

/*!
 * \brief This function places the move in specified row/column.
 *
 * This function places the move using provided row and column on 3x3 board.
 * It edits the board in place and returns nothing.
 *
 * @param board The board to be modified.
 * @param row The row on the board on which to put the move.
 * @param column The column on the board on which to put the move.
 * @param player The sign representing the players turn - X or O (Player enum)
 */
void modify_board(Board *board, int row, int column, Player player);

/*!
 * \brief This function perform checks on the single board and manages its status.
 *
 * This function checks the single board and if there is a draw or someone won the game it
 * modifies the board status
 *
 * @param board The board to be checked.
 * @param turn The player in the game.
 */
void check_board(Board *board, Player turn);

/*!
 * \brief This function perform checks on the game and manages its status.
 *
 * This function checks all the game boards and if there is a draw or someone won the game it
 * modifies the game status
 *
 * @param game The game to be checked.
 * @param turn The player turn in the game.
 */
void check_draw(Board *board);

/*!
 * \brief This function perform checks on the game and manages its status.
 *
 * This function checks all the game boards and if there is a draw or someone won the game it
 * modifies the game status
 *
 * @param game The game to be checked.
 * @param turn The player turn in the game.
 */
void check_game(Game *game, Player turn);

void check_game_draw(Game *game);

/*!
 * \brief This function handles the tictac toe gameplay.
 *
 * This function executes logic needed to play any (correct) amount of the 3x3 games.
 * It keeps the correct order of player moves and executes check/modify functions.
 *
 * @param game The pointer to the game of tictactoe - initialized beforehand.
 */
void gameplay(Sdl_Data *game);

#endif // GAME_H
