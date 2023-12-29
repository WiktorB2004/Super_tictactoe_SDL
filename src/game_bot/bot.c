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
            której trzeba wykonać następny ruch, 0 jeśli gra jest 3x3
        -dodaje do planszy X lub O

*/
#include "../../include/game_bot.h"
#include "../../include/utils/bot_utils.h"

int bot(char **plansza, char gracz, int czesc, int tryb){
    int (*boty[])(char **, char, int) = {
        bot_3x3_normal,
        bot_3x3_hard,
        bot_3x3_impopable,
        bot_9x9_normal,
        bot_9x9_hard,
        bot_9x9_impopable
    };

    if(tryb < 0 || tryb > 5){
        //to się nie zdaży jeśli ktoś zaimplementuje sprawdzenie danych wejściowych
        puts("Podałeś zły tryb wojowniku");
        exit(EXIT_FAILURE);
    }

    int ans = (*boty[tryb])(plansza, gracz, czesc);
    return ans;
}

//TODO zmienić liczbę iteracji dla reszty botów (względem bota impopable)
int bot_9x9_normal(char **plansza, char gracz, int czesc);
int bot_9x9_hard(char **plansza, char gracz, int czesc);

int bot_9x9_impopable(char **plansza, char gracz, int czesc){
    node *v = create_node();
    v -> ruch.gracz = zmiana_gracza(gracz);

    //dla 9 planszy sprawdza kto wygrywa w poszczególnych planszach 
    char **nad_zwyciestwa = calloc(3, sizeof(char *));
    if(nad_zwyciestwa == NULL){
        puts("błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < 3; i++){
        nad_zwyciestwa[i] = calloc(3, sizeof(char));
        if(nad_zwyciestwa[i] == NULL){
            puts("błąd alokacji pamięci");
            exit(EXIT_FAILURE);
        }
    }
    uzupelnij_nad_zwyciestwa(plansza, nad_zwyciestwa);

    //początek tworzenia mcts
    for(int i = 0; i < 500; i++){
        //wybieram liścia
        node *selected = select(plansza, czesc, v);

        //wybranemu wierzchołkowi dodaje syna
        dodaj_syna(selected, plansza, czesc, gracz);

        //przeprowadzam symulacje dla syna
        symulate(selected, plansza, czesc);

        //updatuje informacje dla wierzchołków od syna do korzenia (v)
        unselect(selected, plansza, gracz);
    }

    //wybierz najlepszy ruch
    zmiana ruch = znajdz_opt(v);

    //zmianiam plansze
    plansza[ruch.x][ruch.y] = gracz;

    //pobieram dodatkową pamięć ram z chmury
    destruct_node(v);
    
    return znajdz_czesc(ruch);
}
