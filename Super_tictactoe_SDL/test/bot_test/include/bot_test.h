#pragma once

#ifndef BOT_TEST_H
#define BOT_TEST_H

#include "unity.h"
#include "../../../include/game_bot.h"
#include "../../../include/utils/gameplay_utils.h"

extern Game *game;

void test_czy_bot_ogolnie_dziala_poprawnie_dla_calej_pustej_planszy(void);

void test_bot_miejsca_wolne_na_planszy_0(void);
void test_bot_miejsca_wolne_na_planszy_1(void);
void test_bot_miejsca_wolne_na_planszy_2(void);
void test_bot_miejsca_wolne_na_planszy_3(void);
void test_bot_miejsca_wolne_na_planszy_4(void);
void test_bot_miejsca_wolne_na_planszy_5(void);
void test_bot_miejsca_wolne_na_planszy_6(void);
void test_bot_miejsca_wolne_na_planszy_7(void);
void test_bot_miejsca_wolne_na_planszy_8(void);
void test_bot_miejsca_wolne_na_planszy_9(void);

void test_bot_poprawne_zwrocenie_nr_planszy_0(void);
void test_bot_poprawne_zwrocenie_nr_planszy_1(void);
void test_bot_poprawne_zwrocenie_nr_planszy_2(void);
void test_bot_poprawne_zwrocenie_nr_planszy_3(void);
void test_bot_poprawne_zwrocenie_nr_planszy_4(void);
void test_bot_poprawne_zwrocenie_nr_planszy_5(void);
void test_bot_poprawne_zwrocenie_nr_planszy_6(void);
void test_bot_poprawne_zwrocenie_nr_planszy_7(void);
void test_bot_poprawne_zwrocenie_nr_planszy_8(void);

#endif // BOT_TEST_H