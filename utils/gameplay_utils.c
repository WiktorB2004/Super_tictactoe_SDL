#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/gameplay.h"
#include "../include/utils/gameplay_utils.h"

void initialize_Board(Board *board)
{
    board->status = IN_PROGRESS;
    board->moves_count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board->value[i][j] = EMPTY;
        }
    }
}

void initialize_Game(Game *game, int size)
{
    game->board = (Board **)malloc(sizeof(Board *) * (size * size));
    if (game->board == NULL)
    {
        fprintf(stderr, "Memory allocation for Game failed.\n");
        exit(EXIT_FAILURE);
    }
    // FIXME: Make it random
    for (int i = 0; i < (size * size); i++)
    {
        game->board[i] = (Board *)malloc(sizeof(Board));
        initialize_Board(game->board[i]);
    }
    game->turn = X;
    game->board_size = size;
    game->moves_count = 0;
    game->status = NOT_STARTED;
}

void free_Game(Game *game)
{
    if (game == NULL)
    {
        return;
    }

    if (game->board != NULL)
    {
        for (int i = 0; i < (game->board_size * game->board_size); i++)
        {
            if (game->board[i] != NULL)
            {
                free(game->board[i]);
            }
        }
        free(game->board);
    }
}

bool check_board_horizontally(Board *board)
{
    for (int row = 0; row < 3; ++row)
    {
        if (board->value[row][0] != EMPTY &&
            board->value[row][0] == board->value[row][1] &&
            board->value[row][0] == board->value[row][2])
        {
            if (board->value[row][0] == X)
                board->status = X_WON;
            else
                board->status = O_WON;
            return true;
        }
    }
    return false;
}

bool check_board_vertically(Board *board)
{
    for (int col = 0; col < 3; ++col)
    {
        if (board->value[0][col] != EMPTY &&
            board->value[0][col] == board->value[1][col] &&
            board->value[0][col] == board->value[2][col])
        {
            if (board->value[0][col] == X)
                board->status = X_WON;
            else
                board->status = O_WON;
            return true;
        }
    }
    return false;
}

bool check_board_diagonally(Board *board)
{
    Player player = board->value[1][1];
    if (player != EMPTY &&
        ((board->value[0][0] == player && board->value[2][2] == player) ||
         (board->value[0][2] == player && board->value[2][0] == player)))
    {
        if (player == X)
            board->status = X_WON;
        else
            board->status = O_WON;
        return true;
    }
    return false;
}