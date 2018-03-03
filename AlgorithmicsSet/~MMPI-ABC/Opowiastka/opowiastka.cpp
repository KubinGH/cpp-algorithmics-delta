#include <bits/stdc++.h>

using namespace std;

int main()
{
    string out, available;
    cin >> out >> available;
    sort(available.begin(), available.end());
    uint32_t j = 0;
    for(uint32_t i = 0; i < out.size(); i++)
    {
        while(j < available.size() and available[j] < out[i])
            cout << available[j], j++;
        cout << out[i];
    }
    while(j < available.size())
        cout << available[j], j++;
}
