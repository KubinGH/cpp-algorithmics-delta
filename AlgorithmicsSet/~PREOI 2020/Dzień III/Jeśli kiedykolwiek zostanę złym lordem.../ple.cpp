#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>

using namespace std;

struct query
{
    size_t i, L, R;
    uint w;
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<uint> A(n);
    for(auto& a : A)
        cin >> a;

    size_t q;
    cin >> q;

    vector<query> Q(q);
    uint m = 1;
    for(size_t i = 0; i < q; i++)
    {
        Q[i].i = i;
        cin >> Q[i].L >> Q[i].R >> Q[i].w;
        Q[i].L--;
        m = max(m, Q[i].w);
    }

    sort(Q.begin(), Q.end(), [&](const query& lhs, const query& rhs) {
        return tie(lhs.R, lhs.L) < tie(rhs.R, rhs.L);
    });

    vector<size_t> K(m+1, SIZE_MAX);
    K[0] = n;

    vector<bool> D(q);

    size_t R = 0;
    for(const auto& c : Q)
    {
        while(R < c.R)
        {
            auto a = A[R];
            for(size_t i = m+1; i --> a + 1; )
                if(K[i - a] != SIZE_MAX and (K[i] == SIZE_MAX or K[i] < K[i - a]))
                    K[i] = K[i - a];
            if(a <= m)
                K[a] = R;
            R++;
        }

        D[c.i] = (K[c.w] != SIZE_MAX and K[c.w] >= c.L);
    }

    for(size_t i = 0; i < q; i++)
        cout << (D[i] ? "TAK\n" : "NIE\n");
 }
