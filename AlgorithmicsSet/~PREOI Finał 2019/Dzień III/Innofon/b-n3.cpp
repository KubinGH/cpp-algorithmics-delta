#include <bits/stdc++.h>

using namespace std;

template<typename T, typename Iterator>
size_t count_less(Iterator first, Iterator last, T value)
{
    size_t lo = 0, hi = last - first;
    while(lo < hi)
    {
        size_t mid = (lo + hi) / 2;
        if(first[mid] >= value)
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n), B(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i] >> B[i];

    auto oA = A, oB = B;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    auto value = [&](uint32_t x, uint32_t X) {
        uint64_t r = 0;
        for(uint32_t i = 0; i < n; i++)
            if(oA[i] >= X)
                r += X;
            else if(oB[i] >= x)
                r += x;
        return r;
    };

    uint64_t result = 0;
    vector<uint32_t> V; V.reserve(2*n + 1);
    V.push_back(0);
    merge(A.begin(), A.end(), B.begin(), B.end(), back_inserter(V));

    for(uint32_t i = 0; i < V.size(); i++)
        for(uint32_t j = i + 1; j < V.size(); j++)
            result = max(result, value(V[i], V[j]));
    cout << result;
}
