#include <bits/stdc++.h>

using namespace std;

const int oo = INT_MAX / 3;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    const size_t n = count(S.begin(), S.end(), '(');
    vector<bool> leaf(n);
    vector<int> sum(n);
    vector<size_t> left(n), right(n);

    size_t index = 0, curr = 0;
    function<size_t(void)> build = [&]() {
        auto i = curr++;
        index++;
        if(S[index] == ')')
            leaf[i] = true;
        else if(S[index] == 'B')
            leaf[i] = true, sum[i] = 1, index++;
        else
        {
            left[i] = build();
            right[i] = build();
            sum[i] = sum[left[i]] + sum[right[i]];
        }
        index++;
        return i;
    };
    build();

    vector<array<pair<pair<size_t, int>, int>, 4>> cache(n);
    vector<size_t> cache_idx(n);

    function<int(size_t, int)> solve = [&](size_t u, int b) {
        if(u) for(size_t t = 0; t < 4; t++)
            if(cache[u][t].first == make_pair(u, b))
                return cache[u][t].second;

        const auto c = sum[u] + b;
        if(not leaf[u])
        {
            const auto l = c/2 - sum[left[u]], r = c/2 - sum[right[u]];
            int ret;
            if(c % 2 == 0)
                ret = solve(left[u], l) + solve(right[u], r);
            else
                ret = min(
                    solve(left[u], l+1) + solve(right[u], r),
                    solve(left[u], l) + solve(right[u], r+1)
                );
            cache[u][cache_idx[u]++] = {{u, b}, ret};
            return ret;
        }
        else
            return c == 0 or c == 1 ? (b == 1) : +oo;
    };

    auto r = solve(0, 0);
    if(r < +oo)
        cout << "TAK" << endl << r << endl;
    else
        cout << "NIE" << endl;
}
