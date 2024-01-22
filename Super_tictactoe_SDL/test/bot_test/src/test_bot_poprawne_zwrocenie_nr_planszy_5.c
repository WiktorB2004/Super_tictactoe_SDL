#include "unity.h"
#include "../include/bot_test.h"

extern Game *game;
void test_bot_poprawne_zwrocenie_nr_planszy_5(void)
{
    //ustawienie planszy
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            game -> board[4] -> value[i][j] = 0; //X

    game -> board[4] -> value[1][2] = 2;

    int next_czesc = bot(game, 4, 4);
    TEST_ASSERT_TRUE(next_czesc == 5);
}