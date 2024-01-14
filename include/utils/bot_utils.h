#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

/**
 * @brief Struktura przechowująca informacje o ruchu w grze.
 */
typedef struct zmiana
{
    int x;       /**< Współrzędna X ruchu */
    int y;       /**< Współrzędna Y ruchu */
    int czesc;   /**< Numer części planszy w którym ma się odbyć następny ruch */
    char gracz;  /**< Symbol gracza (X lub O) */
} zmiana;

/**
 * @brief Struktura przechowująca współrzędne na planszy.
 */
typedef struct pair
{
    int x;  /**< Współrzędna X */
    int y;  /**< Współrzędna Y */
} pair;

/**
 * @brief Struktura przechowująca dynamiczną tablicę wskaźników na synów węzła.
 */
typedef struct vector_node
{
    int size;                /**< Aktualny rozmiar tablicy */
    int max_size;            /**< Maksymalny rozmiar tablicy */
    struct node **sons;      /**< Wskaźnik na tablicę wskaźników na synów typu node */
} vector_node;

/**
 * @brief Struktura reprezentująca węzeł drzewa poszukiwań Monte Carlo.
 */
typedef struct node
{
    struct node *parent;         /**< Wskaźnik na rodzica węzła */
    vector_node *vec;            /**< Wskaźnik na dynamiczną tablicę wskaźników na synów typu node */
    zmiana ruch;                 /**< Informacje o ruchu */
    int visit;                   /**< Liczba odwiedzin węzła */
    int wins;                    /**< Liczba zwycięstw w symulacjach związanych z węzłem */
    pthread_mutex_t *mutex;      /**< Wskaźnik na muteks dla bezpiecznej synchronizacji węzłów w wielowątkowym środowisku */
} node;

/**
 * @brief Struktura przechowująca dane dla funkcji głównej.
 */
typedef struct argument
{
    char **plansza;   /**< Wskaźnik na planszę gry */
    char **nad_zwyciestwa;  /**< Wskaźnik na pomocniczą planszę do sprawdzania zwycięstwa */
    char gracz;       /**< Symbol aktualnego gracza */
    int czesc;        /**< Numer części planszy w którym ma się odbyć ruch*/
    node *v;          /**< Wskaźnik na korzeń drzewa poszukiwań Monte Carlo */
} argument;

/**
 * @brief Struktura przechowująca informacje o wybranym węźle.
 */
typedef struct choosen_node
{
    node *v;  /**< Wskaźnik na wybrany węzeł */
    int idx;   /**< Indeks wybranego węzła */
} choosen_node;

/** @name Funkcje inicjalizujące i usuwające struktury danych */
///@{
node *create_node(char **plansza, int czesc);
vector_node *create_vector_node(char **plansza, int czesc);
void destruct_node(node *NODE);
void destruct_vector_node(vector_node *vector);
void push_back(choosen_node *cn, node *new_node);
///@}

/** @name Funkcje sprawdzające wyniki potyczek na planszy */
///@{
char sprawdz_wynik(char **sub_plansza);
void uzupelnij_nad_zwyciestwa(char **plansza, char **nad_zwyciestwa);
void update_nad_zwyciestwa(char **plnasza, char **nad_zwyciestwa, int czesc);
///@}

/** @name Funkcje do selection */
///@{
double uct(node *wierzcholek);
int pelny(char **plansza, int czesc, node *v);
choosen_node *Select(char **plansza, node *v, char **nad_zwyciestwa);
int remis(char **nad_zwyciestwa);
///@}

/** @name Funkcje do expansion */
///@{
int dodaj_syna(choosen_node *v, char **plansza, char **nad_zwyciestwa);
///@}

/** @name Funkcje do simulation */
///@{
int symulate(node *v, char **plansza, char **nad_zwyciestwa, char gracz);
///@}

/** @name Funkcje do backpropagation */
///@{
void unselect(node *v, char **plansza, int wynik, char **nad_zwyciestwa);
///@}

/** @name Funkcje pomocnicze */
///@{
char zmiana_gracza(char gracz);
int znajdz_czesc(zmiana ruch);
pair poczatek_czesci(int czesc);
zmiana znajdz_opt(node *v);
///@}

/** @name Funkcje wypisywania (do debugowania)*/
///@{
void cout(char **plansza, int x);
///@}

/** @name Funkcje alokacji i dealokacji pamięci */
///@{
char **allocate(int x);
void deallocate(char **matrix, int x);
///@}
