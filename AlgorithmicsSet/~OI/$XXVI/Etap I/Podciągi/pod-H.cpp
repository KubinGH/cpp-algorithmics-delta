#include <bits/stdc++.h>

using namespace std;

const size_t MAX = (1 << 20) + (1 << 18), QMAX = 1 << 16, A = 60, N = 1000;
const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz"
                       "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                       "0123456789";

struct primes_module_t
{
    bitset<MAX> is_prime;
    vector<uint32_t> primes;
    primes_module_t() : is_prime(), primes()
    {
        cerr << "Sieve ... ";
        is_prime.set(); is_prime[0] = is_prime[1] = false;
        primes.reserve(1024);
        for(uint32_t i = 1; i < MAX; i++)
        {
            if(is_prime[i] and i <= 1000) primes.push_back(i);
            if(i != 1) for(uint32_t x = 2*i; x < MAX; x += i)
                is_prime[x] = false;
        }
        cerr << "done" << endl;
    }
    vector<uint32_t> find_divs(uint32_t x)
    {
        vector<uint32_t> r;
        for(uint32_t i = 1; i*i <= x; i++)
            if(x % i == 0)
                r.push_back(i);
        for(uint32_t i = r.size(); i --> 0; )
            if(r[i] * r[i] != x)
                r.push_back(x / r[i]);
        return r;
    }
} Sieve;

const uint32_t LIM = 1 << 13, CNT = 8;
typedef array<uint16_t, CNT> pattern_arr_t;
typedef pair<int32_t, pattern_arr_t> pattern_t;

namespace std
{
    template<>
    struct hash<pair<uint16_t, uint16_t>>
    {
        size_t operator()(const pair<uint16_t, uint16_t>& k) const
        {
            return (size_t(k.first) << 16) | size_t(k.second);
        }
    };
}

// [(x, a), (y, b), {r}, (x, c), (y, d), (x, e), (y, f)]
struct pattern_finder_module_t
{
    unordered_map<pair<uint16_t, uint16_t>, pattern_t> congo;
    vector<bool> valid;
    pattern_finder_module_t() : congo(), valid(LIM)
    {
        cerr << "Pattern finder ... ";
        congo.reserve(1 << 25);
        congo[{2, 0}] = {0, {{1, 0, 0, 0, 0, 0, 0, 0}}};
        #define for_in_range(_i, _lo, _hi) for((_i) = (_lo); (_i) < (_hi); (_i)++)
        uint16_t a, b, c, d, e, f, g, h;
        for_in_range(a, 0, 11) for_in_range(b, 0, 11)
          for_in_range(c, 0, 11) for_in_range(d, 0, 11)
            for_in_range(e, 0, 10) for_in_range(f, 0, 10)
              for_in_range(g, 0, 10) for_in_range(h, 0, 10)
        {
            int32_t ct[2] = {int32_t((a+1)*(b+1)), 0};
            int32_t ls[2][2] = {{0, int32_t(a)}, {0, int32_t((a+1)*b)}};
            pattern_arr_t arr = {{a, b, c, d, e, f, g, h}};
            for(uint32_t i = 2; i < arr.size(); i++)
            {
                int32_t cc[2] = {ct[0], ct[1]};
                for(uint32_t p = 0; p < 2; p++)
                {
                    ct[p] = cc[p] + (cc[p] - ls[i%2][p]) * int32_t(arr[i]);
                    ls[i%2][p] = cc[p] + (cc[p] - ls[i%2][p]) * int32_t(arr[i] - 1);
                }
            }
            uint32_t x = ct[0], y = (ct[0] + ct[1]%ct[0]) % ct[0];
            if(x != 1 and x < LIM)
            {
                pair<uint16_t, uint16_t> key = {uint16_t(x), uint16_t(y)};
                if(congo.find(key) == congo.end() or
                   accumulate(arr.begin(), arr.end(), 0)
                    < accumulate(congo[key].second.begin(), congo[key].second.end(), 0))
                {
                    valid[x] = true;
                    congo[key] = {ct[1], arr};
                }
            }
        }
        #undef for_in_range
        cerr << "done (found " << congo.size() << " pairs)" << endl;
        uint64_t s = 0, mx = 0;
        for(auto k : congo)
        {
            uint64_t x = accumulate(k.second.second.begin(), k.second.second.end(), 0);
            s += x;
            mx = max(mx, x);
        }
        cerr << "avg " << double(s)/congo.size() << "; max " << mx << endl;
    }
    pair<uint64_t, pattern_arr_t> find_pattern_for(uint64_t n)
    {
        if(n % 2 == 0)
            return {n/2, congo[{2, 0}].second};
        for(uint32_t i = 2; i < (uint32_t)min(n, (uint64_t)LIM); i++)
        {
            if(not valid[i]) continue;
            auto it = congo.find({i, n%i});
            if(it != congo.end())
            {
                return {(n-it->second.first)/i, it->second.second};
            }
        }
        return {-1llu, {}};
    }
} Patterns;

uint64_t verify(char* it)
{
    size_t n = strlen(it);
    vector<uint64_t> dp(n+2);
    vector<size_t> ls(256);
    dp[0] = 0; dp[1] = 1;
    for(uint32_t i = 0; i < n; i++)
    {
        dp[i+2] = 2*dp[i+1] - dp[ls[it[i] - CHAR_MIN]];
        ls[it[i] - CHAR_MIN] = i+1;
    }
    return dp.back();
}

pair<char*, size_t> deduce_solution(uint64_t n, char* out, size_t alpha = 0)
{
    if(n < 8 or n == 17)
    {
        for(uint32_t i = 0; i < n-1; i++)
            *out++ = ALPHABET[alpha];
        return {out, alpha+1};
    }
    if(n % 2 == 0)
    {
        *out++ = ALPHABET[alpha++];
        return deduce_solution(n/2, out, alpha);
    }
    if(n % 4 == 3)
    {
        size_t before = alpha++;
        *out++ = ALPHABET[before];
        tie(out, alpha) = deduce_solution((n+1)/4, out, alpha);
        *out++ = ALPHABET[before];
        return {out, alpha};
    }
    auto p = Patterns.find_pattern_for(n);
    uint64_t m = p.first; auto v = p.second;
    if(m == -1llu)
    {
        abort();
        return {out, alpha};
    }
    uint32_t first = -1u, second = -1u;
    for(uint32_t i = 0; i < v.size(); i += 2)
        if(v[i] and first == -1u) first = alpha++;
    for(uint32_t i = 1; i < v.size(); i += 2)
        if(v[i] and second == -1u) second = alpha++;
    for(uint32_t k = 0; k < v[0]; k++)
        *out++ = ALPHABET[first];
    for(uint32_t k = 0; k < v[1]; k++)
        *out++ = ALPHABET[second];
    tie(out, alpha) = deduce_solution(p.first, out, alpha);
    for(uint32_t i = 2; i < v.size(); i++)
        for(uint32_t k = 0; k < v[i]; k++)
            *out++ = ALPHABET[i%2 ? second : first];
    return {out, alpha};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        static char buffer[QMAX];
        uint64_t n;
        cin >> n;
        char* last;
        vector<uint32_t> F; uint64_t m = n; uint32_t s = 0;
        for(uint32_t p : Sieve.primes)
            while(m % p == 0) m /= p, F.push_back(p), s += p;
        if(s <= 1000 and n > 1e6 and m == 1)
        {
            char* out = buffer;
            for(uint32_t a = 0; a < F.size(); a++)
                for(uint32_t p = 0; p < F[a]-1; p++)
                    *out++ = ALPHABET[a];
            last = out;
        }
        else
            last = deduce_solution(n, buffer).first;
        *last = '\0';
        //assert(n == verify(buffer));
        cout << buffer << "\n";
    }
}
