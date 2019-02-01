#include "osalib.h"
#include <iostream>
using namespace std;

int main() {
    int q;
    cout << "Wpisz liczbe wszystkich zapytan: ";
    cin >> q;
    cout << "Jak nazywa sie osada z poczatkow historii?\n";
    string name;
    cin >> name;
    init(name);
    
    string x, a, b;
    int d;
    while(q--) {
        cout << "? - pytanie kupca\nnew - nowa osada:\n";
        cin >> x;
        if(x == "?") {
            cout << "O jakie osady zapytal kupiec?\n";
            cin >> a >> b;
            cout << "Odpowiedz programu: " << odleglosc(a, b) << "\n";
        }
        else {
            cout << "Jaka nazwe wymyslili mieszkancy?\n";
            cin >> a;
            cout << "Z jaka osadą jest poloczone " << a << "?\n";
            cin >> b;
            cout << "Ile ma droga pomiedzy " << a << " a " << b << "?\n";
            cin >> d;
            nowa_osada(a, b, d);
        }
    }
    return 0;
}