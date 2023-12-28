#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct zmiana{
    int x;
    int y;
    char gracz;
} zmiana;

typedef struct vector_node{
    int size;
    int cap;
    node **sons; //wskaźnik na tablice wskaźników, które wskazują na synów typu node
} vector_node;

typedef struct node{
    node *parent;
    vector_node *vector_node;

    zmiana ruch; 
    int visit;
    int wins;
} node;

vector_node *create_vector_node();
node *create_node();
void destruct_node(node *NODE);
void destruct_vector_node(vector_node *vector);
void push_back(vector_node *vector, node *new_node);
double uct(node *wierzcholek);
void zmiana_gracza(char *gracz);
int znajdz_czesc(zmiana ruch);

//TODO
node *select(char **plansza, int czesc, node *v, char gracz);
void dodaj_syna(node *v, char **plansza, int czesc, char gracz);
void symulate(node *v, char **plansza, int czesc);
void unselect(node *v, char **plansza, char gracz);
zmiana znajdz_opt(node *v);