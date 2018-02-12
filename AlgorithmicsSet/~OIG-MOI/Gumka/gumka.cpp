#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 10000;
const size_t MAX_C = 10000000;

const string COMP = "bitek";

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    string S[MAX];
    static uint32_t CI[MAX], NI[MAX];
    uint32_t *PCI, *PNI;
    PCI = CI; PNI = NI;
    for(uint32_t i = 0; i < n; i++)
        cin >> S[i];
    string result;
    for(char c = 'z' + 1; c --> 'a';)
    {
        bool ok = true;
        for(uint32_t s = 0; s < n; s++)
        {
            bool found = false;
            for(uint32_t i = PCI[s]; i < S[s].size(); i++)
            {
                if(S[s][i] == c)
                {
                    found = true;
                    PNI[s] = i + 1;
                    break;
                }
            }
            if(not found)
            {
                ok = false;
                break;
            }
        }
        if(not ok)
            continue;
        uint32_t* t = PCI;
        PCI = PNI;
        PNI = t;
        result += c;
        c++;
    }
    if(lexicographical_compare(result.begin(), result.end(),
                               COMP.begin(), COMP.end()))
        cout << COMP;
    else
        cout << result;
}
