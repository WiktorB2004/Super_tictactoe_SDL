#include "include/bot_test.h"
#include "../../../include/gameplay.h"
#include "../../../include/utils/gameplay_utils.h"

Game *game;
void setUp(void)
{
    game = malloc(sizeof(Game));
    if (game == NULL)
    {
        puts("bląd alokaji pamięci");
        exit(1);
    }

    initialize_Game(game, 3);
    game->turn = 1; // X
}

void tearDown(void)
{
    free_Game(game);
}

int main(void)
{
    UNITY_BEGIN();

    // testy
    // pusta cała plansza
    RUN_TEST(test_czy_bot_ogolnie_dziala_poprawnie_dla_calej_pustej_planszy);

    /*
        będe testował to jak sobie poradzi bot dla rożnej ilości zapełnionych pol,
        test przeprowadze na częśi 4, reszta częsci nie ma znaczenia jak są ustawione
    */
    RUN_TEST(test_bot_miejsca_wolne_na_planszy_0); // 0 miejsc wolnych ma dać -1
    RUN_TEST(test_bot_miejsca_wolne_na_planszy_1); // 1 miejsce wolne
    RUN_TEST(test_bot_miejsca_wolne_na_planszy_2); // 2 miejsce wolne
    RUN_TEST(test_bot_miejsca_wolne_na_planszy_3); // 3 miejsce wolne
    RUN_TEST(test_bot_miejsca_wolne_na_planszy_4); // 4 miejsce wolne
    RUN_TEST(test_bot_miejsca_wolne_na_planszy_5); // 5 miejsce wolne
    RUN_TEST(test_bot_miejsca_wolne_na_planszy_6); // 6 miejsce wolne
    RUN_TEST(test_bot_miejsca_wolne_na_planszy_7); // 7 miejsce wolne
    RUN_TEST(test_bot_miejsca_wolne_na_planszy_8); // 8 miejsce wolne
    RUN_TEST(test_bot_miejsca_wolne_na_planszy_9); // 9 miejsce wolne

    /*
        będe spawdzał czy bot poprawnie zwraca częci planszy w ktorej ma się odbyć
        następny ruch
    */

    RUN_TEST(test_bot_poprawne_zwrocenie_nr_planszy_0); // ma dać 0
    RUN_TEST(test_bot_poprawne_zwrocenie_nr_planszy_1); // ma dać 1
    RUN_TEST(test_bot_poprawne_zwrocenie_nr_planszy_2); // ma dać 2
    RUN_TEST(test_bot_poprawne_zwrocenie_nr_planszy_3); // ma dać 3
    RUN_TEST(test_bot_poprawne_zwrocenie_nr_planszy_4); // ma dać 4
    RUN_TEST(test_bot_poprawne_zwrocenie_nr_planszy_5); // ma dać 5
    RUN_TEST(test_bot_poprawne_zwrocenie_nr_planszy_6); // ma dać 6
    RUN_TEST(test_bot_poprawne_zwrocenie_nr_planszy_7); // ma dać 7
    RUN_TEST(test_bot_poprawne_zwrocenie_nr_planszy_8); // ma dać 8

    // koniec testow
    return UNITY_END();
}
