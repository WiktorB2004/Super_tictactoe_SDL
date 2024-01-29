#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/gameplay.h"
#include "../../include/sdl_display.h"
#include "../../include/utils/gameplay_utils.h"
#include "../../include/game_bot.h"

int bot(Game *game, int czesc, int tryb);

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

void check_board(Board *board, Player turn, bool is_super)
{
    check_board_horizontally(board);
    check_board_vertically(board);
    check_board_diagonally(board);

    if (board->moves_count == 9 && board->status == IN_PROGRESS)
    {
        board->status = DRAW;
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
                board->moves_count++;
                break;
            case O_WON:
                board->value[i][j] = O;
                board->moves_count++;
                break;
            case DRAW:
                board->value[i][j] = DRAW;
                board->moves_count++;
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
    check_board(board, turn, true);
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
        if(game->bot_turn)
        {
            int board_id;

            if(data->super_mode)
            {
                board_id = bot(game, data->select_board, data->bot_difficulty + 3);
                data->select_board = game->board[board_id]->status == IN_PROGRESS ? board_id : -1;
            }
            else
            {
                board_id = bot(game, 0, 0);
            }

            game->bot_turn = 0;
        }   
        else
        {
            modify_board(game->board[data->select_board], data->select_x, data->select_y, game->turn);

            if(!data->on_lan)
            {
                game->bot_turn = 1;
            }
        }
        
        if (game->board_size > 1)
        {
            for (int board_id = 0; board_id < (game->board_size) * (game->board_size); board_id++)
            {
                check_board(game->board[board_id], game->turn, true);
                // check_draw(game->board[board_id]);
            }

            check_game(game, game->turn);
            game->moves_count++;
        }
        else if (game->board_size == 1)
        {
            check_board(game->board[0], game->turn, false);
            game->status = game->board[0]->status;
            game->moves_count = game->board[0]->moves_count;
        }
        game->turn = (game->turn == X) ? O : X;
    }
}
