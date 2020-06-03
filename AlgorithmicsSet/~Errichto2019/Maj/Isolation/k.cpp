#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
const uint MOD = 998244353;

struct block
{
    int lock_lim;
    vector<int>& locks;
    const vector<uint>& value;
    vector<uint64_t> lock_sum;
    uint64_t sum = 0;

    block(size_t n, int k, vector<int>& _locks, const vector<uint>& _value)
        : lock_lim(k), locks(_locks), value(_value), lock_sum(n+1) {}

    void insert(size_t i) { lock_sum[0] += value[i]; sum += value[i]; }
    void push_lock() { if(lock_lim-- >= 0) sum -= lock_sum[lock_lim+1]; }
    void pop_lock()  { if(++lock_lim >= 0) sum += lock_sum[lock_lim]; }
    void push_lock(size_t i)
    {
        lock_sum[locks[i]] -= value[i];
        lock_sum[++locks[i]] += value[i];
        if(locks[i] == lock_lim+1) sum -= value[i];
    }
    void pop_lock(size_t i)
    {
        lock_sum[locks[i]] -= value[i];
        lock_sum[--locks[i]] += value[i];
        if(locks[i] == lock_lim) sum += value[i];
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int k;
    cin >> n >> k;

    vector<size_t> A(n);
    for(size_t& a : A)
        cin >> a, a--;

    vector<uint> Q(n+1);
    Q[0] = 1;

    const size_t m = floor(sqrt(n));

    vector<size_t> prev(n, SIZE_MAX), prev2(n, SIZE_MAX);
    vector<int> locks(n);

    vector<block> blocks;
    for(size_t i = 0; blocks.size() <= (n+1)/m; i++)
        blocks.emplace_back(n, k, locks, Q);


    auto push = [&](size_t a, size_t b) {
        for(size_t j = a; j <= b; j++)
        {
            if(j % m == 0 and j+m-1 <= b)
                blocks[j/m].push_lock(), j += m-1;
            else
                blocks[j/m].push_lock(j);
        }
    };
    auto pop = [&](size_t a, size_t b) {
        for(size_t j = a; j <= b; j++)
        {
            if(j % m == 0 and j+m-1 <= b)
                blocks[j/m].pop_lock(), j += m-1;
            else
                blocks[j/m].pop_lock(j);
        }
    };

    blocks[0].insert(0);
    for(size_t i = 0; i < n; i++)
    {
        if(prev[A[i]] != SIZE_MAX)
            pop(prev2[A[i]]+1, prev[A[i]]);
        push(prev[A[i]]+1, i);

        for(size_t j = 0; j <= i; j++)
        {
            if(j % m == 0 and j+m-1 <= i)
                Q[i+1] = (Q[i+1] + blocks[j/m].sum) % MOD, j += m-1;
            else if(blocks[j/m].locks[j] <= blocks[j/m].lock_lim)
                Q[i+1] = (Q[i+1] + Q[j]) % MOD;
        }
        blocks[(i+1)/m].insert(i+1);

        prev2[A[i]] = prev[A[i]];
        prev[A[i]] = i;
    }

    cout << Q[n] << endl;
}
