#pragma once

#include "unity.h"
#include "../../../include/game_bot.h"
#include "../../../include/gameplay.h"

#include "../src/sample_test0.c"
#include "../src/sample_test1.c"
#include "../src/sample_test2.c"
#include "../src/sample_test3.c"
#include "../src/sample_test4.c"
#include "../src/sample_test5.c"
#include "../src/sample_test6.c"
#include "../src/sample_test7.c"
#include "../src/sample_test8.c"
#include "../src/sample_test9.c"
#include "../src/sample_test10.c"
#include "../src/sample_test11.c"
#include "../src/sample_test12.c"
#include "../src/sample_test13.c"
#include "../src/sample_test14.c"
#include "../src/sample_test15.c"
#include "../src/sample_test16.c"
#include "../src/sample_test17.c"
#include "../src/sample_test18.c"
#include "../src/sample_test19.c"


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