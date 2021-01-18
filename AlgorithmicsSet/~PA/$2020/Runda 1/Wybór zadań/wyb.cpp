#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    int cnt[5][3] = {};
    for(size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        cnt[str[0] - '1'][str[1] - 'A']++;
    }

    bool ok = true;
    for(size_t i = 0; i < 5; i++)
        for(size_t j = 0; j < 3; j++)
            ok = ok and (cnt[i][j] >= (1 + (i == 4)));

    cout << (ok ? "TAK" : "NIE") << endl;
}
