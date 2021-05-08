#include <bits/stdc++.h>

using namespace std;

template<typename T, typename Tk, typename AssociativeBinaryOp = multiplies<T>>
T power(T n, Tk k, AssociativeBinaryOp f = {}, T r = T(1))
{
    while(k)
    {
        if(k % 2)
            r = f(r, n);
        k /= 2;
        n = f(n, n);
    }
    return r;
}

template<size_t B = 10>
uint64_t count_same_len(string S)
{
    if(S.size() == 0)
        return 0;
    auto s = [&](size_t i) {
        return size_t(S[i] - '0');
    };
    vector<array<array<uint64_t, 2>, B>> R(S.size());
    for(size_t a = 1; a < s(0); a++)
        R[0][a][1] = 1;
    R[0][s(0)][0] = 1;
    for(size_t i = 1; i < S.size(); i++)
    {
        for(size_t a = 0; a < B; a++)
        {
            for(size_t b = 0; b < B; b++) if(a != b)
            {
                if(a == s(i))
                    R[i][a][0] += R[i-1][b][0];
                else if(a < s(i))
                    R[i][a][1] += R[i-1][b][0];
                R[i][a][1] += R[i-1][b][1];
            }
        }
    }
    uint64_t result = 0;
    for(size_t a = 0; a < B; a++)
        result += R.back()[a][1];
    return result;
}

template<size_t B = 10>
uint64_t count(string S)
{
    if(S == "0")
        return 0;
    uint64_t result = count_same_len<B>(S);
    for(size_t k = 0; k < S.size(); k++)
        result += power<uint64_t>(9, k);
    return result;
}

int main()
{
    uint64_t a, b;
    cin >> a >> b;
    cout << count<10>(to_string(b+1)) - count<10>(to_string(a)) << endl;
}
