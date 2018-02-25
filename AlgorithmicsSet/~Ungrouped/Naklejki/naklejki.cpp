#include <bits/stdc++.h>
#define MAX 100000

using namespace std;

typedef unsigned short uint16_t;

int main()
{
    uint16_t length, pairs;
    cin >> length >> pairs;
    static char word[MAX + 1];
    cin >> word;
    static pair<uint16_t, uint16_t> changes[MAX];
    for(uint16_t i = 0; i < pairs; i++)
    {
        cin >> changes[i].first >> changes[i].second;
        changes[i].first--; changes[i].second--;
    }
    reverse(changes, changes + pairs);
    static bool changed[MAX];
    for(uint16_t i = 0; i < pairs; i++)
    {
        pair<uint16_t, uint16_t> current = changes[i];
        if(changed[current.first])
            continue;
        uint16_t L, P;
        for(L = current.first, P = current.second; P < length; L++, P++)
        {
            if(changed[P]) break;
            word[P] = word[L];
        }
        fill(changed + current.second, changed + P + 1, true);
    }
    cout << word;
}
