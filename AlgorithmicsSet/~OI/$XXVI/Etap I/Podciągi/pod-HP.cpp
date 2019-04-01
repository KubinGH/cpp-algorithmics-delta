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
    //vector<uint16_t> divs[QMAX];
    primes_module_t()
    {
        cerr << "Sieve ... ";
        is_prime.set(); is_prime[0] = is_prime[1] = false;
        primes.reserve(1024);
        //divs[1].push_back(1);
        for(uint32_t i = 1; i < MAX; i++)
        {
            if(is_prime[i] and i <= 1000) primes.push_back(i);
            for(uint32_t x = 2*i; x < MAX; x += i)
            {
                if(i != 1) is_prime[x] = false;
                //if(x < QMAX and i < 2048 and i*i <= x) divs[x].push_back(i);
            }
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

// [(x, a), (y, b), {r}, (x, c), (y, d), (x, e), (y, f)]
struct pattern_finder_module_t
{
    map<pair<uint16_t, uint16_t>, pattern_t> congo;
    pattern_finder_module_t()
    {
        cerr << "Pattern finder ... ";
        congo[{2, 0}] = {0, {{1, 0, 0, 0, 0, 0, 0, 0}}};
        #define for_in_range(_i, _lo, _hi) for((_i) = (_lo); (_i) < (_hi); (_i)++)
        uint16_t a, b, c, d, e, f, g, h;
        // LIM 1<<13
        //     9: 1893690
        //    10: 2302311
        //    11: 2754500
        //    12: 3113567
        //  13/8: 1765860
        //    13: 3462027
        // LIM 1<<11
        //     9: 280039
        //    13: 373889
        for_in_range(a, 0, 9) for_in_range(b, 0, 9)
          for_in_range(c, 0, 9) for_in_range(d, 0, 9)
            for_in_range(e, 0, 9) for_in_range(f, 0, 9)
              for_in_range(g, 0, 9) for_in_range(h, 0, 9)
        {
            int64_t ct[2] = {int64_t((a+1)*(b+1)), 0};
            int64_t ls[2][2] = {{0, int64_t(a)}, {0, int64_t((a+1)*b)}};
            pattern_arr_t arr = {{a, b, c, d, e, f, g, h}};
            for(uint32_t i = 2; i < arr.size(); i++)
            {
                int64_t cc[2] = {ct[0], ct[1]};
                for(uint32_t p = 0; p < 2; p++)
                {
                    ct[p] = cc[p] + (cc[p] - ls[i%2][p]) * int64_t(arr[i]);
                    ls[i%2][p] = cc[p] + (cc[p] - ls[i%2][p]) * int64_t(arr[i] - 1);
                }
            }
            uint64_t x = ct[0], y = (ct[0] + ct[1]%ct[0]) % ct[0];
            if(x != 1 and x < LIM)
                congo[{uint16_t(x), uint16_t(y)}] = {ct[1], arr};
            if(x >= LIM) break;
        }
        #undef for_in_range
        cerr << "done (found " << congo.size() << " pairs)" << endl;
    }
    pair<uint64_t, pattern_arr_t> find_pattern_for(uint64_t n)
    {
        if(n % 2 == 0)
            return {n/2, congo[{2, 0}].second};
        for(uint32_t i = 2; i < (uint32_t)min(n, (uint64_t)LIM); i++)
        {
            auto it = congo.find({i, n%i});
            if(it != congo.end())
            {
                return {(n-it->second.first)/i, it->second.second};
            }
        }
        return {-1llu, {}};
    }
} Patterns;

enum solution_type { basic, multiply, jump, pattern };
struct solution_desc { solution_type type; uint32_t p, q, r; };

struct preprocessing_module_t
{
    uint32_t W[QMAX];
    solution_desc S[QMAX];
    preprocessing_module_t()
    {
        cerr << "Preprocessing1e6 ... ";
        deque<vector<uint32_t>> div_cache; uint32_t left = 0;
        div_cache.push_back({}); div_cache.push_back({1});
        for(uint32_t n = 2; n < QMAX; n++)
        {
            W[n] = n - 1; S[n] = {basic, -1u, -1u, -1u};
            div_cache.push_back(Sieve.find_divs(n));
            for(uint32_t p : div_cache[n-left])
            {
                if(p != 1 and p != n and W[p] + W[n/p] < W[n])
                    S[n] = {multiply, p, -1u, -1u}, W[n] = W[p] + W[n/p];
            }
            if(n >= 8 and n % 4 == 3 and W[(n+1)/4] + 2 < W[n])
            {
                S[n] = {jump, 1, 1, (n+1)/4};
                W[n] = W[(n+1)/4] + 2;
            }
            if(n > 8)
            {
                auto p = Patterns.find_pattern_for(n);
                if(p.first != -1llu)
                {
                    uint32_t s = accumulate(p.second.begin(), p.second.end(), 0);
                    if(s + W[p.first] < W[n])
                        S[n] = {pattern, -1u, -1u, -1u}, W[n] = s + W[p.first];
                }
            }
            for(uint32_t q = 1; q < min(W[n], 1000u); q++)
            {
                for(uint32_t r_x : div_cache[(n-q)-left])
                {
                    uint32_t upper_r = ((n - q) / r_x + q), lower_r = (q + 1);
                    if(upper_r % lower_r or upper_r == 0) continue;
                    uint32_t r = upper_r / lower_r;
                    if(r >= n) continue;
                    uint32_t upper_p = (n - r*(q + 1)), lower_p = (r*(q + 1) - q);
                    if(upper_p % lower_p or upper_p == 0) continue;
                    uint32_t p = upper_p / lower_p;
                    if(p + q + W[r] < W[n])
                        S[n] = {jump, p, q, r}, W[n] = p + q + W[r];
                }
            }
            while(n >= left+1000)
                div_cache.pop_front(), left++;
        }
        cerr << "done" << endl;
    }
} Pre;


bool is_power_of_two(uint64_t x) { return (x & (x-1)) == 0; }
uint32_t log2floor(uint64_t x) { return 63 - __builtin_clzll(x); }
pair<uint32_t, uint32_t> as_power_of_two_diff(uint64_t x)
{
    uint32_t j = 0;
    while(x % 2 == 0) x /= 2, j++;
    if(is_power_of_two(x+1))
        return {log2floor(x)+j, j};
    else
        return {-1u, -1u};
}

pair<char*, size_t> write_solution(uint64_t n, char* out, size_t alpha = 0)
{
    //cerr << n << endl;
    if(Pre.S[n].type == basic)
    {
        //cerr << " basic" << endl;
        for(uint32_t i = 0; i < n - 1; i++)
            *out++ = ALPHABET[alpha];
        if(n > 1) alpha++;
    }
    else if(Pre.S[n].type == multiply)
    {
        //cerr << " multiply " << S[n].p << endl;
        tie(out, alpha) = write_solution(Pre.S[n].p, out, alpha);
        tie(out, alpha) = write_solution(n / Pre.S[n].p, out, alpha);
    }
    else if(Pre.S[n].type == jump)
    {
        //cerr << " jump " << S[n].p << " " << S[n].q << " " << S[n].r << endl;
        for(uint32_t i = 0; i < Pre.S[n].p; i++)
            *out++ = ALPHABET[alpha];
        uint32_t before = alpha;
        if(Pre.S[n].p or Pre.S[n].q) alpha++;
        tie(out, alpha) = write_solution(Pre.S[n].r, out, alpha);
        for(uint32_t i = 0; i < Pre.S[n].q; i++)
            *out++ = ALPHABET[before];
    }
    else if(Pre.S[n].type == pattern)
    {
        auto p = Patterns.find_pattern_for(n);
        auto v = p.second;
        uint32_t first = -1u, second = -1u;
        for(uint32_t i = 0; i < v.size(); i += 2)
            if(v[i] and first == -1u) first = alpha++;
        for(uint32_t i = 1; i < v.size(); i += 2)
            if(v[i] and second == -1u) second = alpha++;
        for(uint32_t k = 0; k < v[0]; k++)
            *out++ = ALPHABET[first];
        for(uint32_t k = 0; k < v[1]; k++)
            *out++ = ALPHABET[second];
        tie(out, alpha) = write_solution(p.first, out, alpha);
        for(uint32_t i = 2; i < v.size(); i++)
            for(uint32_t k = 0; k < v[i]; k++)
                *out++ = ALPHABET[i%2 ? second : first];
        return {out, alpha};
    }
    *out = '\0';
    return {out, alpha};
}

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
    if(n < 16)
    {
        for(uint32_t i = 0; i < n; i++)
            *out++ = alpha;
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
        assert(n == verify(buffer));
        //cerr << verify(buffer) << endl;
        cout << buffer << "\n";
    }
}
