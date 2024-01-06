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
} GameStatus;

/*!
 * \brief Represents a single tictactoe board.
 *
 * This structure defines tictactoe board. It keeps game status and board as 3x3 matrix,
 * with "X" and "O" as user moves.
 */
typedef struct
{
    GameStatus status; /**< Status of the game on the board */
    int moves_count;   /**< Counter of moves played on the board */
    char value[3][3];  /**< Matrix representing the board */
} Board;

/*!
 * \brief Represents any board of the size nxn.
 *
 * This structure defines tictactoe board. It keeps nxn game status and boards,
 * allowing to play on the boards of any size.
 */
typedef struct
{
    Board **board;     /**< Pointer to the pointer of boards - representation of nxn board */
    int board_size;    /**< boards are board_size x board_size */
    int moves_count;   /**< Counter of the moves played in the game */
    GameStatus status; /**< Status of the game on the board */
} UltimateGame;

/*!
 * \brief This function initializes game of specified size (nxn).
 *
 * This function initializes game of specified size by allocating needed memory
 * and other struct values.
 *
 *
 * @param game Pointer to UltimateGame to initialize.
 * @param size The size of the game to initialize
 */
void initialize_UltimateGame(UltimateGame *game, int size);

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
