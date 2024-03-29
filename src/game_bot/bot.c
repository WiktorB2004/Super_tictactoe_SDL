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
#include "../../include/gameplay.h"

#define iteracje_normal 2500
#define iteracje_hard 25000
#define iteracje_impopable 2500000
#define thread_no 8

pthread_mutex_t lock_cnt, stop_malloc;
int liczba_iteracji, cel_liczby_iteracji;

int bot(Game *game, int czesc, int tryb)
{
    int (*boty[])(Game *, int) = {
        bot_3x3_normal,
        bot_3x3_hard,
        bot_3x3_impopable,
        bot_9x9_normal,
        bot_9x9_hard,
        bot_9x9_impopable};

    if (tryb < 0 || tryb > 5)
    {
        // to się nie zdaży jeśli ktoś zaimplementuje sprawdzenie danych wejściowych
        puts("Podałeś zły tryb wojowniku");
        exit(EXIT_FAILURE);
    }

    // inicjalizacja mutexa na malloca
    if (pthread_mutex_init(&stop_malloc, NULL) != 0)
    {
        puts("błąd inicjalizaji mutexa");
        exit(EXIT_FAILURE);
    }

    if(czesc == -1)
    {
        for(int i = 0; i < 9; i++)
        {
            if(game->board[i]->status == IN_PROGRESS)
            {
                czesc = i;
                break;
            }
        }
    }

    int ans = (*boty[tryb])(game, czesc);

    // deaktywacja mutexa na malloca
    pthread_mutex_destroy(&stop_malloc);

    return ans;
}

void *watek(void *ARG)
{
    while (1)
    {
        pthread_mutex_lock(&lock_cnt);
        if (liczba_iteracji >= cel_liczby_iteracji)
        {
            pthread_mutex_unlock(&lock_cnt);
            break;
        }
        liczba_iteracji++;
        pthread_mutex_unlock(&lock_cnt);

        // iteracja
        argument *arg = (argument *)ARG;

        // wybieram liścia
        choosen_node *selected = Select(arg->plansza, arg->v, arg->nad_zwyciestwa);

        // wybranemu wierzchołkowi dodaje syna i ustawia plansze pod niego
        node *new_selected;
        if (dodaj_syna(selected, arg->plansza, arg->nad_zwyciestwa))
        {
            // nie udało sie dodać syna, więc będe robił symulacje dla ojca
            new_selected = selected->v;
        }
        else
        {
            // udało sie dodać syna, więc robie symulacje dla syna
            new_selected = selected->v->vec->sons[selected->idx];
        }

        // przeprowadzam symulacje dla syna/ojca i mówie czy
        // wygrał/zremisował/przegrał gracz (ten z argumentu funcji)
        int wynik = symulate(new_selected, arg->plansza, arg->nad_zwyciestwa, arg->gracz);

        // updatuje informacje dla wierzchołków od syna do korzenia (v)
        unselect(new_selected, arg->plansza, wynik, arg->nad_zwyciestwa);
        free(selected);
        // koniec iteracji
    }
}

int make_mcts(Game *game, int czesc)
{
    // zamiana game -> plansza i nadzwyciestwa
    char **plansza = allocate(9);
    char **nad_zywciestwa = allocate(3);
    char gracz = (game->turn == 0 ? 'O' : 'X');

    for (int i = 0; i < 9; i++)
    {
        char wynik = game->board[i]->status;
        if (wynik == X_WON)
            nad_zywciestwa[i / 3][i % 3] = 'X';
        else if (wynik == O_WON)
            nad_zywciestwa[i / 3][i % 3] = 'O';
        else
            nad_zywciestwa[i / 3][i % 3] = ' ';
    }

    for (int c = 0; c < 9; c++)
    {
        pair p = poczatek_czesci(c);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int w = game->board[c]->value[i][j];
                if (w == O)
                    plansza[p.x + i][p.y + j] = 'O';
                else if (w == X)
                    plansza[p.x + i][p.y + j] = 'X';
                else
                    plansza[p.x + i][p.y + j] = ' ';
            }
        }
    }
    // koniec zamiany

    // sprawdzenie czy da sie w ogóle zrobić ruch
    pair p = poczatek_czesci(czesc);
    int moge = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (plansza[p.x + i][p.y + j] == ' ')
                moge++;

    if (moge == 0)
    {
        printf("niemoge xd\n");
        // nie mam jak dokonać ruchu, zwracam -1
        deallocate(plansza, 9);
        deallocate(nad_zywciestwa, 3);
        return -1;
    }

    // początek normalnego kodu
    node *v = create_node(plansza, czesc);
    v->ruch.gracz = zmiana_gracza(gracz);
    v->ruch.czesc = czesc;

    // torzenie wątków
    pthread_t thread[thread_no];
    argument arg[thread_no];
    for (int i = 0; i < thread_no; i++)
    {
        char **_plansza = allocate(9);
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                _plansza[i][j] = plansza[i][j];
        arg[i].plansza = _plansza;

        char **_nad_zwyciestwa = allocate(3);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                _nad_zwyciestwa[i][j] = nad_zywciestwa[i][j];

        arg[i].nad_zwyciestwa = _nad_zwyciestwa;

        arg[i].czesc = czesc;
        arg[i].gracz = gracz;
        arg[i].v = v;
    }

    if (pthread_mutex_init(&lock_cnt, NULL) != 0)
    {
        puts("błąd przy tworzenie wątków");
        exit(1);
    }

    // wywoływanie wątków
    for (int i = 0; i < thread_no; i++)
    {
        if (pthread_create(&thread[i], NULL, watek, &arg[i]) != 0)
        {
            puts("błąd przy tworzenie wątków");
            exit(1);
        }
    }

    // łączenie wątków
    for (int i = 0; i < thread_no; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            puts("błąd przy łączenie wątków");
            exit(1);
        }
    }

    // wybierz najlepszy ruch
    zmiana ruch = znajdz_opt(v);

    // pobieram dodatkową pamięć ram z chmury
    for (int i = 0; i < thread_no; i++)
    {
        deallocate(arg[i].plansza, 9);
        deallocate(arg[i].nad_zwyciestwa, 3);
    }

    destruct_node(v);
    pthread_mutex_destroy(&lock_cnt);

    deallocate(plansza, 9);
    deallocate(nad_zywciestwa, 3);

    if (ruch.czesc == -1)
        return -1;

    // dopisywanie zmiany
    modify_board(game->board[znajdz_czesc(ruch)], ruch.x % 3, ruch.y % 3, game->turn);
    // game -> board[znajdz_czesc(ruch)] -> value[ruch.x % 3][ruch.y % 3] = gracz;
    return (ruch.x % 3 + ruch.y % 3 * 3);
}

int bot_9x9_normal(Game *game, int czesc)
{
    liczba_iteracji = 0;
    cel_liczby_iteracji = iteracje_normal;

    return make_mcts(game, czesc);
}

int bot_9x9_hard(Game *game, int czesc)
{
    liczba_iteracji = 0;
    cel_liczby_iteracji = iteracje_hard;

    return make_mcts(game, czesc);
}

int bot_9x9_impopable(Game *game, int czesc)
{
    liczba_iteracji = 0;
    cel_liczby_iteracji = iteracje_impopable;

    return make_mcts(game, czesc);
}

int bot_9x9_random(char **plansza, char gracz, int czesc)
{
    pair p = poczatek_czesci(czesc);

    int ile_opcji = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (plansza[p.x + i][p.y + j] == ' ')
                ile_opcji++;

    if (ile_opcji == 0)
        return -1;
    int wybieram = rand() % ile_opcji;
    zmiana ruch;

    for (int i = 0, idx = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (plansza[p.x + i][p.y + j] == ' ' && wybieram == idx)
            {
                ruch.x = p.x + i;
                ruch.y = p.y + j;
                ruch.czesc = i * 3 + j;
                idx++;
            }
            else if (plansza[p.x + i][p.y + j] == ' ')
                idx++;
        }
    }

    plansza[ruch.x][ruch.y] = gracz;
    return ruch.czesc;
}

bestMove minimax(Game *game, int depth, Player ruch_bota);

int bot_3x3_normal(Game *game, int czesc)
{
    // jesli ruch niemozliwy - zwroc -1
    check_board(game->board[0], game->turn, false);
    check_game_draw(game);
    if (game->board[0]->moves_count == 9)
        return -1;
    else if (game->status != IN_PROGRESS)
        return -1;
    srand(time(0));
    int miejsce, kolumna, wiersz;

    // losowanie ruchu i zmiana planszy
    while (game->status == IN_PROGRESS)
    {
        miejsce = rand() % 9;
        wiersz = miejsce / 3;
        kolumna = miejsce % 3;
        if (game->board[0]->value[wiersz][kolumna] != EMPTY)
            continue;
        else
            break;
    }
    modify_board(game->board[0], wiersz, kolumna, game->turn);

    return 0;
}

int bot_3x3_hard(Game *game, int czesc)
{
    check_board(game->board[0], game->turn, false);
    check_game_draw(game);
    if (game->board[0]->moves_count == 9)
        return -1;
    else if (game->status != IN_PROGRESS)
        return -1;
    else
    {
        bestMove naj_ruch = minimax(game, 2, game->turn);
        modify_board(game->board[0], naj_ruch.x, naj_ruch.y, game->turn);
    }
    return 0;
}

int bot_3x3_impopable(Game *game, int czesc)
{
    check_board(game->board[0], game->turn, false);
    check_game_draw(game);
    if (game->board[0]->moves_count == 9)
        return -1;
    else if (game->status != IN_PROGRESS)
        return -1;
    else
    {
        bestMove naj_ruch = minimax(game, 100, game->turn);
        modify_board(game->board[0], naj_ruch.x, naj_ruch.y, game->turn);
    }
    return 0;
}

bestMove minimax(Game *game, int depth, Player ruch_bota)
{
    // żeby już za dużo nie zmieniać i checkBoardStatus działał
    bestMove toReturn;
    toReturn.x = -1;
    toReturn.y = -1;

    check_board(game->board[0], game->turn, false);
    check_game_draw(game);
    printf("status gry: %i \n", game->turn);
    switch (game->status)
    {
    case IN_PROGRESS:
        if (depth == 0)
        {
            toReturn.wartosc_ruchu = 0;
            return toReturn;
        }
        break;
    case X_WON:
        if (ruch_bota == X)
        {
            toReturn.wartosc_ruchu = (10 - game->board[0]->moves_count);
            return toReturn;
        }
        else if (ruch_bota == O)
        {
            toReturn.wartosc_ruchu = -1 * (10 - game->board[0]->moves_count);
            return toReturn;
        }
        // zwraca wartość ruchu jako ilość pozostałych wolnych pól +1 (czyli 1/-1 gdy plansza jest zapełniona)
        break;
    case O_WON:
        if (ruch_bota == X)
        {
            toReturn.wartosc_ruchu = -1 * (10 - game->board[0]->moves_count);
            return toReturn;
        }
        else if (ruch_bota == O)
        {
            toReturn.wartosc_ruchu = (10 - game->board[0]->moves_count);
            return toReturn;
        }
        break;
    case DRAW:
        toReturn.wartosc_ruchu = 0;
        return toReturn;
        break;
    default:
        break;
    }

    bestMove min, max, value;
    min.wartosc_ruchu = 100;
    max.wartosc_ruchu = -100;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game->board[0]->value[i][j] == EMPTY)
            {
                // zmiana game'a
                modify_board(game->board[0], i, j, game->turn);
                if (game->turn == X)
                    game->turn = O;
                else
                    game->turn = X;
                (game->board[0]->moves_count)++;

                // rekurencyjne wywołanie aby otrzymać wartość ruchu
                value.x = i;
                value.y = j;
                value.wartosc_ruchu = minimax(game, depth - 1, ruch_bota).wartosc_ruchu;

                // cofnięcie zmian game'a
                modify_board(game->board[0], i, j, EMPTY);
                if (game->turn == X)
                    game->turn = O;
                else
                    game->turn = X;
                (game->board[0]->moves_count)--;

                // ustalenie min i maxa
                if (value.wartosc_ruchu > max.wartosc_ruchu)
                    max = value;
                if (value.wartosc_ruchu < min.wartosc_ruchu)
                    min = value;
            }
        }
    }
    // określenie najlepszego ruchu
    if (game->turn == ruch_bota)
        return max;
    else
        return min;
}