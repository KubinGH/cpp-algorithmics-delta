#include <bits/stdc++.h>

using namespace std;

const uint64_t MOD = 1e9 + 7;

struct interval { uint32_t L, R; };

vector<uint32_t> filter_over(const vector<interval>& A)
{
    const uint32_t n = A.size();

    using event_t = tuple<uint32_t, uint32_t, uint32_t>;
    vector<event_t> E(n);
    for(uint32_t i = 0; i < n; i++)
        E[i] = event_t{A[i].R, -A[i].L, i};

    sort(E.begin(), E.end());

    vector<bool> f(n);
    uint32_t maxL = 0; bool any = false;
    for(auto e : E)
    {
        uint32_t i = get<2>(e);
        if(any and maxL >= A[i].L)
            f[i] = true;
        maxL = max(maxL, A[i].L); any = true;
    }
    vector<uint32_t> F; F.reserve(n);
    for(uint32_t i = 0; i < n; i++)
        if(not f[i])
            F.push_back(i);
    return F;
}

struct state_t {  uint32_t opt; uint64_t sum; };
state_t combine(state_t a, state_t b)
{
    if(a.opt < b.opt)
        return {a.opt, a.sum};
    else if(b.opt < a.opt)
        return {b.opt, b.sum};
    else
        return {a.opt, (a.sum + b.sum) % MOD};
}

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  uint32_t z, _;
  cin >> z;
  while(z --> 0)
  {
    uint32_t n;
    cin >> _ >> n;
    vector<interval> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i].L >> A[i].R;

    auto F = filter_over(A);

    uint32_t m = F.size();
    sort(F.begin(), F.end(), [&](uint32_t i, uint32_t j) {
        return A[i].R < A[j].R;
    });
    vector<interval> B(m+1);
    B[0] = {0, 0};
    for(uint32_t i = 0; i < m; i++)
        B[i+1] = A[F[i]];

    vector<uint32_t> O(m+2);
    vector<uint64_t> S(m+2), V(m+2);
    V[0] += B[1].R; S[1] += B[1].R; O[1]++;
    vector<state_t> Q(m+1, {-1u, 0});
    Q[0] = {0, 1};
    for(uint32_t i = 1, j = 0, x = 0; i <= m; i++)
    {
        while(j < i and B[i].L >= B[j].R)
        {
            S[Q[j].opt+1] += MOD - V[j]; S[Q[j].opt+1] %= MOD;
            O[Q[j].opt+1]--;
            j++;
        }
        if(j < i)
        {
            while(x < m and not O[x])
                x++;
            Q[i] = {x, S[x]};
        }
        if(B[j].R > B[i].L)
            Q[i] = combine(Q[i], {Q[j-1].opt + 1, (Q[j-1].sum * (B[j].R - B[i].L)) % MOD});

        if(i < m)
        {
            V[i] = (Q[i].sum * (B[i+1].R - B[i].R)) % MOD;
            S[Q[i].opt+1] += V[i]; S[Q[i].opt+1] %= MOD;
            O[Q[i].opt+1]++;
            x = min(x, Q[i].opt);
        }
    }

    cout << Q.back().opt << " " << Q.back().sum << "\n";
  }
}
