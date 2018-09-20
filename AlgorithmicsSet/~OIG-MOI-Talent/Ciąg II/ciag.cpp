#include <bits/stdc++.h>

using namespace std;

template<typename Iterator, typename T = typename iterator_traits<Iterator>::value_type>
vector<T> get_stair_array(Iterator first, Iterator last)
{
    vector<T> S;
    S.reserve(distance(first, last));
    S.push_back((*first > 0) ? 1 : 0);
    auto it = first;
    for(it++; it != last; it++)
        S.push_back(min(S.back() + 1, *it));
    return S;
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    vector<uint32_t> U, V;
    U = get_stair_array(A.begin(), A.end());
    V = get_stair_array(A.rbegin(), A.rend());
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
        r = max(r, min(U[i], V[n-i-1]));
    cout << r;
}
