/*
    tutaj implementuje wszystkie funkcje pomocnicze do bota
*/

#include "../include/game_bot.h"
#include "../include/utils/bot_utils.h"

#define inf 1e9

vector_node *create_vector_node(char **plnasza, int czesc){
    vector_node *vector = malloc(sizeof(vector_node));
    vector -> size = 0;
    int cnt = 0;
    pair p = poczatek_czesci(czesc);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(plnasza[i + p.x][j + p.y] == ' ') cnt++;

    vector -> max_size = cnt;
    vector -> sons = malloc(cnt * sizeof(node*));
    if(vector -> sons == NULL){
        puts("błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < cnt; i++)
        vector -> sons[i] = NULL;

    return vector;
}

node *create_node(char **plansza, int czesc){
    node *wierzcholek = malloc(sizeof(node));
    if(wierzcholek == NULL){
        puts("błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
    if(mutex == NULL){
        puts("błąd alokajic pamięci");
        exit(EXIT_FAILURE);
    }


    wierzcholek -> mutex = mutex;
    if(pthread_mutex_init(mutex, NULL) != 0){
        puts("błąd inicjalizaji mutexa");
        exit(EXIT_FAILURE);
    }
    
    wierzcholek -> ruch.x = -1;
    wierzcholek -> ruch.y = -1;
    wierzcholek -> ruch.czesc = -1;
    wierzcholek -> ruch.gracz = '\0';

    wierzcholek -> parent = NULL;
    wierzcholek -> vec = create_vector_node(plansza, czesc);
    wierzcholek -> visit = 0;
    wierzcholek -> wins = 0;

    return wierzcholek;
}


void destruct_node(node *NODE){
    if(NODE -> vec != NULL) //nie jest liściem 
        destruct_vector_node(NODE -> vec);

    pthread_mutex_destroy(NODE -> mutex);
    free(NODE -> mutex);

    free(NODE);
}

void destruct_vector_node(vector_node *vector){
    for(int i = 0; i < vector -> size; i++)
        destruct_node(vector -> sons[i]);

    free(vector -> sons);
    free(vector);
}

void push_back(choosen_node *cn, node *new_node){
    cn -> v -> vec -> sons[cn -> idx] = new_node;
}

double uct(node *wierzcholek){
    if(wierzcholek -> visit == 0) return (double) inf;

    double uct = (double) wierzcholek -> wins / wierzcholek -> visit;
    uct += (double) sqrt(2) * sqrt(log(wierzcholek -> parent == NULL ? wierzcholek -> visit :
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
    int x = 0, o = 0;
    for(int i = 0; i < 3; i++){
        if(sub_plansza[i][0] == sub_plansza[i][1] &&
            sub_plansza[i][1] == sub_plansza[i][2] && sub_plansza[i][0] != ' '){
                if(sub_plansza[i][0] == 'X') x++;
                else o++;
            }
    }

    for(int j = 0; j < 3; j++){
        if(sub_plansza[0][j] == sub_plansza[1][j] &&
            sub_plansza[1][j] == sub_plansza[2][j] && sub_plansza[0][j] != ' '){
                if(sub_plansza[0][j] == 'X') x++;
                else o++;
            }
    }

    if(sub_plansza[0][0] == sub_plansza[1][1] &&
        sub_plansza[1][1] == sub_plansza[2][2] && sub_plansza[0][0] != ' '){
            if(sub_plansza[0][0] == 'X') x++;
            else o++;
        }


    if(sub_plansza[0][2] == sub_plansza[1][1] &&
        sub_plansza[1][1] == sub_plansza[2][0] && sub_plansza[0][2] != ' '){
            if(sub_plansza[0][2] == 'X') x++;
            else o++;
        }

    if(o > 0 && x > 0) return ' ';
    if(x > 0) return 'X';
    if(o > 0) return 'O';
    return ' ';
}

void uzupelnij_nad_zwyciestwa(char **plansza, char **nad_zwyciestwa){
    char **sub_plansza = allocate(3);

    for(int i = 0; i < 9; i++){
        pair p = poczatek_czesci(i);

        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                sub_plansza[j][k] = plansza[p.x + j][p.y + k];
        
        nad_zwyciestwa[i / 3][i % 3] = sprawdz_wynik(sub_plansza);
    }

    deallocate(sub_plansza, 3);
}

void update_nad_zwyciestwa(char **plansza, char **nad_zwyciestwa, int czesc){
    if(nad_zwyciestwa[czesc / 3][czesc % 3] != ' ') return;

    char **sub_plansza = allocate(3);
    pair p = poczatek_czesci(czesc);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            sub_plansza[i][j] = plansza[p.x + i][p.y + j];
    
    nad_zwyciestwa[czesc / 3][czesc % 3] = sprawdz_wynik(sub_plansza);

    deallocate(sub_plansza, 3);
}


int pelny(char **plansza, int czesc, node *v){
    int sajz = v -> vec -> size;
    int moge = 0;

    pair p = poczatek_czesci(czesc);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(plansza[p.x + i][p.y + j] == ' ') moge++;
    
    return sajz == moge;
}

choosen_node *Select(char **plansza, node *v, char **nad_zwyciestwa){
    pthread_mutex_lock(v -> mutex);
    //vector jest pełny można tylko wybrać syna
    if(v -> vec -> size == v -> vec -> max_size){
        pthread_mutex_unlock(v -> mutex);

        double best_score = 0;
        int idx_best = -1;
        for(int i = 0; i < v -> vec -> size; i++){
            if(v -> vec -> sons[i] == NULL || v -> vec -> sons[i] -> visit == 0){
                continue;
            }
            // if(v -> vec -> sons[i] -> parent != v){
            //     puts("oj");
            // }
            if(uct(v -> vec -> sons[i]) > best_score){
                best_score = uct(v -> vec -> sons[i]);
                idx_best = i;
            }
        }

        if(idx_best == -1){
            choosen_node *cn = malloc(sizeof(choosen_node));
            if(cn == NULL){
                puts("błąd alokacji pamięcji");
                exit(0);
            }
            
            cn -> idx = -1;
            cn -> v = v;

            return cn;
        }
        //!nie wybrano syna, ponieważ go sie nie da wybrać, więc nie ide w dół,
        //!pozostaje w nodzie, ale potem będe dla niego próbował dobrać syna 
        //!co się znów nie uda 
        
        node *son = v -> vec -> sons[idx_best];
        plansza[son -> ruch.x][son -> ruch.y] = son -> ruch.gracz;
        update_nad_zwyciestwa(plansza, nad_zwyciestwa, v -> ruch.czesc);

        return Select(plansza, son, nad_zwyciestwa);
    }

    //vector nie jest pełny można dodawać mu syna
    else{
        int add_idx = v -> vec -> size;
        v -> vec -> size++;
        pthread_mutex_unlock(v -> mutex);

        choosen_node *cn = malloc(sizeof(choosen_node));
        if(cn == NULL){
            puts("błąd alokacji pamięcji");
            exit(0);
        }
        
        cn -> idx = add_idx;
        cn -> v = v;

        return cn;
    }

    //żeby kompilator nie krzyczał że coś ni zwracam, to i tak nigdy się nie wykona
    return NULL;
}

// 0 jeśli się udało dodać syna, 1 jeśli się nie udało
int dodaj_syna(choosen_node *cn, char **plansza, char **nad_zwyciestwa){
    pair p = poczatek_czesci(cn -> v -> ruch.czesc);
    int nowa_czesc = -1;
    int x = -1, y = -1;
    int target = cn -> idx;

    for(int i = 0, idx = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(plansza[p.x + i][p.y + j] == ' ' && idx == target){
                x = p.x + i, y = p.y + j;
                nowa_czesc = i * 3 + j;
                idx++;
            }
            else if(plansza[p.x + i][p.y + j] == ' ') idx++;
    
    if(nowa_czesc == -1) 
        return 1;
    
    plansza[x][y] = zmiana_gracza(cn -> v -> ruch.gracz);
    update_nad_zwyciestwa(plansza, nad_zwyciestwa, cn -> v -> ruch.czesc);

    //wybrano już x i y, teraz czas dodać nowego syna
    node *new_node = create_node(plansza, nowa_czesc);
    new_node -> parent = cn -> v;

    zmiana ruch = {x, y, nowa_czesc, zmiana_gracza(cn -> v -> ruch.gracz)};
    new_node -> ruch = ruch;
    push_back(cn, new_node);

    if(cn -> v != new_node -> parent){
        puts("dkjfkd");
    }

    //zmiana planszy pod new_node
    // plansza[new_node -> ruch.x][new_node -> ruch.y] = new_node -> ruch.gracz;
    // update_nad_zwyciestwa(plansza, nad_zwyciestwa, cn -> v -> ruch.czesc); 
        
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
    char **matrix = allocate(9);
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            matrix[i][j] = plansza[i][j];
    
    char **wyniki_pol = allocate(3);

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
            deallocate(matrix, 9);
            deallocate(wyniki_pol, 3);

            return 1;
        }

        int opcja = rand() % ile_opcji;
        int stara_czesc = ruch.czesc;
        for(int i = 0, idx = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(matrix[p.x + i][p.y + j] == ' ' && opcja == idx){
                    ruch.x = p.x + i;
                    ruch.y = p.y + j;
                    ruch.czesc = i * 3 + j;
                    ruch.gracz = zmiana_gracza(ruch.gracz);
                    idx++;
                }
                else if(matrix[p.x + i][p.y + j] == ' ') idx++;
            }
        }

        matrix[ruch.x][ruch.y] = ruch.gracz;
        update_nad_zwyciestwa(matrix, wyniki_pol, stara_czesc);
    }


    if(remis(wyniki_pol)){
        deallocate(wyniki_pol, 3);
        deallocate(matrix, 9);

        return 1;
    }

    int wynik = 3 * (sprawdz_wynik(wyniki_pol) == gracz);
    deallocate(wyniki_pol, 3);
    deallocate(matrix, 9);

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
    if(v -> vec -> size == 0){
        ruch.czesc = -1;
        return ruch;
    }

    int best_score = 0;
    int best_idx = 0;
    for(int i = 0; i < v -> vec -> size; i++){
        if(v -> vec -> sons[i] -> visit > best_score){
            best_score = v -> vec -> sons[i] -> visit;
            best_idx = i;
        }
    }

    return v -> vec -> sons[best_idx] -> ruch;
}

void cout(char **plansza, int x){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < x; j++){
            if(plansza[i][j] == ' ') putchar('.');
            else putchar(plansza[i][j]);
        }
        putchar('\n');
    }
}

char **allocate(int x){
    char **matrix = malloc(x * sizeof(char *));
    if(matrix == NULL){
        puts("błąd alokacji pamięcji");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < x; i++){
        matrix[i] = malloc(x * sizeof(char));
        if(matrix[i] == NULL){
            puts("błąd alokacji pamięcji");
            exit(EXIT_FAILURE);
        }
    }

    return matrix;
}

void deallocate(char **matrix, int x){
    for(int i = 0; i < x; i++)
        free(matrix[i]);
    free(matrix);
}


