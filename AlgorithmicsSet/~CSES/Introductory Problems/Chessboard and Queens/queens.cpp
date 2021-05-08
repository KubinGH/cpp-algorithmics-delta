#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    array<array<bool, 8>, 8> lock;
    for(size_t y = 0; y < 8; y++)
    {
        for(size_t x = 0; x < 8; x++)
        {
            char c;
            cin >> c;
            lock[y][x] = (c == '*');
        }
    }

    vector<int> X(8);
    iota(X.begin(), X.end(), 0);

    size_t result = 0;
    do {
        bool ok = true;
        for(int y = 0; ok and y < 8; y++)
        {
            ok &= not lock[y][X[y]];
            for(int y1 = 0; y1 < y; y1++)
                ok &= (y+X[y] != y1+X[y1]) and (y-X[y] != y1-X[y1]);
        }
        result += ok;
    } while(next_permutation(X.begin(), X.end()));

    cout << result << endl;
}
