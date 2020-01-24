#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    auto check = [&](const pair<int, int>& A, const pair<int, int>& B) {
        return A.first < B.second and B.first < A.second;
    };

    vector<pair<int, int>> W;
    for(size_t i = 0; i < n; i++)
    {
        pair<int, int> w;
        cin >> w.first >> w.second;

        bool ok = true;
        for(size_t a = 0; a < W.size(); a++)
            for(size_t b = a+1; b < W.size(); b++)
                if(check(w, W[a]) + check(w, W[b]) + check(W[a], W[b]) == 2)
                    ok = false;

        if(ok) W.push_back(w);
        cout << (ok ? "TAK\n" : "NIE\n");
    }
}
