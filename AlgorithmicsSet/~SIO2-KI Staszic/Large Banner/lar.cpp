#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint64_t M, N, L, H, B;
    cin >> M >> N >> L >> H >> B;
    const uint64_t Ld = L*L, Hd = H*H;

    uint64_t lim = max(N, M);
    vector<vector<uint32_t>> divisors(lim+1);
    vector<int8_t> Mu(lim+1); Mu[1] = 1;
    for(uint32_t d = 1; d <= lim; d++)
    {
        divisors[d].push_back(d);
        for(uint32_t x = 2*d; x <= lim; x += d)
            Mu[x] -= Mu[d], divisors[x].push_back(d);
    }

    auto psi_sum = [&](uint64_t x, uint64_t Y) {
        uint64_t r = 0;
        for(uint64_t d : divisors[x])
        {
            uint64_t rd = ((Y-1)/d) * (N+1) - d * ((Y-1)/d) * (((Y-1)/d)+1) / 2;
            r += (rd * (B + Mu[d])) % B;
        }
        return ((r % B) * ((M+1) - x)) % B;
    };

    uint64_t result = 0;
    if(L == 1)
        result = (M + 1) * N + (N + 1) * M;
    for(uint64_t x = 1; x <= M and x < H; x++)
    {
        uint64_t y1 = 1, y2 = N;
        if(x*x < Ld)
            y1 = (uint64_t)ceil(sqrt(Ld - x*x));
        if(x*x < Hd)
            y2 = min(N, (uint64_t)floor(sqrt(Hd - x*x)));
        if(y1 <= y2)
            result += 2 * (B + psi_sum(x, y2+1) - psi_sum(x, y1));
    }
    cout << result % B;
}
