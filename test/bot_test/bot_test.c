#include "include/bot_test.h"
#include "../../../include/gameplay.h"
#include "../../../include/utils/gameplay_utils.h"

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
