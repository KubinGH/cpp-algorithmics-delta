#include <bits/stdc++.h>

using namespace std;

template<typename String, typename T = typename String::value_type, typename Compare = less<T>>
size_t min_rotation(const String& Z, Compare cmp = {})
{
    String S = Z + Z;
    const size_t n = S.size();
    uint32_t i = 0, r = 0;
    while(i < n / 2)
    {
        r = i;
        uint32_t j = i + 1, k = i;
        while(j < n and (cmp(S[k], S[j]) or S[k] == S[j]))
        {
            if(cmp(S[k], S[j]))
                k = i;
            else
                k++;
            j++;
        }
        while(i <= k)
            i += j - k;
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        uint32_t n;
        string S;
        cin >> n >> S;
        uint32_t k = min_rotation(S, greater<char>());
        rotate(S.begin(), S.begin() + k, S.end());
        cout << S << "\n";
    }
}
