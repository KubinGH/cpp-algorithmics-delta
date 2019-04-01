#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 21, QMAX = 1 << 20, A = 60, N = 1000;
const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz"
                       "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                       "0123456789";

enum solution_type { basic, multiply, jump };
struct solution_desc { solution_type type; uint32_t p, q, r; };

static solution_desc S[QMAX];

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
    //cout << n << ": ";
    if(S[n].type == basic)
    {
        //cout << "basic " << endl;
        for(uint32_t i = 0; i < n - 1; i++)
            *out++ = ALPHABET[alpha];
        alpha++;
    }
    else if(S[n].type == multiply)
    {
        //cout << "multiply " << S[n].p << endl;
        tie(out, alpha) = write_solution(S[n].p, out, alpha);
        tie(out, alpha) = write_solution(n / S[n].p, out, alpha);
    }
    else if(S[n].type == jump)
    {
        //cout << "jump " << S[n].p << " " << S[n].q << " " << S[n].r << endl;
        for(uint32_t i = 0; i < S[n].p; i++)
            *out++ = ALPHABET[alpha];
        uint32_t before = alpha++;
        tie(out, alpha) = write_solution(S[n].r, out, alpha);
        for(uint32_t i = 0; i < S[n].q; i++)
            *out++ = ALPHABET[before];
    }
    *out = '\0';
    return {out, alpha};
}

uint32_t verify(char* it, size_t n)
{
    vector<uint32_t> dp(n+2), ls(256);
    dp[0] = 0; dp[1] = 1;
    for(uint32_t i = 0; i < n; i++)
    {
        dp[i+2] = 2*dp[i+1] - dp[ls[it[i] - CHAR_MIN]];
        ls[it[i] - CHAR_MIN] = i+1;
    }
    return dp.back();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static bitset<MAX> is_prime; is_prime.set();
    is_prime[0] = is_prime[1] = false;
    static vector<uint32_t> divs[MAX];
    vector<uint32_t> primes; primes.reserve(256);
    //cout << "begin sieve" << endl;
    for(uint32_t i = 1; i < MAX; i++)
    {
        if(is_prime[i] and i <= 300) primes.push_back(i);
        divs[i].push_back(i);
        for(uint32_t x = 2*i; x < MAX; x += i)
        {
            is_prime[x] = false;
            divs[x].push_back(i);
        }
    }
    //cout << "end sieve" << endl;
    static uint32_t W[QMAX];
    // global solution_desc S[QMAX];
    //cout << "begin preprocessing" << endl;
    for(uint32_t n = 2; n < QMAX; n++)
    {
        W[n] = n - 1; S[n] = {basic, -1u, -1u, -1u};
        for(uint32_t p : divs[n])
        {
            if(p != 1 and p != n and W[p] + W[n/p] < W[n])
                S[n] = {multiply, p, -1u, -1u}, W[n] = W[p] + W[n/p];
        }
        //cout << n << " -> " << W[n];
        //cout << n << ": ";
        /*
        cout << "///" << endl;
        for(uint32_t q = 1; q < min(W[n], 100u); q++)
        {
            for(uint32_t r = 1; r < n and q + W[r] < W[n] and n >= r*(q + 1); r++)
            {
                uint32_t upper = (n - r*(q + 1)), lower = (r*(q + 1) - q);
                if(upper % lower) continue;
                uint32_t p = upper / lower;
                cout << n << ": " << p << " " << q << " " << r << endl;
                if(p + q + W[r] < W[n])
                    S[n] = {jump, p, q, r}, W[n] = p + q + W[r];
            }
        }
        cout << "//" << endl;
        */
        for(uint32_t q = 1; q < min(W[n], 200u) and q <= n; q++)
        {
            for(uint32_t r_x : divs[n - q])
            {
                uint32_t upper_r = ((n - q) / r_x + q), lower_r = (q + 1);
                if(upper_r % lower_r or upper_r == 0) continue;
                uint32_t r = upper_r / lower_r;
                if(r >= n) continue;
                uint32_t upper_p = (n - r*(q + 1)), lower_p = (r*(q + 1) - q);
                if(upper_p % lower_p or upper_p == 0) continue;
                uint32_t p = upper_p / lower_p;
                //cout << n << ": " << p << " " << q << " " << r << endl;
                if(p + q + W[r] < W[n])
                    S[n] = {jump, p, q, r}, W[n] = p + q + W[r];
            }
        }
        //cout << " / " << W[n] << endl;
    }
    //cout << "done preprocessing" << endl;
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        static char buffer[QMAX];
        uint64_t n;
        cin >> n;
        char* last;
        uint32_t i, j; tie(i, j) = as_power_of_two_diff(n);
        vector<uint32_t> F; uint64_t m = n; uint32_t s = 0;
        for(uint32_t p : primes)
            while(m % p == 0) m /= p, F.push_back(p), s += p;
        if(s <= 1000 and n > 1e6 and m == 1)
        {
            char* out = buffer;
            for(uint32_t a = 0; a < F.size(); a++)
                for(uint32_t p = 0; p < F[a]; p++)
                    *out++ = ALPHABET[a];
            last = out;
        }
        if((n > QMAX or i < W[n]) and i != -1u and j != -1u)
        {
            for(uint32_t k = 0; k < i; k++)
                buffer[k] = ALPHABET[k];
            buffer[i] = ALPHABET[j];
            last = buffer + i + 1;
        }
        else
            last = write_solution(n, buffer).first;
        *last = '\0';
        cout << buffer << "\n";
        //assert(verify(buffer, last - buffer) == n and last - buffer <= 1000);
    }
}
