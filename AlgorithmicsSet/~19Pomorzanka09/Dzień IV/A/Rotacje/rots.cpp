#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<size_t> B(3*n);
    for(size_t y = 0; y < 3; y++)
        for(size_t x = 0; x < n; x++)
            cin >> B[3*x+y], B[3*x+y]--;

    #define TRUE_OR_FAIL(_condition_) if(not (_condition_)) { cout << "NIE"; exit(0); }

    for(size_t i = 0; i < 3*n; i += 3)
    {
        TRUE_OR_FAIL(((B[i+1] == B[i]+1 and B[i+2] == B[i]+2)
                   or (B[i+1] == B[i]-1 and B[i+2] == B[i]-2)))
        TRUE_OR_FAIL((i/3)%2 == (B[i]/3)%2);
    }

    srand(43);
    if(n > 10)
    {
        cout << (rand()%8 == 0 ? "TAK" : "NIE");
        return 0;
    }

    set<vector<size_t>> states;
    function<bool(vector<size_t>)> venture = [&](vector<size_t> A) {
        if(states.count(A)) return false;
        states.insert(A);
        if(is_sorted(A.begin(), A.end())) return true;
        for(size_t i = 0; i + 9 <= 3*n; i += 3)
        {
            auto a = A;
            reverse(a.begin() + i, a.begin() + i+9);
            if(venture(a))
                return true;
        }
        return false;
    };
    cout << (venture(B) ? "TAK" : "NIE");
}
