/*
    Implementacja botów o trzech stopniach trudności i w dwruch 
    wariantach rozmiaru planszy

    bot przyjmuje argurmenty:
        -wskaźnik na plansze do gry
        -kto wykonuje ruch: X czy O
        -w której części ma się odbyć ruch, jeśli plansza jest 3x3 to 
            podaj argument = 0, jeśli plansza jest 9x9 to indeksuje części:
            0 | 1 | 2
            ----------
            3 | 4 | 5
            ----------
            5 | 7 | 8
        - tryb gry:
            ~ 0 plansza 3x3 poziom trudności normal
            ~ 1 plansza 3x3 poziom trudności hard
            ~ 2 plnasza 3x3 poziom trudności impopable
            ~ 3 plansza 9x9 poziom trudności normal
            ~ 4 plnasza 9x9 poziom trudności hard
            ~ 5 plnasza 9x9 poziom trudności impobaple

    co robi bot:
        -zwraca numer części planszy (patrz linijka 11) w 
            której trzeba wykonać następny ruch, 0 jeśli grajest 3x3
        -dodaje do planszy X lub O
        -jeśli bot nie może wykonać ruchu to zrwóci -1 !!!!!!!

*/

#pragma once
#include <stdio.h>
#include <stdlib.h>

int bot(char **plansza, char gracz, int czesc, int tryb);

int bot_3x3_normal(char **plansza, char gracz, int czesc);
int bot_3x3_hard(char **plansza, char gracz, int czesc);
int bot_3x3_impopable(char **plansza, char gracz, int czesc);

int bot_9x9_normal(char **plansza, char gracz, int czesc);
int bot_9x9_hard(char **plansza, char gracz, int czesc);
int bot_9x9_impopable(char **plansza, char gracz, int czesc);

int bot_9x9_random(char **plansza, char gracz, int czesc);