#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int64_t s;
    cin >> n >> s;

    vector<int64_t> A(2*n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i], A[n+i] = A[i];

    vector<int64_t> S(2*n+1);
    partial_sum(A.begin(), A.end(), S.begin() + 1);

    mt19937 gen(time(0));
    auto randint = [&](int a, int b) {
        return uniform_int_distribution<int>{a, b}(gen);
    };

    auto get = [&](size_t p) {
        size_t i = 0, c = 0;
        auto first = S.begin() + p, last = S.begin() + p + n + 1;
        while(i < n)
            i = upper_bound(first, last, S[p+i] + s) - (first+1), c++;
        return c;
    };

    size_t result = get(0);
    const size_t t = max(20.0, 5.0 * n / (result - (result>1)));
    for(size_t i = 0; i < t; i++)
        result = min(result, get(randint(0, n - 1)));

    cout << result << endl;
}
