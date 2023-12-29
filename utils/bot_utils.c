/*
    tutaj implementuje wszystkie funkcje pomocnicze do bota
*/
#include "../include/game_bot.h"
#include "../include/utils/bot_utils.h"

#define inf 1e9

vector_node *create_vector_node(){
    vector_node *vector = malloc(sizeof(vector_node));
    vector -> size = 0;
    vector -> cap = 1;

    vector -> sons = malloc(sizeof(node*));
    if(vector -> sons == NULL){
        puts("błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }

    return vector;
}

node *create_node(){
    node *wierzcholek = malloc(sizeof(node));
    if(wierzcholek == NULL){
        puts("błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }

    wierzcholek -> ruch.x = -1;
    wierzcholek -> ruch.y = -1;
    wierzcholek -> ruch.gracz = '\0';

    wierzcholek -> parent = NULL;
    wierzcholek -> vector_node = create_vector_node();
    wierzcholek -> visit = 0;
    wierzcholek -> wins = 0;

    return wierzcholek;
}


void destruct_node(node *NODE){
    if(NODE -> vector_node != NULL) //nie jest liściem 
        destruct_vector_node(NODE -> vector_node);
    free(NODE);
}

void destruct_vector_node(vector_node *vector){
    for(int i = 0; i < vector -> size; i++)
        destruct_node(vector -> sons[i]);

    free(vector -> sons);
    free(vector);
}

void push_back(vector_node *vector, node *new_node){
    if(vector -> size + 1 == vector -> cap){
        void **sons2 = realloc(vector -> sons, vector -> cap * 2.2 * sizeof(node*));
        if(sons2 == NULL){
            puts("błąd alokacji pamięci");
            exit(EXIT_FAILURE);
        }

        vector -> sons = sons2;
        vector -> cap *= 2.2;
    }

    vector -> sons[vector -> size] = new_node;
    vector -> size++;
}

double uct(node *wierzcholek){
    if(wierzcholek -> visit == 0) return (double) inf;

    double uct = (double) wierzcholek -> wins / wierzcholek -> visit;
    uct += (double) sqrt(2) * sqrt(ln(wierzcholek -> parent == NULL ? wierzcholek -> visit :
        wierzcholek -> parent -> visit) / wierzcholek -> visit);
    return uct;
}

char zmiana_gracza(char gracz){
    if(gracz == 'O') return 'X';
    return 'O';
}

int znajdz_czesc(zmiana ruch){
    int ans = 0;
    ans += (ruch.x / 3) * 3;
    ans += (ruch.y / 3);

    return ans;
}

pair poczatek_czesci(int czesc){
    pair p;
    p.x = (czesc / 3) * 3;
    p.y = (czesc % 3) * 3;

    return p;
}

char sprawdz_wynik(char **sub_plansza){
    for(int i = 0; i < 3; i++){
        if(sub_plansza[i][0] == sub_plansza[i][1] &&
            sub_plansza[i][1] == sub_plansza[i][2]) return sub_plansza[i][0];
    }

    for(int j = 0; j < 3; j++){
        if(sub_plansza[0][j] == sub_plansza[1][j] &&
            sub_plansza[1][j] == sub_plansza[2][j]) return sub_plansza[0][j];
    }

    if(sub_plansza[0][0] == sub_plansza[1][1] &&
        sub_plansza[1][1] == sub_plansza[2][2]) return sub_plansza[0][0];

    if(sub_plansza[0][2] == sub_plansza[1][1] &&
        sub_plansza[1][1] == sub_plansza[3][0]) return sub_plansza[0][2];

    return ' ';
}

void uzupelnij_nad_zwyciestwa(char **plansza, char **nad_zwyciestwa){
    char **sub_plansza = malloc(3 * sizeof(char *));
    if(sub_plansza == NULL){
        puts("błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < 3; i++){
        sub_plansza[i] = malloc(3 * sizeof(char));
        if(sub_plansza[i] == NULL){
            puts("błąd alokacji pamięci");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < 9; i++){
        pair p = poczatek_czesci(i);
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                sub_plansza[j][k] = plansza[p.x + j][p.y + k];
        
        nad_zwyciestwa[p.x][p.y] = sprawdz_wynik(sub_plansza);
    }

    for(int i = 0; i < 3; i++) 
        free(sub_plansza[i]);
    free(sub_plansza);
}

void update_nad_zwyciestwa(char **plnasza, char **nad_zwyciestwa, int czesc){
    char **sub_plansza = malloc(3 * sizeof(char *));
    if(sub_plansza == NULL){
        puts("błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < 3; i++){
        sub_plansza[i] = malloc(3 * sizeof(char));
        if(sub_plansza[i] == NULL){
            puts("błąd alokacji pamięci");
            exit(EXIT_FAILURE);
        }
    }

    pair p = poczatek_czesci(czesc);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            sub_plansza[i][j] = plnasza[p.x + i][p.y + j];
    
    nad_zwyciestwa[czesc / 3][czesc % 3] = sprawdz_wynik(sub_plansza);

    for(int i = 0; i < 3; i++) 
        free(sub_plansza[i]);
    free(sub_plansza);
}


int pelny(char **plansza, int czesc, node *v){
    int sajz = v -> vector_node -> size;
    int moge = 0;

    pair p = poczatek_czesci(czesc);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(plansza[p.x + i][p.y + j] == ' ') moge++;
    
    return sajz < moge;
}

node *select(char **plansza, int czesc, node *v){
    //vector jest pełny można tylko wybrać syna
    if(pelny(plansza, czesc, v)){
        int best_score = 0, idx_best = 0;
        for(int i = 0; i < 9; i++){
            if(uct(v -> vector_node -> sons[i]) > best_score){
                best_score = uct(v -> vector_node -> sons[i]);
                idx_best = i;
            }
        }
        
        node *son = v -> vector_node -> sons[idx_best];
        plansza[son -> ruch.x][son -> ruch.y] = son -> ruch.gracz;

        return select(plansza, znajdz_czesc(son -> ruch), son);
    }

    //vector nie jest pełny można dodawać mu syna
    else{
        return v;
    }

    //żeby kompilator nie krzyczał że coś ni zwracam, to i tak nigdy się nie wykona
    return NULL;
}

