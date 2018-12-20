#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const int N = 1 << 20;

template<typename T>
struct mod_multiplies : multiplies<T>
{
    T m;
    mod_multiplies(T _m) : m(_m) {}
    T operator() (T a, T b) { return (a*b) % m; }
};

uint32_t S[N], P[2][32];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	uint32_t n; uint64_t m;
    cin >> n >> m;

	for(uint32_t i = 1; i <= n; i++)
    {
		uint32_t x;
		cin >> x;
		uint32_t e = (i-1)%2, a = i%2;
        copy(P[e], P[e] + 32, P[a]);
		S[a] = S[e];
		for(uint32_t j = 0; j < S[a]; j++)
			if(x & (1 << (31 - __builtin_clz(P[a][j]))))
				x ^= P[a][j];
		if(not x)
            continue;

		uint32_t b = 31 - __builtin_clz(x);
		for(uint32_t j = 0; j < S[a]; j++) if(P[a][j] & (1 << b))
			P[a][j] ^= x;

		uint32_t j;
		for(j = S[a]; j --> 0 and P[a][j] < x; )
			P[a][j+1] = P[a][j];
		P[a][j+1] = x, S[a]++;

		j = 0;
		for(uint32_t k = 0; k < S[a]; k++)
			if(P[a][k]) P[a][j++] = P[a][k];
		S[a] = j;
	}

	cout << power(2LLU, n - S[n%2], mod_multiplies<uint64_t>(m));

	return 0;
}
