#include <bits/stdc++.h>

using namespace std;

template<typename T>
vector<T> vslice(const vector<T>& vec, size_t first, size_t last, size_t step)
{
    vector<T> out;
    out.reserve((last - first) / step);
    for(size_t i = first; i < last; i += step)
        out.push_back(vec[i]);
    return out;
}

vector<uint64_t> ntt(const vector<uint64_t>& A, uint64_t w, uint64_t mod)
{
    const uint32_t n = A.size();
    if(n == 1)
        return {A[0]};
    auto A0 = vslice(A, 0, A.size(), 2), A1 = vslice(A, 1, A.size(), 2);
    auto Y0 = ntt(A0, (w * w) % mod, mod), Y1 = ntt(A1, (w * w) % mod, mod);
    vector<uint64_t> Y(n);
    uint64_t wi = 1;
    for(uint32_t k = 0; k < n / 2; k++, wi = (wi * w) % mod)
        Y[k] = (Y0[k] + wi*Y1[k]) % mod;
    for(uint32_t k = 0; k < n / 2; k++, wi = (wi * w) % mod)
        Y[k+n/2] = (Y0[k] + wi*Y1[k]) % mod;
    return Y;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; uint64_t mod, w;
    cin >> n >> mod >> w;
    vector<uint64_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], A[i] %= mod;

    auto Y = ntt(A, w, mod);
    cout << accumulate(Y.begin(), Y.end(), 0ull) % mod << "\n";
    Y.push_back(Y.front()); Y.erase(Y.begin());
    for(auto y : Y)
        cout << y << " ";
}
