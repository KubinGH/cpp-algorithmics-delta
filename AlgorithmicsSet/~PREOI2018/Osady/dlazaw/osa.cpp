// paczka dla zawodnika

#include "osalib.h"
#include <iostream>
using namespace std;

void init(string nazwa) {
    cerr << "pierwsza osada: " << nazwa << "\n";
}

void nowa_osada(string nowa, string stara, int dlugosc) {
    cerr << "nowa osada: " << nowa << " polaczona z " << stara << " droga dlugosci " << dlugosc << "\n";
}

int odleglosc(string pierwsza, string druga) {
    if(pierwsza == druga)
        return 0;
    if(druga == "SARAJEWO")
        return 9;
    return 3;
}
