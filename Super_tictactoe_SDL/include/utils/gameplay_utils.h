#pragma once
#include <stdbool.h>
#include "../gameplay.h"


/*!
 * \brief This function initializes regular game of size (3x3).
 *
 * This function initializes game of size 3x3 by allocating needed memory
 * and other struct values.
 *
 * @param board Pointer to board to initialize.
 */
void initialize_Board(Board *board);

/*!
 * \brief This function initializes game of specified size (NxN).
 *
 * This function initializes game of specified size by allocating needed memory
 * and other struct values.
 *
 *
 * @param game Pointer to Game to initialize.
 * @param size The size of the game to initialize
 */
void initialize_Game(Game *game, int size);

/*!
 * \brief This function deallocates memory of the Game.
 *
 * This function deallocates the memory allocated in initialize_Game function.
 *
 * @param game Pointer to the game to free.
 */
void free_Game(Game *game);

/*!
 * \brief This function perform horizontall checks on the board.
 *
 * This function checks the board and if someone won the game it
 * returns true.
 *
 * @param board The board to be checked.
 * @return win/continue = true/false
 */
bool check_board_horizontally(Board *board);

/*!
 * \brief This function perform verticall checks on the board.
 *
 * This function checks the board and if someone won the game it
 * returns true.
 *
 * @param board The board to be checked.
 * @return win/continue = true/false
 */
bool check_board_vertically(Board *board);

/*!
 * \brief This function perform diagonall checks on the board.
 *
 * This function checks the board and if someone won the game it
 * returns true.
 *
 * @param board The board to be checked.
 * @return win/continue = true/false
 */
bool check_board_diagonally(Board *board);

/*!
 * \brief This function perform horizontall checks on the board.
 *
 * This function checks the board and if it is still possible
 * to win the game by placing symbols horizontally it
 * returns true.
 *
 * @param board The board to be checked.
 * @return win/continue = true/false
 */
bool check_draw_horizontally(Board *board);

/*!
 * \brief This function perform verticall checks on the board.
 *
 * This function checks the board and if it is still possible
 * to win the game by placing symbols vertically it
 * returns true.
 *
 * @param board The board to be checked.
 * @return win/continue = true/false
 */
bool check_draw_vertically(Board *board);

/*!
 * \brief This function perform diagonall checks on the board.
 *
 * This function checks the board and if it is still possible
 * to win the game by placing symbols diagonally it
 * returns true.
 *
 * @param board The board to be checked.
 * @return win/continue = true/false
 */
bool check_draw_diagonally(Board *board);
