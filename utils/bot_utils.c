/*
    tutaj implementuje wszystko co potrzebuje do bota
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

void zmiana_gracza(char *gracz){
    if(*gracz == 'O') *gracz = 'X';
    else *gracz = 'O';
}

int znajdz_czesc(zmiana ruch){
    int ans = 0;
    for(int x1 = 0, x2 = 3; x1 < 9; x1 += 3, x2 += 3)
        for(int y1 = 0, y2 = 3; y1 < 9; y1 += 3, y2 += 3, ans++)
            if(x1 <= ruch.x && ruch.x < x2 && y1 <= ruch.y && ruch.y < y2) return ans;
}





