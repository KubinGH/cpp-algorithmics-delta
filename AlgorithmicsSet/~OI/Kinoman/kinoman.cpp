#include <cstdio>
#include <cctype>
#include <array>
#include <tuple>
#ifndef _WIN32
#define getchar getchar_unlocked
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

using namespace std;

const size_t MAX = 1e6, TSIZE = 1 << 21;

char FCHAR;
template<typename T>
void load_dec_unsafe(T& x)
{
    while(isdigit(FCHAR = getchar()))
        x *= 10, x += FCHAR - '0';
}

template<typename T, size_t N, T(*F)(T, T), T NONE, T SET_NONE,
        T(*S)(T, T) = F>
struct segment_tree_intervalop
{
    array<T, N> values, to_set;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    inline size_t offset() const { return N/2; }
    segment_tree_intervalop()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[2*i], values[2*i+1]);
        fill(to_set.begin(), to_set.end(), SET_NONE);
    }
    void pull(size_t i, size_t tbegin, size_t tend)
    {
        if(tbegin < tend)
        {
            to_set[2*i] += to_set[i];
            to_set[2*i+1] += to_set[i];
        }
        values[i] += to_set[i];
        to_set[i] = SET_NONE;
    }
    size_t sbegin, send; T value;
    void _set(size_t i, size_t tbegin, size_t tend)
    {
        if(to_set[i] != SET_NONE) pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_set[i] = S(to_set[i], value);
            pull(i, tbegin, tend);
        }
        else
        {
            _set(2*i,  tbegin, (tbegin+tend)/2);
            _set(2*i+1, (tbegin+tend)/2+1, tend);
            values[i] = F(values[2*i], values[2*i+1]);
        }
    }
    void set(size_t _sbegin, size_t _send, T svalue)
        { sbegin = _sbegin; send = _send; value = svalue; return _set(1, 0, N/2 - 1); }
};
int64_t max_i64(int64_t a, int64_t b) { return a>b ? a : b; }
int64_t add_i64(int64_t a, int64_t b) { return a + b; }


int main()
{
    uint32_t n = 0, m = 0;
    load_dec_unsafe(n); load_dec_unsafe(m);
    static uint32_t id[MAX];
    for(uint32_t i = 0; i < n; i++)
        load_dec_unsafe(id[i]), id[i]--;
    static int64_t value[MAX];
    for(uint32_t i = 0; i < m; i++)
        load_dec_unsafe(value[i]);
    static segment_tree_intervalop<
        int64_t, TSIZE, max_i64, 0, 0, add_i64
    > result_tree;
    static pair<uint32_t, uint32_t> last_segment[MAX];
    for(uint32_t i = 0; i < m; i++)
        last_segment[i] = make_pair(n, n);
    int64_t result = 0;
    for(uint32_t i = n; i --> 0; )
    {
        uint32_t j, k;
        tie(j, k) = last_segment[id[i]];
        result_tree.set(j, k, -value[id[i]]);
        result_tree.set(i, j-1, value[id[i]]);
        last_segment[id[i]] = make_pair(i, j-1);
        result = max(result, result_tree.values[1]);
    }
    printf(LL_FMT, result);
}
