## Raport ze stanu bota 9x9

---

#### Wstep
Algorytm kótry został użyty do stworzenia bota to mcts. W tym przypadku nie dało się użyć algorytmu minmax, ponieważ do gry super tic-tac-toe nie istnieje evaluation fuction która jest niezbędna do działania minmaxa. 

#### Opis działania MCTS
MCTS jest techniką poszukiwania drzewa decyzyjnego, która symuluje tysiące losowych rozgrywek, oceniając ich skuteczność i wybierając najlepsze ruchy na podstawie zebranych statystyk. Dzięki temu bot jest w stanie dostosowywać swoją strategię w czasie rzeczywistym, by skutecznie konkurować z przeciwnikiem. Podczas tworzenia drzewa algorytm MCTS do utworzenia nowego wierzchołka wykonuje 1 iteracje na którą składają się:
- Selection - wybranie wierzchołka (liścia)
- Expansion - dodanie mu syna
- Simulation - przeprowadzenie symulacje dla nowego wierzchołka
- Backpropagation - dodanie zaktualizowanych informacji dla ścieżki od roota do nowego wierzchołka

#### Wybieranie wierzchołków
Podczas wyboru wierzchołka (część Select) warzne jest zachowanie równowagi pomiędzy eksploracją (poszukiwanie nowych ruchów), a eksploatacją (korzystanie z już "dobrego" ruchu). Taką równowagę zapewnia UCT którą używa bot.

### Dobieranie parametrów
Dobranie różnych parametrów do bota znacznie zmienia jego zachowanie, dla tego by je odpowiednio dobrać zostało przetestowane 46 róznych zestawów parametrów. Testy polegały na 200 grach pomiędzy botem normal o 500 iteracjach a botem hard o 25'000 iterachach. Zostały wybrane następujące parametry:

1) DIFF: przyjmujący argumenty: {0, 1}. Jeśli parametr jest aktywny to do wzoru na UCT jest dodawana wartość 1 / (rand() % 45 + 5) dzięki czemu przy użyciu wielu wątków chodzących po drzewie, wątki nie idą aż tak często do tego samego wierzchołka.

2) SQRT: przyjmuje argumenty: {1, 2, 4, 9}. We wzorze na UCT występuje stała c, w programie jest to pierwiastek właśnie z argumentu SQRT.

3) WINS: przyjmuje argumenty: {2, 3}. Jeśli nowo dodany wierzchołek przegrywa to dostaje (on oraz jego poprzednicy) 0pkt, remisuje 1 pkt, wygrywa WINS pkt

4) SELECT: przyjmuje argumenty: {0, 1, 2}. Gdy zostanie już stworzone drzewo MCTS to trzeba wybrać jaki ruch ma wykonać bot, można to zrobić na 3 sposoby:
    - 0: wybranie wierzhołka o najlepszym stosunku wygranych do przegranch
    - 1: wybranie wierzchołka o największym UCT
    - 2: wybranie wierzhołka który został odwiedzony najwięcej razy

#### Analiza wyników dla parametrów
Wykresy pokazują wyniki dla bota nr_4 grającego z botem nr_3

##### Wygrane < 40%

<table>
  <tr>
    <td><img src="/wykresy/wykres_9.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_10.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_15.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_16.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_43.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_46.png" alt="wykres" width="550"/></td>
  </tr>
</table>



##### Wygrane 40% - 45%

<table>
  <tr>
    <td><img src="/wykresy/wykres_0.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_6.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_13.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_22.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_31.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_37.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_40.png" alt="wykres" width="550"/></td>
  </tr>
</table>


##### Wygrane 45% - 50%

<table>
  <tr>
    <td><img src="/wykresy/wykres_2.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_3.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_12.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_19.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_21.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_25.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_27.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_34.png" alt="wykres" width="550"/></td>
  </tr>
</table>


##### Wygrane 50% - 55%

<table>
  <tr>
    <td><img src="/wykresy/wykres_1.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_4.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_7.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_8.png" alt="wykres" width="550"/></td>
  </tr>
</table>


##### Wygrane 55% - 60%

<table>
  <tr>
    <td><img src="/wykresy/wykres_5.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_14.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_18.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_20.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_24.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_28.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_33.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_39.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_42.png" alt="wykres" width="550"/></td>
  </tr>
</table>


##### Wygrane 60% - 65%

<table>
  <tr>
    <td><img src="/wykresy/wykres_11.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_23.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_30.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_36.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_41.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_45.png" alt="wykres" width="550"/></td>
  </tr>
</table>


##### Wygrane 65% - 70%

<table>
  <tr>
    <td><img src="/wykresy/wykres_17.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_26.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_29.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_32.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_35.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_38.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_44.png" alt="wykres" width="550"/></td>
  </tr>
</table>


##### Wygrane 70% > 
![wykres](/wykresy/wykres_47.png)

### Analiza wykresów
Podczas przeprowadzania testów okazało się że DIFF = 1 daje dobre wyniki, niestety takie ustawnienie powoduje, że czas działania bota jest o wiele większy. Bot króry wykonuje 500k iteracji i ma DIFF = 1 wykonuje 1 ruch 8s, taką sama ilosc czasu na wykonanie ruchu wykonuje bot który ma 7M iteracji i DIFF = 0. Mając dwa zarótno tak bardzo podobne i różne boty szkoda by było ich nie porównać. Porówanie tych dwuch botów na 50 testach:
![wykres](/wykresy/wykresDIFF0vsDiFF1.png)

Jak wynika z wykresu nie ma to znaczenia czy używamy bota z 7M iteracji i DIFF = 0, czy bota z 500k iteracji i DIFF = 1


### Druga część analizy wyników
Druga częć polegała na pojedynkach pomiędzy botem impopable a botem hard, każdy zestaw danych miał 25 rund, jest to spowodowane tym że jedna runda trwała 5min. W tej części oba boty miały cały czas DIFF = 1 oraz select = 2, zmienily się tylko parametry WINS = {2, 3}, SQRT = {1, 2, 4, 9, 16, 25}

<table>
  <tr>
    <td><img src="/wykresy/wykres_v2_0.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v2_1.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v2_2.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_v2_3.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v2_4.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v2_5.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_v2_6.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v2_7.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v2_8.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_v2_9.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v2_10.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v2_11.png" alt="wykres" width="550"/></td>
  </tr>
</table>


Jak widać z wykresów bot impobable nie jest aż tak impopable, widać też tendencje: im większe SQRT i WINS tym gorzej radzi sobie bot impopable, więc warto by było przetestować co sie stanie dla mniejszego SQRT, WINS musi być conajmiej 2, ponieważ remist dodaje 1pkt, a przegrana 0pkt.

### Trzecia częśc doboru współczynników

W tej części znów grały przeciwko sobie boty hard i impopable, jednak teraz DIFF = 0, SELECT pozostaje bez zmian oraz SQRT = {0.2, 0.4, 0.8, 1}, WINS = {2, 3}. Dla przypomienia parametr SQRT, czyli stała c we wzorze UCT nie wynosi np 0.2, a sqrt(0.2).

<table>
  <tr>
    <td><img src="/wykresy/wykres_v3_0.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v3_1.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_v3_2.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v3_3.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_v3_4.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v3_5.png" alt="wykres" width="550"/></td>
  </tr>
  <tr>
    <td><img src="/wykresy/wykres_v3_6.png" alt="wykres" width="550"/></td>
    <td><img src="/wykresy/wykres_v3_7.png" alt="wykres" width="550"/></td>
  </tr>
</table>


---

### Podsumowanie
Najlepiej sobie poradził bot DIFF = 0, SQRT = 0.8, SELECT = 2, WINS = 2 są to ostateczne parametry dla bota. Testy jak sobie radzą inne boty dla tych paramatrów, każdy test zawiera 50 symulacji

##### random vs normal
![wykres](/wykresy/wykresRandomNormal.png)

##### normal vs hard
![wykres](/wykresy/wykresNormalHard.png)

##### hard vs impopable
![wykres](/wykresy/wykres_v3_4.png)