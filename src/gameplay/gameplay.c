#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/gameplay.h"
#include "../../include/sdl_display.h"
#include "../../include/utils/gameplay_utils.h"

void modify_board(Board *board, int row, int column, Player player)
{
    switch (board->status)
    {
    case IN_PROGRESS:
        if (board->value[row][column] == EMPTY)
        {
            board->value[row][column] = player;
            board->moves_count++;
        }
        else
        {
            fprintf(stderr, "This place is taken - choose another spot.\n");
        }
        break;
    case X_WON:
    case O_WON:
    case DRAW:
        fprintf(stderr, "Invalid action: The game has already ended.\n");
        break;
    default:
        fprintf(stderr, "Incorrect board status provided - cant modify the board.\n");
        exit(EXIT_FAILURE);
        break;
    }
}

void check_board(Board *board, Player turn)
{
    bool check_result = check_board_horizontally(board) || check_board_vertically(board) || check_board_diagonally(board);
    if (check_result && board->status == IN_PROGRESS)
    {
        switch (turn)
        {
        case X:
            board->status = X_WON;
            break;
        case O:
            board->status = O_WON;
            break;
        default:
            fprintf(stderr, "Incorrect turn data provided - couldnt check the board status.\n");
            exit(EXIT_FAILURE);
            break;
        }
    }
}

void check_draw(Board *board)
{
    bool check_result = check_draw_horizontally(board) || check_draw_vertically(board) || check_draw_diagonally(board);
    if (!check_result)
        board->status = DRAW;
}

void check_game(Game *game, Player turn)
{
    Board *board = (Board *)malloc(sizeof(Board));
    initialize_Board(board);

    int idx = 0;
    for (int i = 0; i < game->board_size; i++)
    {
        for (int j = 0; j < game->board_size; j++)
        {
            switch (game->board[idx]->status)
            {
            case X_WON:
                board->value[i][j] = X;
            case O_WON:
                board->value[i][j] = O;
                break;
            case DRAW:
                board->value[i][j] = DRAW;
                break;
            case IN_PROGRESS:
                board->value[i][j] = EMPTY;
                break;
            default:
                fprintf(stderr, "Incorrect game status provided - couldnt remap game->board into NxN board.\n");
                exit(EXIT_FAILURE);
                break;
            }
            idx++;
        }
    }

    check_board(board, turn);
    game->status = board->status;
    free(board);
}

void check_game_draw(Game *game)
{
    Board *board = (Board *)malloc(sizeof(Board));
    initialize_Board(board);
    int idx = 0;
    while (idx < 9)
    {
        int pom = game->board[idx]->status;
        if (pom == 1)
            board->value[idx / 3][idx % 3] = 1;
        else if (pom == 2)
            board->value[idx / 3][idx % 3] = 0;
        else if (pom == 3)
            board->value[idx / 3][idx % 3] = 3;
        else
            board->value[idx / 3][idx % 3] = 2;
        idx++;
    }
    check_draw(board);
    if (game->status == 0)
        game->status = board->status;
    free(board);
}

void gameplay(Sdl_Data *data)
{
    Game *game = data->game;
    if (game->status == IN_PROGRESS)
    {
        modify_board(game->board[data->select_board], data->select_x, data->select_y, game->turn);
        for (int board_id = 0; board_id < (game->board_size) * (game->board_size); board_id++)
        {
            check_board(game->board[board_id], game->turn);
            // check_draw(game->board[board_id]);
        }

        if (game->board_size == 1)
        {
            game->status = game->board[0]->status;
        }
        else
        {
            check_game(game, game->turn);
            // check_game_draw(game);
        }
        game->turn = (game->turn == X) ? O : X;
        game->moves_count++;
    }
}
