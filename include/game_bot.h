/*
    @file bot.c
    Implementacja botów o trzech stopniach trudności i w dwóch wariantach rozmiaru planszy.

    Bot przyjmuje argumenty:
        - wskaźnik na planszę do gry
        - kto wykonuje ruch: X czy O
        - w której części ma się odbyć ruch, jeśli plansza jest 3x3 to 
            podaj argument = 0, jeśli plansza jest 9x9 to indeksuje części:
            0 | 1 | 2
            ----------
            3 | 4 | 5
            ----------
            5 | 7 | 8
        - tryb gry:
            ~ 0 plansza 3x3 poziom trudności normal
            ~ 1 plansza 3x3 poziom trudności hard
            ~ 2 plansza 3x3 poziom trudności impopable
            ~ 3 plansza 9x9 poziom trudności normal
            ~ 4 plansza 9x9 poziom trudności hard
            ~ 5 plansza 9x9 poziom trudności impobaple

    Co robi bot:
        - zwraca numer części planszy (patrz linijka 11) w 
            której trzeba wykonać następny ruch, 0 jeśli gra jest 3x3
        - dodaje do planszy X lub O
        - jeśli bot nie może wykonać ruchu to zwróci -1
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Funkcja realizująca działanie bota w grze kółko-krzyżyk.
 *
 * @param plansza Wskaźnik na planszę do gry.
 * @param gracz Znak określający, kto wykonuje ruch: 'X' lub 'O'.
 * @param czesc Numer części planszy, w której ma się odbyć ruch.
 * @param tryb Tryb gry określający poziom trudności i rozmiar planszy.
 * @return Numer części planszy, w której trzeba wykonać następny ruch, 0 jeśli gra jest 3x3, -1 jeśli bot nie może wykonać ruchu.
 */
int bot(char **plansza, char gracz, int czesc, int tryb);

/**
 * @brief Funkcja realizująca działanie bota w trybie normalnym na planszy 3x3.
 *
 * @param plansza Wskaźnik na planszę do gry.
 * @param gracz Znak określający, kto wykonuje ruch: 'X' lub 'O'.
 * @param czesc Numer części planszy, w której ma się odbyć ruch.
 * @return Numer części planszy, w której trzeba wykonać następny ruch, 0 jeśli gra jest 3x3, -1 jeśli bot nie może wykonać ruchu.
 */
int bot_3x3_normal(char **plansza, char gracz, int czesc);

/**
 * @brief Funkcja realizująca działanie bota w trybie trudnym na planszy 3x3.
 *
 * @param plansza Wskaźnik na planszę do gry.
 * @param gracz Znak określający, kto wykonuje ruch: 'X' lub 'O'.
 * @param czesc Numer części planszy, w której ma się odbyć ruch.
 * @return Numer części planszy, w której trzeba wykonać następny ruch, 0 jeśli gra jest 3x3, -1 jeśli bot nie może wykonać ruchu.
 */
int bot_3x3_hard(char **plansza, char gracz, int czesc);

/**
 * @brief Funkcja realizująca działanie bota w trybie impopable na planszy 3x3.
 *
 * @param plansza Wskaźnik na planszę do gry.
 * @param gracz Znak określający, kto wykonuje ruch: 'X' lub 'O'.
 * @param czesc Numer części planszy, w której ma się odbyć ruch.
 * @return Numer części planszy, w której trzeba wykonać następny ruch, 0 jeśli gra jest 3x3, -1 jeśli bot nie może wykonać ruchu.
 */
int bot_3x3_impopable(char **plansza, char gracz, int czesc);

/**
 * @brief Funkcja realizująca działanie bota w trybie normalnym na planszy 9x9.
 *
 * @param plansza Wskaźnik na planszę do gry.
 * @param gracz Znak określający, kto wykonuje ruch: 'X' lub 'O'.
 * @param czesc Numer części planszy, w której ma się odbyć ruch.
 * @return Numer części planszy, w której trzeba wykonać następny ruch, 0 jeśli gra jest 3x3, -1 jeśli bot nie może wykonać ruchu.
 */
int bot_9x9_normal(char **plansza, char gracz, int czesc);

/**
 * @brief Funkcja realizująca działanie bota w trybie trudnym na planszy 9x9.
 *
 * @param plansza Wskaźnik na planszę do gry.
 * @param gracz Znak określający, kto wykonuje ruch: 'X' lub 'O'.
 * @param czesc Numer części planszy, w której ma się odbyć ruch.
 * @return Numer części planszy, w której trzeba wykonać następny ruch, 0 jeśli gra jest 3x3, -1 jeśli bot nie może wykonać ruchu.
 */
int bot_9x9_hard(char **plansza, char gracz, int czesc);

/**
 * @brief Funkcja realizująca działanie bota w trybie impopable na planszy 9x9.
 *
 * @param plansza Wskaźnik na planszę do gry.
 * @param gracz Znak określający, kto wykonuje ruch: 'X' lub 'O'.
 * @param czesc Numer części planszy, w której ma się odbyć ruch.
 * @return Numer części planszy, w której trzeba wykonać następny ruch, 0 jeśli gra jest 3x3, -1 jeśli bot nie może wykonać ruchu.
 */
int bot_9x9_impopable(char **plansza, char gracz, int czesc);

/**
 * @brief Funkcja realizująca działanie bota w trybie losowym na planszy 9x9.
 *
 * @param plansza Wskaźnik na planszę do gry.
 * @param gracz Znak określający, kto wykonuje ruch: 'X' lub 'O'.
 * @param czesc Numer części planszy, w której ma się odbyć ruch.
 * @return Numer części planszy, w której trzeba wykonać następny ruch, 0 jeśli gra jest 3x3, -1 jeśli bot nie może wykonać ruchu.
 */
int bot_9x9_random(char **plansza, char gracz, int czesc);
