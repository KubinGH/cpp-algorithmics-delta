#include <bits/stdc++.h>
#include <ktl/text/kmr.cpp>
#include <ktl/text/suffix_array.cpp>
#include <ktl/text/lcp.cpp>
#include <ktl/structures/sparse_table.cpp>

using namespace std;

struct mins { size_t operator() (size_t a, size_t b) { return min(a, b); } };

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;
    string S;
    S.reserve(2*n + 1);
    cin >> S;

    S.push_back('$');
    copy(S.rbegin()+1, S.rend(), back_inserter(S));

    karp_miller_rosenberg kmr(S.begin(), S.end());
    auto sarray = suffix_array(kmr), lcp = lcp_array(kmr, sarray);

    vector<size_t> rank(2*n + 1);
    for(size_t i = 0; i < 2*n + 1; i++)
        rank[sarray[i]] = i;

    sparse_table<size_t, mins> min_lcp(lcp.begin(), lcp.end());

    vector<size_t> count = {0, 0, 0};
    size_t result = 0;
    auto f = [&](size_t i) {
        return i < n ? 0 : (i > n ? 1 : 2);
    };
    for(size_t i = 0, j = 0; i < 2*n + 1; i++)
    {
        while(j < 2*n + 1 and not (count[0] and count[1]))
        {
            count[f(sarray[j])]++;
            j++;
        }
        if(count[0] and count[1])
            result = max(result, min_lcp(i, j - 1));
        count[f(sarray[i])]--;
    }

    cout << result;
}
