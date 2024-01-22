#include "unity.h"
#include "../include/bot_test.h"

extern Game *game;
void test_czy_bot_ogólnie_dziala_poprawnie_dla_calej_pustej_planszy(void)
{
    //ustawienie planszy
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            game -> board[4] -> value[i][j] = 2;

    int next_czesc = bot(game, 4, 4);
    TEST_ASSERT_TRUE(next_czesc >= 0 && next_czesc <= 8);
}