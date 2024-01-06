#pragma once
#include <stdbool.h>
#include "../gameplay.h"

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
