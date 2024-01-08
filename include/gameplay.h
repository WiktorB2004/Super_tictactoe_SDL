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
    NOT_STARTED, /**< Game waiting for the start  - 4 */
} GameStatus;

/*!
 * \brief Enumerates the turns of players.
 *
 * This enumeration represents which player is about to place next move.
 */
typedef enum
{
    O,     /**< O - 0 */
    X,     /**< X - 1 */
    EMPTY, /**< Empty space - 2 */
} Player;

/*!
 * \brief Represents a single tictactoe board.
 *
 * This structure defines tictactoe board. It keeps game status and board as 3x3 matrix,
 * with "X" and "O" as user moves.
 */
typedef struct
{
    GameStatus status;  /**< Status of the game on the board */
    int moves_count;    /**< Counter of moves played on the board */
    Player value[3][3]; /**< Matrix representing the board */
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
    Player turn;       /**< X or O indicating which player is about to move next */
} Game;

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
 * \brief This function initializes game of specified size (nxn).
 *
 * This function initializes game of specified size by allocating needed memory
 * and other struct values.
 *
 *
 * @param game Pointer to UltimateGame to initialize.
 * @param size The size of the game to initialize
 */
void initialize_Game(Game *game, int size);

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
 * @param player The sign representing the players turn - X or O (Player enum)
 */
void modify_board(Board *board, int row, int column, Player player);

/*!
 * \brief This function perform checks on the board and manages its status.
 *
 * This function checks the board and if there is a draw or someone won the game it
 * modifies the board status
 *
 * @param board The board to be checked.
 * @param turn The player turn on the board / in the game depending on game board size.
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
void check_game(Game *game, Player turn);

/*!
 * \brief This function handles the tictac toe gameplay.
 *
 * This function executes logic needed to play any amount of the 3x3 games.
 * It keeps the correct order of player moves and executes check/modify functions.
 *
 * @param game The pointer to the game of tictactoe - initialized beforehand.
 */
void gameplay(Game *game);
