/* Przykladowe (oczywiscie niepoprawne) rozwiazanie
 * do zadania Alokator
 */

#include <cstdlib>
#include "calolib.h"

int main() {
    srand(426942);

    // pobieramy wielkosc tablicy
    int N = inicjuj();

    while (true) {
        // pobieramy zapytanie
        int pyt = zapytanie();

        if (pyt > 0) {
            // jesli mozna, losujemy miejsce, gdzie wstawic; co ok. 10
            // zapytan przestawiamy wczesniej losowy klocek z pierwszej polowy
            // gdziekolwiek na druga polowe tablicy

            if (rand() % 10 == 0)
                przesun(rand() % (N / 2) + 1, N - rand() % (N / 2));

            dodaj(rand() % N + 1);
        } else {
            // po usunieciu nic nie robimy, ale musimy to stwierdzic
            zrobione();
        }
    }
}
