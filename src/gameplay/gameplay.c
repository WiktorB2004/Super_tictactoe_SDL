#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/gameplay.h"
#include "../../include/utils/gameplay_utils.h"

// FIXME: Create memory deallocation functions - use them inside engine after the end of the game

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
    if (check_result)
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

void gameplay(Game *game)
{
    int mv_board = 0, mv_row, mv_col;
    while (game->status == IN_PROGRESS)
    {
        // -------------TO BE DELETED--------------------
        // Sketch of printing the board
        for (int k = 0; k < game->board_size; k++)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    printf("%d", game->board[k]->value[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }
        // Sketch of getting user input
        if (game->board_size > 1)
        {
            printf("Select the board to place a move (0 - %d)\n", game->board_size - 1);
            scanf("%d", &mv_board);
        }
        printf("Enter the point to place a move (0 - %d) (0 - %d)\n", 2, 2);
        scanf("%d %d", &mv_row, &mv_col);
        // ------------TO BE DELETED--------------------

        modify_board(game->board[mv_board], mv_row, mv_col, game->turn);

        // Check the boards and game for win/draw
        // FIXME: Check for draw
        for (int board_id = 0; board_id < game->board_size; board_id++)
        {
            check_board(game->board[board_id], game->turn);
        }

        if (game->board_size == 1)
        {
            game->status = game->board[0]->status;
        }
        else
        {
            check_game(game, game->turn);
        }
        // Add to the moves count and switch turns
        game->turn = (game->turn == X) ? O : X;
        game->moves_count++;
    }

    // ------------TO BE DELETED--------------------
    printf("WYGRAL: %d\n", game->status);
    // -------------TO BE DELETED--------------------
}