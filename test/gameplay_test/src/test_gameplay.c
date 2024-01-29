#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "../../include/gameplay.h"
#include "../include/gameplay_test.h"
#include "../../include/utils/gameplay_utils.h"

// Test case for initialize_Board function
void test_initialize_Board(void)
{
    Board board;
    initialize_Board(&board);

    TEST_ASSERT_EQUAL(IN_PROGRESS, board.status);
    TEST_ASSERT_EQUAL(0, board.moves_count);

    // Test the initialization of the board values
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            TEST_ASSERT_EQUAL(EMPTY, board.value[i][j]);
        }
    }
}

// Test case for initialize_Game function
void test_initialize_Game(void)
{
    Game game;
    initialize_Game(&game);

    TEST_ASSERT_EQUAL(NOT_STARTED, game.status);
    TEST_ASSERT_EQUAL(0, game.moves_count);
    TEST_ASSERT_EQUAL(X, game.turn);

    for (int i = 0; i < 9; i++)
    {
        TEST_ASSERT_NOT_NULL(game.board[i]);
        TEST_ASSERT_EQUAL(IN_PROGRESS, game.board[i]->status);
        TEST_ASSERT_EQUAL(0, game.board[i]->moves_count);
    }
}

// FIXME: Missing board pointers check
// Test case for free_Game function
void test_free_Game(void)
{
    Game *test_game = (Game *)malloc(sizeof(Game));
    TEST_ASSERT_NOT_NULL(test_game); // Check if memory allocation is successful

    initialize_Game(test_game);

    free_Game(test_game);

    TEST_ASSERT_NULL(test_game->board);

    free(test_game);
}

// Test case for check_board_horizontally function
void test_check_board_horizontally(void)
{
    Board board;
    initialize_Board(&board);

    board.value[0][0] = X;
    board.value[0][1] = X;
    board.value[0][2] = X;

    TEST_ASSERT_TRUE(check_board_horizontally(&board));
    TEST_ASSERT_EQUAL(X_WON, board.status);
}

// Test case for check_board_vertically function
void test_check_board_vertically(void)
{
    Board board;
    initialize_Board(&board);

    board.value[0][0] = O;
    board.value[1][0] = O;
    board.value[2][0] = O;

    TEST_ASSERT_TRUE(check_board_vertically(&board));
    TEST_ASSERT_EQUAL(O_WON, board.status);
}

// Test case for check_board_diagonally function
void test_check_board_diagonally(void)
{
    Board board;
    initialize_Board(&board);

    board.value[0][0] = X;
    board.value[1][1] = X;
    board.value[2][2] = X;

    TEST_ASSERT_TRUE(check_board_diagonally(&board));
    TEST_ASSERT_EQUAL(X_WON, board.status);
}

// Test case for modify_board function
void test_modify_board(void)
{
    Board board;
    initialize_Board(&board);

    modify_board(&board, 0, 0, X);
    TEST_ASSERT_EQUAL(X, board.value[0][0]);
    TEST_ASSERT_EQUAL(1, board.moves_count);

    modify_board(&board, 0, 0, O);
    TEST_ASSERT_EQUAL(X, board.value[0][0]); // Value shouldn't change
    TEST_ASSERT_EQUAL(1, board.moves_count); // Moves count remains the same

    board.status = X_WON;
    modify_board(&board, 1, 1, O);
    TEST_ASSERT_EQUAL(X_WON, board.status);  // Status should remain X_WON
    TEST_ASSERT_EQUAL(1, board.moves_count); // Moves count remains the same
}

// Test case for check_board function
void test_check_board(void)
{
    Board board;
    initialize_Board(&board);

    board.value[0][0] = X;
    board.value[0][1] = X;
    board.value[0][2] = X;

    Player turn = X;
    check_board(&board, turn, false);
    TEST_ASSERT_EQUAL(X_WON, board.status);

    board.status = IN_PROGRESS;
    board.value[0][0] = O;
    board.value[1][0] = O;
    board.value[2][0] = O;

    turn = O;
    check_board(&board, turn, false);
    TEST_ASSERT_EQUAL(O_WON, board.status);
}

// Test case for check_game function
void test_check_game(void)
{
    Game game;
    int size = 2;
    initialize_Game(&game);
    Player turn = X;
    check_game(&game, turn);
    TEST_ASSERT_EQUAL(IN_PROGRESS, game.status);

    // Simulate a situation where all boards result in a draw
    for (int i = 0; i < (size * size); i++)
    {
        game.board[i]->status = DRAW;
    }

    check_game(&game, turn);
    TEST_ASSERT_EQUAL(DRAW, game.status);
}

// Test case for gameplay function - integration test
void test_gameplay(void)
{
    // Requires user input simulation or mocking for complete testing
    // This can be challenging to unit test completely without user interaction simulation - consider using the bot.
}