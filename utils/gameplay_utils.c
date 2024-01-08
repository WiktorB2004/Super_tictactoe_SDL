#include <stdbool.h>
#include "../include/gameplay.h"
#include "../include/utils/gameplay_utils.h"

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