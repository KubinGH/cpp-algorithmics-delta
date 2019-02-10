#include <bits/stdc++.h>

using namespace std;

uint64_t solve(const vector<uint32_t>& D, const string& Ls, const string& Rs)
{
    const uint32_t k = D.size();
    vector<uint32_t> Dr(k+1);
    partial_sum(D.begin(), D.end(), Dr.begin()+1);
    auto extended = [&](const string& S) {
        vector<uint32_t> E;
        for(uint32_t i = 0; i < S.size(); i++)
        {
            if(S[i] == '0' or S[i] == '1')
                E.push_back(S[i] - '0');
            else
            {
                uint32_t a = S[i] - 'a';
                for(uint32_t j = 0; j < D[a]; j++)
                    E.push_back(Dr[a] + j + 2);
            }
        }
        return E;
    };
    vector<uint32_t> L = extended(Ls), R = extended(Rs);
    uint32_t n = L.size(), n2 = R.size();
    if(n != n2)
        return 0;
    vector<vector<uint32_t>> G(v);
}

int main()
{
  uint32_t cases;
  cin >> cases;
  while(cases --> 0)
  {
    uint32_t k;
    cin >> k;
    vector<uint32_t> D(k);
    for(uint32_t i = 0; i < k; i++)
        cin >> D[i];
    const uint32_t v = Dr[k] + 2;
    uint32_t _; string Ls, Rs;
    cin >> _ >> Ls >> _ >> Rs;
    cout << solve(D, Ls, Rs) << "\n";
  }
}
