#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/gameplay.h"
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

void check_draw(Board *board)
{
    bool check_result = check_draw_horizontally(board) || check_draw_vertically(board) || check_draw_diagonally(board);
    if (!check_result) board->status=DRAW;
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
    while(idx<9)
    {
        int pom = game->board[idx]->status;
        if( pom == 1 ) board->value[idx/3][idx%3] = 1;
        else if( pom == 2 ) board->value[idx/3][idx%3] = 0;
        else if( pom == 3 ) board->value[idx/3][idx%3] = 3;
        else board->value[idx/3][idx%3] = 2;
        idx++;
        for(int a=0;a<3;a++)
            {
                for(int b=0;b<3;b++) printf("%d",board->value[a][b]);
                printf("\n");
            }
            printf("\n");
    }
    /*for (int i = 0; i < game->board_size; i++)
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
                board->value[i][j] = DRAW_pom;
                break;
            case IN_PROGRESS:
                board->value[i][j] = EMPTY;
                break;
            default:
                fprintf(stderr, "Incorrect game status provided - couldnt remap game->board into NxN board.\n");
                exit(EXIT_FAILURE);
                break;
            }
        }
    }*/
    check_draw(board);
    if( game->status == 0 ) game->status = board->status;
    free(board);
}

void gameplay(Game *game)
{
    int mv_board = 0, mv_row, mv_col;
    while (game->status == IN_PROGRESS)
    {
        // -------------TO BE DELETED--------------------
        // Sketch of printing the board
        int b=0;
        for(int k = 0; k < 3*(game->board_size); k++)
        {
              int i = k % 3;
              for(int j=0;j<3;j++) printf("%d", game->board[b]->value[i][j]);
              printf(" ");
              for(int j=0;j<3;j++) printf("%d", game->board[b+1]->value[i][j]);
              printf(" ");
              for(int j=0;j<3;j++) printf("%d", game->board[b+2]->value[i][j]);
              printf("\n");

              if( k % 3 == 2 && k>0) { printf("\n"); b+=3; }
        }
        // Sketch of getting user input
        if (game->board_size > 1)
        {
            printf("Select the board to place a move (0 - %d)\n", (game->board_size)*(game->board_size) - 1);
            while(true)
            {
                if( scanf("%d",&mv_board)<1 )
                {
                    fprintf(stderr,"You must select a number\n");
                    continue;
                }
                else if( mv_board<0 || mv_board>(game->board_size)*(game->board_size)-1 )
                {
                    fprintf(stderr,"The number selected must be in range(0 - %d)\n",(game->board_size)*(game->board_size)-1);
                    continue;
                }
                break;
            }
        }
        printf("Enter the point to place a move (0 - %d) (0 - %d)\n", 2, 2);
        while(true)
        {
             if( scanf("%d %d", &mv_row, &mv_col)<2 )
             {
                  fprintf(stderr,"You must select two numbers\n");
                  continue;
             }
             else if( mv_row<0 || mv_col<0 || mv_row>2 || mv_col>2 )
             {
                  fprintf(stderr,"Selected numbers must both be in range(0 - 2)\n" );
                  continue;
             }
             break;
        }
        // ------------TO BE DELETED--------------------

        modify_board(game->board[mv_board], mv_row, mv_col, game->turn);

        // Check the boards and game for win/draw
        // FIXME: Check for draw
        for (int board_id = 0; board_id < (game->board_size)*(game->board_size); board_id++)
        {
            check_board(game->board[board_id], game->turn);
            check_draw(game->board[board_id]);
        }

        if (game->board_size == 1)
        {
            game->status = game->board[0]->status;
        }
        else
        {
            check_game(game, game->turn);
            check_game_draw(game);
        }
        // Add to the moves count and switch turns
        game->turn = (game->turn == X) ? O : X;
        game->moves_count++;
    }

    // ------------TO BE DELETED--------------------
    switch(game->status)
    {
        case X_WON:
        case O_WON:
             printf("WYGRAL: %d\n", game->status);
             break;
        case DRAW:
             printf("REMIS");
             break;
        default:
             fprintf(stderr,"BLAD PRZY WYPISYWANIU STATUSU");
    }
    // -------------TO BE DELETED--------------------
}
