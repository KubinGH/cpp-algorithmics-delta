#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;

uint count_less(vector<uint> A, uint x)
{
    sort(A.begin(), A.end());
    uint result = 0;
    for(size_t i = 0, j = A.size() - 1; i < j; i++)
    {
        while(i < j and A[i] + A[j] >= x)
            j--;
        if(i < j)
            result += j - i;
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<uint> A(n);
    for(auto& a : A)
        cin >> a;

    auto b = __lg(*max_element(A.begin(), A.end())) + 2;

    vector<uint> B(n);
    uint result = 0;
    for(size_t k = 0; k < b; k++)
    {
        for(size_t i = 0; i < n; i++)
            B[i] = A[i] & ((2<<k) - 1);

        auto c = count_less(B, (2 << k)) - count_less(B, (1 << k))
               + count_less(B, (4 << k)) - count_less(B, (2 << k) + (1 << k));

        if(c % 2)
            result |= (1 << k);
    }

    cout << result << endl;
}
