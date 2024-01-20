#include "include/bot_test.h"

extern Game *game;
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
    RUN_TEST(test_sample0); 

    /*
        będe testował to jak sobie poradzi bot dla różnej ilości zapełnionych pól,
        test przeprowadze na częśi 4, reszta częsci nie ma znaczenia jak są ustawione
    */
    RUN_TEST(test_sample1); //0 miejsc wolnych
    RUN_TEST(test_sample2); //1 miejsce wolne
    RUN_TEST(test_sample3); //2 miejsce wolne
    RUN_TEST(test_sample4); //3 miejsce wolne
    RUN_TEST(test_sample5); //4 miejsce wolne
    RUN_TEST(test_sample6); //5 miejsce wolne
    RUN_TEST(test_sample7); //6 miejsce wolne
    RUN_TEST(test_sample8); //7 miejsce wolne
    RUN_TEST(test_sample9); //8 miejsce wolne
    RUN_TEST(test_sample10); //9 miejsce wolne

    /*
        będe spawdzał czy bot poprawnie zwraca częci planszy w której ma się odbyć 
        następny ruch
    */

    RUN_TEST(test_sample11); // ma dać 0
    RUN_TEST(test_sample12); // ma dać 1
    RUN_TEST(test_sample13); // ma dać 2
    RUN_TEST(test_sample14); // ma dać 3
    RUN_TEST(test_sample15); // ma dać 4
    RUN_TEST(test_sample16); // ma dać 5
    RUN_TEST(test_sample17); // ma dać 6
    RUN_TEST(test_sample18); // ma dać 7
    RUN_TEST(test_sample19); // ma dać 8

    //koniec testów
    return UNITY_END();
}