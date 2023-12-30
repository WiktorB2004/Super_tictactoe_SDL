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
    wierzcholek -> ruch.czesc = -1;
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
        node **sons2 = realloc(vector -> sons, vector -> cap * 2.2 * sizeof(node*));
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

node *select(char **plansza, node *v, char **nad_zwyciestwa){
    //vector jest pełny można tylko wybrać syna
    if(pelny(plansza, v -> ruch.czesc, v)){
        int best_score = 0, idx_best = -1;
        for(int i = 0; i < v -> vector_node -> size; i++){
            if(uct(v -> vector_node -> sons[i]) > best_score){
                best_score = uct(v -> vector_node -> sons[i]);
                idx_best = i;
            }
        }

        if(idx_best == -1) return v;
        //!nie wybrano syna, ponieważ go sie nie da wybrać, więc nie ide w dół,
        //!pozostaje w nodzie, ale potem będe dla niego próbował dobrać syna 
        //!co się znów nie uda 
        
        node *son = v -> vector_node -> sons[idx_best];
        plansza[son -> ruch.x][son -> ruch.y] = son -> ruch.gracz;

        pair p = poczatek_czesci(v -> ruch.czesc);
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

        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                sub_plansza[i][j] = plansza[p.x + i][p.y + j];

        nad_zwyciestwa[v -> ruch.czesc / 3][v -> ruch.czesc % 3] = sprawdz_wynik(sub_plansza);
        
        for(int i = 0; i < 3; i++)
            free(sub_plansza[i]);
        free(sub_plansza);

        return select(plansza, son, nad_zwyciestwa);
    }

    //vector nie jest pełny można dodawać mu syna
    else{
        return v;
    }

    //żeby kompilator nie krzyczał że coś ni zwracam, to i tak nigdy się nie wykona
    return NULL;
}

// 0 jeśli się udało dodać syna, 1 jeśli się nie udało
int dodaj_syna(node *v, char **plansza, char **nad_zwyciestwa){
    pair p = poczatek_czesci(v -> ruch.czesc);
    int nowa_czesc = -1;
    int x = -1, y = -1;

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(plansza[p.x + i][p.y + j] == ' '){
                x = p.x + 1, y = p.y + j;
                nowa_czesc = i * 3 + j;
            }
    
    if(nowa_czesc == -1) return 1;

    //wybrano już x i y, teraz czas dodać nowego syna
    node *new_node = create_node();
    new_node -> parent = v;

    zmiana ruch = {x, y, nowa_czesc, zmiana_gracza(v -> ruch.gracz)};
    new_node -> ruch = ruch;
    
    push_back(v -> vector_node, new_node);

    //zmiana planszy pod new_node
    plansza[new_node -> ruch.x][new_node -> ruch.y] = new_node -> ruch.gracz;
    pair p = poczatek_czesci(v -> ruch.czesc);
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

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            sub_plansza[i][j] = plansza[p.x + i][p.y + j];

    nad_zwyciestwa[v -> ruch.czesc / 3][v -> ruch.czesc % 3] = sprawdz_wynik(sub_plansza);
        
    for(int i = 0; i < 3; i++)
        free(sub_plansza[i]);
    free(sub_plansza);

    return 0;
}

//nikt nie zwyciężył, a wszystki pola są zapełnione
int remis(char **nad_zwyciestwa){
    if(sprawdz_wynik(nad_zwyciestwa) != ' ') return 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(nad_zwyciestwa[i][j] == ' ') return 0;
    
    return 1;
}

// 0: gracz przegrał, 1: gracz zremisował, 2: gracz wygrał
int symulate(node *v, char **plansza, char **nad_zywciestwa, char gracz){
    char matrix[9][9]; //kopia planszy
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            matrix[i][j] = plansza[i][j];
    
    char **wyniki_pol = malloc(3 * sizeof(char *));
    if(wyniki_pol == NULL){
        pust("błąd alokacji pamięcji");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 3; i++){
        wyniki_pol[i] = malloc(3 * sizeof(char));
        if(wyniki_pol[i] == NULL){
            puts("błąd alokacji pamięcji");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            wyniki_pol[i][j] = nad_zywciestwa[i][j];

    zmiana ruch = v -> ruch;
    while(sprawdz_wynik(wyniki_pol) == ' ' && !remis(wyniki_pol)){
        pair p = poczatek_czesci(ruch.czesc);
        int ile_opcji = 0;

        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(matrix[p.x + i][p.y + j] == ' ') ile_opcji++;
        
        if(ile_opcji == 0){
            //nie mam gdzie postawić znaku więc definiuje taką sytuacje jako remis
            for(int i = 0; i < 3; i++) free(wyniki_pol[i]);
            free(wyniki_pol);

            return 1;
        }

        int opcja = rand() % ile_opcji;
        for(int i = 0, idx = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(matrix[p.x + i][p.y + j] == ' ' && opcja == idx){
                    ruch.x = p.x + i;
                    ruch.y = p.y + j;
                    ruch.czesc = i * 3 + j;
                    ruch.gracz = zmiana_gracza(ruch.gracz);
                }
                else if(matrix[i][j] == ' ') idx++;
            }
        }

        matrix[ruch.x][ruch.y] = ruch.gracz;
        char **sub_plansza = malloc(3 * sizeof(char *));
        if(sub_plansza == NULL){
            puts("błąd alokacji pamięcji");
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < 3; i++){
            sub_plansza[i] = malloc(3 * sizeof(char));
            if(sub_plansza[i] == NULL){
                puts("błąd alokacji pamięcji");
                exit(EXIT_FAILURE);
            }
        }

        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                sub_plansza[i][j] = matrix[p.x + i][p.y + j];
        
        int czesc = znajdz_czesc(ruch);
        wyniki_pol[czesc / 3][czesc % 3] = sprawdz_wynik(sub_plansza);

        for(int i = 0; i < 3; i++) free(sub_plansza[i]);
        free(sub_plansza);
    }


    if(remis(wyniki_pol)){
        for(int i = 0; i < 3; i++) free(wyniki_pol[i]);
        free(wyniki_pol);
        return 1;
    }

    int wynik = 2 * (sprawdz_wynik(wyniki_pol) == gracz);
    for(int i = 0; i < 3; i++) free(wyniki_pol[i]);
    free(wyniki_pol);

    return wynik;
}

void unselect(node *v, char **plansza, int wynik, char **nad_zwyciestwa){
    if(v -> parent == NULL){
        v -> visit++;
        v -> wins += wynik;
        return;
    }

    plansza[v -> ruch.x][v -> ruch.y] = ' ';
    update_nad_zwyciestwa(plansza, nad_zwyciestwa, znajdz_czesc(v -> ruch));

    v -> visit++;
    v -> wins += wynik;

    unselect(v -> parent, plansza, wynik, nad_zwyciestwa);
}

zmiana znajdz_opt(node *v){
    zmiana ruch;
    if(v -> vector_node -> size == 0){
        ruch.czesc = -1;
        return ruch;
    }

    int best_score = 0, best_idx = 0;
    for(int i = 0; i < v -> vector_node -> size; i++){
        if(uct(v -> vector_node -> sons[i]) > best_score){
            best_score = uct(v -> vector_node -> sons[i]);
            best_idx = i;
        }
    }

    return v -> vector_node -> sons[best_idx] -> ruch;
}

