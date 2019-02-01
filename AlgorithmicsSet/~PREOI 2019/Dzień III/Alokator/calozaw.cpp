#include <cstdlib>
#include <iostream>
#include "calolib.h"

int inicjuj() {
    int N;
    std::cin >> N;

    std::cerr << "inicjuj() -> " << N << std::endl;

    return N;
}

int zapytanie() {
    int current;
    std::cin >> current;

    if (current == 0) {
        // KONIEC!!!
        std::cerr << "zapytanie() -> exit" << std::endl;
        exit(0);
    }

    std::cerr << "zapytanie() -> " << current << std::endl;

    return current;
}

void przesun(int skad, int dokad) {
    std::cerr << "przesun(" << skad << ", " << dokad << ")" << std::endl;
}

void dodaj(int gdzie) {
    std::cerr << "dodaj(" << gdzie << ")" << std::endl;
}

void zrobione() {
    std::cerr << "zrobione()" << std::endl;
}
