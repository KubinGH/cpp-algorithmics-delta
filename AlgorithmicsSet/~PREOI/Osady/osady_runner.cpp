#include <bits/stdc++.h>
#include "osady.cpp"

using namespace std;

int main()
{
    string initial, first, second;
    uint32_t dist;
    char choice;
    cout << "First village name: ";
    cin >> initial;
    init(initial);
    cout << endl << "New village: '+'" << endl << "Distance: '?'" << endl;
    cout << "Exit: '!'" << endl << endl;
    while(true)
    {
        cin >> choice;
        if(choice == '+')
        {
            cin >> first >> second >> dist;
            nowa_osada(first, second, dist);
            cout << "Done." << endl << endl;
        }
        else if(choice == '?')
        {
            cin >> first >> second;
            cout << "Result: " << odleglosc(first, second) << endl << endl;
        }
        else
            cout << "???" << endl;
    }
}
