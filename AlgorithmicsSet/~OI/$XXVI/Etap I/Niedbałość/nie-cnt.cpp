#include <bits/stdc++.h>

#include <bits/stdc++.h>

using namespace std;

const uint32_t E = 4;
const char alphabet[E+1] = "ACGT";
uint32_t char_as_index(char x) { return find(alphabet, alphabet + E, x) - alphabet; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string IA, IB;
    cin >> IA >> IB;
    vector<uint32_t> A(IA.size()), B(IB.size());
    for(uint32_t i = 0; i < A.size(); i++)
        A[i] = char_as_index(IA[i]);
    for(uint32_t i = 0; i < B.size(); i++)
        B[i] = char_as_index(IB[i]);
    vector<uint32_t> S, Z;
    for(uint32_t c = 0; c < E; c++)
    {
        // add all characters `c`
        // that don't break the subsequence S
        // FIX ALL OF THIS, THIS USED INDICES
        // INSTEAD OF ELEMENTS
        vector<uint32_t> P, Q;
        auto dzeta = [&](uint32_t iu, uint32_t iv, vector<uint32_t>& I,
                         uint32_t ju, uint32_t jv, vector<uint32_t>& J) {
            //cerr << "dzeta on " << iu << ".." << iv << " " << ju << ".." << jv << endl;
            uint32_t x = 0, y = 0;
            for(uint32_t i = iu; i < iv; i++)
                if(A[i] == c) x++;
            for(uint32_t i = ju; i < jv; i++)
                if(B[i] == c) y++;
            uint32_t _z = min(x, y);
            for(uint32_t z = _z, i = iu; z and i < iv; i++)
                if(A[i] == c) I.push_back(c), z--;
            for(uint32_t z = _z, i = ju; z and i < jv; i++)
                if(B[i] == c) J.push_back(c), z--;
        };
        uint32_t a = 0, b = 0;
        for(uint32_t k = 0; k < S.size(); k++)
        {
            dzeta(a, S[k], P, b, Z[k], Q);
            P.push_back(c); a = S[k] + 1;
            Q.push_back(c); b = Z[k] + 1;
        }
        dzeta(a, A.size(), P, b, B.size(), Q);
        S = P; Z = Q;
        //cerr << alphabet[c] << endl;
        //cerr << "S: "; for(uint32_t s : S) cout << s << " "; cout << endl;
        //cerr << "Z: "; for(uint32_t z : Z) cout << z << " "; cout << endl;
    }
    for(uint32_t i : S)
        cout << alphabet[A[i]];
}
