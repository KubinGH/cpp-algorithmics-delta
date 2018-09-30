#include <bits/stdc++.h>

using namespace std;

template<typename Iterator, class T = typename iterator_traits<Iterator>::value_type >
vector<uint32_t> manacher(Iterator first, Iterator last, T leaf = '$')
{
    vector<T> A(distance(first, last)*2 + 1);
    for(auto it = A.begin(); first != last; first++)
    {
        *it++ = leaf;
        *it++ = *first;
    }
    A.back() = '$';
    vector<uint32_t> P(A.size(), 0);
    uint32_t right = 0, center = 0;
    for(uint32_t i = 1; i < A.size(); i++)
    {
        uint32_t mirror = 2*center - i;
        if(i + P[mirror] <= min(right, A.size() - 1))
            P[i] = P[mirror];
        while(i >= P[i]+1 and i+P[i]+1 < A.size()
              and A[i-P[i]-1] == A[i+P[i]+1])
            P[i]++;
        if(i + P[i] > right)
        {
            center = i;
            right = center + P[i];
        }
    }
    for(uint32_t i = 0; i < A.size(); i++)
        P[i] = P[i]/2 + i%2;
    return P;
}

int main()
{
    string S;
    cin >> S;
    for(uint32_t v : manacher(S.begin(), S.end()))
        cout << v << " ";
}