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
        -jeśli bot nie może wykonać ruchu to zrwóci -1 !!!!!!!

*/
#include "../../include/game_bot.h" 
#include "../../include/utils/bot_utils.h"

#define iteracje_normal 500
#define iteracje_hard 5000
#define iteracje_impopable 250000

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

int bot_9x9_normal(char **plansza, char gracz, int czesc){
    node *v = create_node();
    v -> ruch.gracz = zmiana_gracza(gracz);
    v -> ruch.czesc = czesc; //czesc mówi w której części ma się odbyć następny ruch 

    //dla 9 planszy sprawdza kto wygrywa w poszczególnych planszach 
    char **nad_zwyciestwa = allocate(3);
    uzupelnij_nad_zwyciestwa(plansza, nad_zwyciestwa);

    //początek tworzenia mcts
    for(int i = 0; i < iteracje_normal; i++){
        //wybieram liścia
        node *selected = Select(plansza, v, nad_zwyciestwa);

        //wybranemu wierzchołkowi dodaje syna i ustawia plansze pod niego 
        node *new_selected;
        if(dodaj_syna(selected, plansza, nad_zwyciestwa)){
            //nie udało sie dodać syna, więc będe robił symulacje dla selected
            new_selected = selected;
        }
        else{
            //udało sie dodać syna, więc robie symulacje dla nowo dodanego syna, który jest 
            //oczywiście na końcu vectora
            new_selected = selected -> vec -> sons[selected -> vec -> size -1];
        }

        //przeprowadzam symulacje dla syna/ojca i mówie czy 
        //wygrał/zremisował/przegrał gracz (ten z argumentu funcji)
        int wynik = symulate(new_selected, plansza, nad_zwyciestwa, gracz);

        //updatuje informacje dla wierzchołków od syna do korzenia (v)
        unselect(new_selected, plansza, wynik, nad_zwyciestwa);
    }

    //wybierz najlepszy ruch
    zmiana ruch = znajdz_opt(v);
    if(ruch.czesc == -1){
        destruct_node(v); //nie mogę wykonać jakiegokolwiek ruchu
        return -1;
    }

    //zmianiam plansze
    plansza[ruch.x][ruch.y] = gracz;

    //pobieram dodatkową pamięć ram z chmury
    destruct_node(v);
    
    return ruch.czesc;
}

int bot_9x9_hard(char **plansza, char gracz, int czesc){
    node *v = create_node();
    v -> ruch.gracz = zmiana_gracza(gracz);
    v -> ruch.czesc = czesc; //czesc mówi w której części ma się odbyć następny ruch 

    //dla 9 planszy sprawdza kto wygrywa w poszczególnych planszach 
    char **nad_zwyciestwa = allocate(3);
    uzupelnij_nad_zwyciestwa(plansza, nad_zwyciestwa);

    //początek tworzenia mcts
    for(int i = 0; i < iteracje_hard; i++){
        //wybieram liścia
        node *selected = Select(plansza, v, nad_zwyciestwa);

        //wybranemu wierzchołkowi dodaje syna i ustawia plansze pod niego 
        node *new_selected;
        if(dodaj_syna(selected, plansza, nad_zwyciestwa)){
            //nie udało sie dodać syna, więc będe robił symulacje dla selected
            new_selected = selected;
        }
        else{
            //udało sie dodać syna, więc robie symulacje dla nowo dodanego syna, który jest 
            //oczywiście na końcu vectora
            new_selected = selected -> vec -> sons[selected -> vec -> size -1];
        }

        //przeprowadzam symulacje dla syna/ojca i mówie czy 
        //wygrał/zremisował/przegrał gracz (ten z argumentu funcji)
        int wynik = symulate(new_selected, plansza, nad_zwyciestwa, gracz);

        //updatuje informacje dla wierzchołków od syna do korzenia (v)
        unselect(new_selected, plansza, wynik, nad_zwyciestwa);
    }

    //wybierz najlepszy ruch
    zmiana ruch = znajdz_opt(v);
    if(ruch.czesc == -1){
        destruct_node(v); //nie mogę wykonać jakiegokolwiek ruchu
        return -1;
    }

    //zmianiam plansze
    plansza[ruch.x][ruch.y] = gracz;

    //pobieram dodatkową pamięć ram z chmury
    destruct_node(v);
    
    return ruch.czesc;
}

int bot_9x9_impopable(char **plansza, char gracz, int czesc){
    node *v = create_node();
    v -> ruch.gracz = zmiana_gracza(gracz);
    v -> ruch.czesc = czesc; //czesc mówi w której części ma się odbyć następny ruch 

    //dla 9 planszy sprawdza kto wygrywa w poszczególnych planszach 
    char **nad_zwyciestwa = allocate(3);
    uzupelnij_nad_zwyciestwa(plansza, nad_zwyciestwa);

    //początek tworzenia mcts
    for(int i = 0; i < iteracje_impopable; i++){
        //wybieram liścia
        node *selected = Select(plansza, v, nad_zwyciestwa);

        //wybranemu wierzchołkowi dodaje syna i ustawia plansze pod niego 
        node *new_selected;
        if(dodaj_syna(selected, plansza, nad_zwyciestwa)){
            //nie udało sie dodać syna, więc będe robił symulacje dla selected
            new_selected = selected;
        }
        else{
            //udało sie dodać syna, więc robie symulacje dla nowo dodanego syna, który jest 
            //oczywiście na końcu vectora
            new_selected = selected -> vec -> sons[selected -> vec -> size -1];
        }

        //przeprowadzam symulacje dla syna/ojca i mówie czy 
        //wygrał/zremisował/przegrał gracz (ten z argumentu funcji)
        int wynik = symulate(new_selected, plansza, nad_zwyciestwa, gracz);

        //updatuje informacje dla wierzchołków od syna do korzenia (v)
        unselect(new_selected, plansza, wynik, nad_zwyciestwa);
    }

    //wybierz najlepszy ruch
    zmiana ruch = znajdz_opt(v);
    if(ruch.czesc == -1){
        destruct_node(v); //nie mogę wykonać jakiegokolwiek ruchu
        return -1;
    }

    //zmianiam plansze
    plansza[ruch.x][ruch.y] = gracz;

    //pobieram dodatkową pamięć ram z chmury
    destruct_node(v);
    
    return ruch.czesc;
}

int bot_9x9_random(char **plansza, char gracz, int czesc){
    pair p = poczatek_czesci(czesc);

    int ile_opcji = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(plansza[p.x + i][p.y + j] == ' ') ile_opcji++;
    
    if(ile_opcji == 0) return -1;
    int wybieram = rand() % ile_opcji;
    zmiana ruch;

    for(int i = 0, idx = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(plansza[p.x + i][p.y + j] == ' ' && wybieram == idx){
                ruch.x = p.x + i;
                ruch.y = p.y + j;
                ruch.czesc = i * 3 + j;
                idx++;
            }
            else if(plansza[p.x + i][p.y + j] == ' ') idx++;
        }
    }

    plansza[ruch.x][ruch.y] = gracz;
    return ruch.czesc;
}


//bez tego nie chce się kompilować
int bot_3x3_normal(char **plansza, char gracz, int czesc){
    return 0;
}
int bot_3x3_hard(char **plansza, char gracz, int czesc){
    return 0;
}
int bot_3x3_impopable(char **plansza, char gracz, int czesc){
    return 0;
}
