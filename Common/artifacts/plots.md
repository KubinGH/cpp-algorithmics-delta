# Plots

Na planszy $n \times n$ niektóre pola są zablokowane. Chcemy wybierać
prostokąty niezawierające zablokowanych pól. Chcemy policzyć:

`cnt[w, h]` = liczba prostokątów wielkości $w \times h$


# Największy prostokąt

* (Dla danego fixowanego dolnego boku prostokąta)
* Budujemy tablicę odległości do najbliższego zablokowanego pola wyżej
* Będziemy odwiedzać od najwyższej kolumny w tak zbudowanym „skyline”
* Odcinamy prostokąt sięgający od góry do wysokości pierwszego niższego z obu stron
    * Szukanie pierwszego elementu mniejszego na lewo -- strzałki ←↓↑→
* Plot-twist: można zrobić z jednej strony
    * Fixowany prawy dolny róg
    * Stos
    * Kozak

# `cnt`

* Bierzemy poprzedni algorytm
* Skracając kolumnę, dodajemy do wyniku prostokąty które przez to są usuwane
    * $h_1 \le h \le h_2$
    * $1 \le w \le w_2$
* Aby to przechować, dodajemy do dwuwymiarowej tablicy różnicowej `precnt`
* Aaale, wcale nie, bo `cnt[w, h] +=` $(w_2 - w + 1)$
    * Dodawanie ciągu arytmetycznego -- podwójna tablica różnicowa
    
