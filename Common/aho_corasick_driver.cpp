#include <bits/stdc++.h>
#include "KTL/text/aho_corasick.cpp"

using namespace std;

/*
abccab
7
a
ab
bab
bc
bca
c
caa
*/

int main()
{
    string M;
    cin >> M;
    uint32_t n;
    cin >> n;
    vector<string> D(n); vector<pair<string::iterator, string::iterator>> DI(n);
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> D[i];
        DI[i] = {D[i].begin(), D[i].end()};
    }
    aho_corasick<char, aho_corasicks::static_node<26>, aho_corasicks::partial_minus<char, 'a'>>
        T(DI.begin(), DI.end());
    auto curr = T.begin();
    for(uint32_t i = 0; i < M.size(); i++)
    {
        curr = curr.advance(M[i]);
        cout << "curr @ " << curr.node << endl;
        auto temp = curr.matches() ? curr : curr.next_match();
        while(temp.valid_match())
        {
            cout << temp.match() << " @ " << i << endl;
            temp = temp.next_match();
        }
    }
}
