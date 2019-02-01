#ifndef OSALIB
#define OSALIB

#include <string>

void init(std::string nazwa);

void nowa_osada(std::string nowa, std::string stara, int dlugosc);

int odleglosc(std::string pierwsza, std::string druga);

#endif