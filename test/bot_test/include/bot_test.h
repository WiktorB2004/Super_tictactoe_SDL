#pragma once

#include "unity.h"
#include "../../../include/game_bot.h"
#include "../../../include/utils/gameplay_utils.h"

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

//pusta cała plansza
void test_bot0(void);

/*
    będe testował to jak sobie poradzi bot dla różnej ilości zapełnionych pól,
    test przeprowadze na częśi 4, reszta częsci nie ma znaczenia jak są ustawione
*/

void test_bot1(void); //0 miejsc wolnych
void test_bot2(void);
void test_bot3(void);
void test_bot4(void);
void test_bot5(void);
void test_bot6(void);
void test_bot7(void);
void test_bot8(void);
void test_bot9(void);
void test_bot10(void); // 9 miejsc wolnych

/*
    będe spawdzał czy bot poprawnie zwraca częci planszy w której ma się odbyć 
    następny ruch
*/

void test_bot11(void); //ma dać 0
void test_bot12(void);
void test_bot13(void);
void test_bot14(void);
void test_bot15(void);
void test_bot16(void);
void test_bot17(void);
void test_bot18(void);
void test_bot19(void); //ma dać 8