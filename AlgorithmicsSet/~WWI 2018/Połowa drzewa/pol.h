#ifndef POL_H_
#define POL_H_

// Zwraca liczbę wierzchołków (n).
int LiczbaWierzcholkow();

// Zwraca liczbę krawędzi (m).
int LiczbaKrawedzi();

// Jeśli zostanie wywołana po raz i-ty (0 <= i < LiczbaKrawedzi()),
// to wyznaczy i-tą krawędź.
// Przypisze końce krawędzi do zmiennych *u i *v, a wagę krawędzi do *w.
// (przykład użycia znajduje się w pliku prog.cpp)
void NastepnaKrawedz(int* u, int* v, long long* w);

// Informuje o wyborze i-tej krawędzi (0 <= i < LiczbaKrawedzi())
// do minimalnego lasu rozpinającego.
void WybierzKrawedz(int i);

// Powiadamia biblioteczkę o zakończeniu wybierania krawędzi.
void Zakoncz();

#include "pol_lib.cpp"

#endif
