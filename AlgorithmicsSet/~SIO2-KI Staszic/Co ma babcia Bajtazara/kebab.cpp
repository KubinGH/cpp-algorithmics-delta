#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string A, B;
    cin >> A >> B;
    static array<pair<uint32_t, uint32_t>, MAX> P;
    for(uint32_t i = 0; i < B.size(); i++)
        P[i].second = -1;
    for(uint32_t i = 0; i < A.size(); i++)
    {
        uint32_t best_length = 0, best_j = -1;
        for(uint32_t j = 0; j < B.size(); j++)
        {
            if(A[i] == B[j] and best_length + 1 > P[j].first)
                P[j].first = best_length + 1, P[j].second = best_j;
            else if(P[j].first > best_length)
                best_length = P[j].first, best_j = j;
        }
        //cerr << j << ": ";
        //for(uint32_t j = 0; j < B.size(); j++)
        //    cerr << "(" << P[j].first << ", " << P[j].second << "); ";
        //cerr << endl;
    }
    uint32_t best_length = P[0].first, best_i = 0;
    for(uint32_t i = 1; i < B.size(); i++)
        if(P[i].first > best_length)
            best_length = P[i].first, best_i = i;
    list<char> result;
    if(best_length)
    {
        while(best_i != -1u)
        {
            result.push_front(B[best_i]);
            best_i = P[best_i].second;
        }
    }
    cout << result.size();
    if(result.size())
    {
        cout << endl;
        for(char c : result)
            cout << c;
    }
}
