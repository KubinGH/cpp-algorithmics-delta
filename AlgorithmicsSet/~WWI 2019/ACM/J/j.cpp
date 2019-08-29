#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t t;
    cin >> t;
    while(t --> 0)
    {
        uint64_t A, B, C, D;
        cin >> A >> B >> C >> D;

        if(D < 13)
        {
            uint64_t r = 0;
            for(uint64_t a = 0; a <= D; a++)
                for(uint64_t b = 0; b <= D; b++)
                    for(uint64_t c = 0; c <= D; c++)
                        if(a+b+c == D)
                            r = max(r, (A+a)*(A+a) + (B+b)*(B+b) + (C+c)*(C+c) + 7*min({A+a, B+b, C+c}));
            cout << r << '\n';
        }
        else
        {
            uint64_t T[3] = {A, B, C};
            sort(T, T + 3);
            T[2] += D;
            A = T[0]; B = T[1]; C = T[2];
            cout << A*A + B*B + C*C + 7*min({A, B, C}) << '\n';
        }
    }
}
