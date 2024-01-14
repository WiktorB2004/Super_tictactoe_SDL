#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

typedef struct zmiana
{
    int x;
    int y;
    int czesc;
    char gracz;
} zmiana;

typedef struct pair
{
    int x;
    int y;
} pair;

typedef struct vector_node
{
    int size;
    int max_size;
    struct node **sons; // wskaźnik na tablice wskaźników, które wskazują na synów typu node
} vector_node;

typedef struct node
{
    struct node *parent;
    vector_node *vec;

    zmiana ruch;
    int visit;
    int wins;
    pthread_mutex_t *mutex;
} node;

typedef struct argument{
    char **plansza;
    char **nad_zwyciestwa;
    char gracz;
    int czesc;
    node *v;

} argument;

typedef struct choosen_node{
    node *v;
    int idx;
} choosen_node;

// dane
node *create_node(char **plansza, int czesc);
vector_node *create_vector_node(char **plansza, int czesc);
void destruct_node(node *NODE);
void destruct_vector_node(vector_node *vector);
void push_back(choosen_node *cn, node *new_node);

// funkcje do sprawdzania wyniku potyczek na planszy
char sprawdz_wynik(char **sub_plansza);
void uzupelnij_nad_zwyciestwa(char **plansza, char **nad_zwyciestwa);
void update_nad_zwyciestwa(char **plnasza, char **nad_zwyciestwa, int czesc);

// funkcje do selection
double uct(node *wierzcholek);
int pelny(char **plansza, int czesc, node *v);
choosen_node *Select(char **plansza, node *v, char **nad_zwyciestwa);
int remis(char **nad_zwyciestwa);

// funkcje do expansion
int dodaj_syna(choosen_node *v, char **plansza, char **nad_zwyciestwa);

// funkcje do simulation
int symulate(node *v, char **plansza, char **nad_zwyciestwa, char gracz);

// funkcje do backpropagation
void unselect(node *v, char **plansza, int wynik, char **nad_zwyciestwa);

// pomieszane funkcje
char zmiana_gracza(char gracz);
int znajdz_czesc(zmiana ruch);
pair poczatek_czesci(int czesc);
zmiana znajdz_opt(node *v);

//wypisywanie
void cout(char **plansza, int x);

//alokacja i dealokacja 
char **allocate(int x);
void deallocate(char **matrix, int x);