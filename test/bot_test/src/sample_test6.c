#include "unity.h"
#include "../include/bot_test.h"

// Example test case
void test_sample(void)
{
    //ustawienie planszy
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            game -> board[4] -> value[i][j] = 0; //X

    for(int i = 0; i < 3; i++) game -> board[4] -> value[2][i] = 2; // ' ' 
    game -> board[4] -> value[1][2] = 2; // ' '
    game -> board[4] -> value[1][1] = 2; // ' '

    int next_czesc = bot(game, 4, 4);
    TEST_ASSERT_TRUE(next_czesc >= 4 && next_czesc <= 8);    
}