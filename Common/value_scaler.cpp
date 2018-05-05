#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

template<typename T, size_t N>
struct value_scaler
{
    pair<T, size_t> _A[N];
    unordered_map<T, size_t> M;
    template<typename Iterator>
    value_scaler(Iterator begin, Iterator end)
    {
        size_t n = 0;
        for(auto it = begin; it != end; it++)
        {
            _A[n].first = *it; _A[n].second = n;
            n++;
        }
        sort(_A, _A + n);
        M.reserve(N);
        for(size_t i = 0, f = 0; i < n; i++)
        {
            if(i > 0 and _A[i].first == _A[i-1].first)
                f++;
            M[_A[i].first] = i - f;
        }
    }
    const size_t& operator[] (const T& x)
    {
        return M[x];
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    static value_scaler<uint32_t, MAX> T(A, A + n);
    for(pair<uint32_t, uint32_t> p : T.M)
        cout << p.first << " -> " << p.second << endl;
}
