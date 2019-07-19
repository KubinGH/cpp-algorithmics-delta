#include <bits/stdc++.h>

using namespace std;


struct karp_miller_rosenberg
{
    size_t n;
    vector<vector<size_t>> T;

    template<typename Iterator>
    karp_miller_rosenberg(Iterator first, Iterator last)
    {
        T.push_back(compressed(first, last));
        n = T[0].size();

        vector<vector<size_t>> buckets(n);
        for(size_t k = 1; (1u << k) <= n; k++)
        {
            const size_t p = 1 << k, q = p >> 1, m = n - p + 1;

            vector<pair<size_t, size_t>> run(m);
            for(size_t i = 0; i < m; i++)
                run[i] = {T[k-1][i], T[k-1][i + q]};

            T.push_back(compressed(run.begin(), run.end()));
        }
    }


    pair<size_t, size_t> operator() (size_t i, size_t j) const
    {
        const size_t d = j - i, e = __lg(d);
        return {T[e][i], T[e][j - (1 << e)]};
    }


    template<typename Iterator, typename V = typename iterator_traits<Iterator>::value_type>
    static vector<size_t> compressed(Iterator first, Iterator last)
    {
        const size_t n = distance(first, last);

        vector<pair<V, size_t>> values; values.reserve(n);
        for(size_t i = 0; i < n; i++, ++first)
            values.emplace_back(*first, i);
        sort(values.begin(), values.end());

        vector<size_t> result(n);
        for(size_t i = 0, f = 0; i < n; i++)
        {
            if(i and values[i].first == values[i-1].first)
                f++;
            result[values[i].second] = i - f;
        }

        return result;
    }
};


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    const size_t n = S.size();
    for(size_t i = 0; i < n; i++)
        S.push_back('$');

    karp_miller_rosenberg kmr(S.begin(), S.end());

    vector<pair<pair<size_t, size_t>, size_t>> keys(n);
    for(size_t i = 0; i < n; i++)
        keys[i] = {kmr(i, i + n), i};

    sort(keys.begin(), keys.end());

    for(auto p : keys)
        cout << p.second << '\n';
}
