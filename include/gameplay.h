#pragma once

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
} BoardStatus;

/*!
 * \brief Represents a single tictactoe board.
 *
 * This structure defines tictactoe board. It keeps game status and board as 3x3 matrix,
 * with "X" and "O" as user moves.
 */
typedef struct
{
    BoardStatus status;
    int moves_count;
    char value[3][3];
} Board;

/*!
 * \brief This function places the move in specified row/column.
 *
 * This function places the move using provided row and column on 3x3 board.
 * It edits the board in place and return nothing.
 *
 *
 * @param board The board to be modified.
 * @param row The row on the board on which to put the move.
 * @param column The column on the board on which to put the move.
 * @param player The sign representing the players turn - X or O
 */
void modify_board(Board *board, int row, int column, char player);

/*!
 * \brief This function perform checks on the board and manages its status.
 *
 * This function checks the board and if there is a draw or someone won the game it
 * modifies the board status
 *
 * @param board The board to be checked.
 */
void check_board(Board *board);

/*!
 * \brief This function handles gameplay on a single board.
 *
 * This function executes logic needed to play the 3x3 game on one board.
 * It keeps the correct order of player moves and executes check/modify functions.
 *
 * @param board The board representing single game of tictactoe.
 */
void gameplay(Board *board);
