#pragma once

#include "unity.h"
#include "../../../include/game_bot.h"
#include "../../../include/gameplay.h"

Game *game;

//pusta cała plansza
void test_sample0(void);

/*
    będe testował to jak sobie poradzi bot dla różnej ilości zapełnionych pól,
    test przeprowadze na częśi 4, reszta częsci nie ma znaczenia jak są ustawione
*/

void test_sample1(void); //0 miejsc wolnych
void test_sample2(void);
void test_sample3(void);
void test_sample4(void);
void test_sample5(void);
void test_sample6(void);
void test_sample7(void);
void test_sample8(void);
void test_sample9(void);
void test_sample10(void); // 9 miejsc wolnych

/*
    będe spawdzał czy bot poprawnie zwraca częci planszy w której ma się odbyć 
    następny ruch
*/

void test_sample11(void); //ma dać 0
void test_sample12(void);
void test_sample13(void);
void test_sample14(void);
void test_sample15(void);
void test_sample16(void);
void test_sample17(void);
void test_sample18(void);
void test_sample19(void); //ma dać 8