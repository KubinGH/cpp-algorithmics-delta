#include <bits/stdc++.h>

using namespace std;

template<typename It>
vector<size_t> manacher(It first, It last)
{
    using T = typename It::value_type;
    static vector<T> S;
    S.clear(); copy(first, last, back_inserter(S));
    const size_t n = S.size();
    vector<size_t> R(n);
    for(size_t i = 0, c = 0; i < n; i++)
    {
        if(i <= c + R[c])
            R[i] = min(R[2*c - i], c + R[c] - i);
        while(i + R[i] + 1 < n and i >= R[i] + 1 and S[i+R[i]+1] == S[i-R[i]-1])
            R[i]++;
        if(i + R[i] > c + R[c])
            c = i;
    }
    return R;
}

template<typename It, typename T = typename It::value_type>
vector<size_t> palindrome_radii(It first, It last, T leaf = T(0))
{
    if(first == last) return {};
    static vector<T> S;
    S.clear();
    S.push_back(leaf);
    do {
        S.push_back(*first);
        S.push_back(leaf);
    } while(++first != last);

    auto R = manacher(S.begin(), S.end());
    R.erase(R.begin()); R.pop_back();
    for(auto& r : R)
        r /= 2;
    return R;
}

template<typename It, typename T = typename It::value_type>
vector<pair<size_t, size_t>> palindrome_substrings(It first, It last, T leaf = T(0))
{
    auto R = palindrome_radii(first, last, leaf);
    vector<pair<size_t, size_t>> Z;
    for(size_t i = 0; i < R.size(); i++)
        Z.emplace_back(2*R[i]+(1-i%2), (i+1)/2 - R[i]);
    return Z;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string S;
    cin >> S;
    auto Z = palindrome_substrings(S.begin(), S.end());
    auto [d, i] = *max_element(Z.begin(), Z.end());
    cout << S.substr(i, d) << endl;
}
