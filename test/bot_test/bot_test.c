#include "include/bot_test.h"
#include "../src/bot_test0.c"
#include "../src/bot_test1.c"
#include "../src/bot_test2.c"
#include "../src/bot_test3.c"
#include "../src/bot_test4.c"
#include "../src/bot_test5.c"
#include "../src/bot_test6.c"
#include "../src/bot_test7.c"
#include "../src/bot_test8.c"
#include "../src/bot_test9.c"
#include "../src/bot_test10.c"
#include "../src/bot_test11.c"
#include "../src/bot_test12.c"
#include "../src/bot_test13.c"
#include "../src/bot_test14.c"
#include "../src/bot_test15.c"
#include "../src/bot_test16.c"
#include "../src/bot_test17.c"
#include "../src/bot_test18.c"
#include "../src/bot_test19.c"

Game *game;
void setUp(void)
{  
    game = malloc(sizeof(Game));
    if(game == NULL){
        puts("bląd alokaji pamięci");
        exit(1);
    }

    initialize_Game(game, 3);
    game -> turn = 1; //X       
}

void tearDown(void)
{
    free_Game(game);   
}

int main(void)
{
    UNITY_BEGIN();

    //testy
    //pusta cała plansza
    RUN_TEST(test_bot0); 

    /*
        będe testował to jak sobie poradzi bot dla różnej ilości zapełnionych pól,
        test przeprowadze na częśi 4, reszta częsci nie ma znaczenia jak są ustawione
    */
    RUN_TEST(test_bot1); //0 miejsc wolnych
    RUN_TEST(test_bot2); //1 miejsce wolne
    RUN_TEST(test_bot3); //2 miejsce wolne
    RUN_TEST(test_bot4); //3 miejsce wolne
    RUN_TEST(test_bot5); //4 miejsce wolne
    RUN_TEST(test_bot6); //5 miejsce wolne
    RUN_TEST(test_bot7); //6 miejsce wolne
    RUN_TEST(test_bot8); //7 miejsce wolne
    RUN_TEST(test_bot9); //8 miejsce wolne
    RUN_TEST(test_bot10); //9 miejsce wolne

    /*
        będe spawdzał czy bot poprawnie zwraca częci planszy w której ma się odbyć 
        następny ruch
    */

    RUN_TEST(test_bot11); // ma dać 0
    RUN_TEST(test_bot12); // ma dać 1
    RUN_TEST(test_bot13); // ma dać 2
    RUN_TEST(test_bot14); // ma dać 3
    RUN_TEST(test_bot15); // ma dać 4
    RUN_TEST(test_bot16); // ma dać 5
    RUN_TEST(test_bot17); // ma dać 6
    RUN_TEST(test_bot18); // ma dać 7
    RUN_TEST(test_bot19); // ma dać 8

    //koniec testów
    return UNITY_END();
}