#include <bits/stdc++.h>

// Kubin's Template Library (tm)

using namespace std;

// Value scaler
// Map-based instead of overwrite
template<typename T, size_t N>
struct value_scaler
{
    T _A[N];
    unordered_map<T, size_t> M;
    template<typename Iterator>
    value_scaler(Iterator begin, Iterator end)
    {
        size_t n = 0;
        for(auto it = begin; it != end; it++)
            _A[n] = *it, n++;
        sort(_A, _A + n);
        M.reserve(2*n);
        for(size_t i = 0, f = 0; i < n; i++)
        {
            if(i > 0 and _A[i-1] == _A[i])
                f++;
            M[_A[i]] = i - f;
        }
    }
    const size_t& operator[] (const T& x)
    {
        return M[x];
    }
};

// Disjoint-set data structure (Find and Union)
template<size_t N>
struct disjoint_set
{
    array<size_t, N> parent, nrank;
    disjoint_set(size_t init = N)
    {
        iota(parent.begin(), parent.begin() + init, 0);
    }
    void unite(size_t first_node, size_t second_node)
    {
        size_t first = find_root(first_node),
               second = find_root(second_node);
        if(nrank[second] > nrank[first])
        {
            parent[first] = second;
            nrank[second]++;
        }
        else
        {
            parent[second] = first;
            if(nrank[first] == nrank[second])
                nrank[first]++;
        }
    }
    size_t find_root(size_t node)
    {
        if(parent[node] == node)
            return node;
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
};

// Segment tree, point set, interval query
// Note: root in 0
template<typename T, size_t N, T(*F)(T, T), T NONE>
struct segment_tree
{
    array<T, N> values;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
    }
    void set(size_t i, T value)
    {
        i += offset();
        values[i] = value;
        while(i > 0)
            i = parent(i), values[i] = F(values[left(i)], values[right(i)]);
    }
    // recursion
    T get(size_t i, size_t tbegin, size_t tend,
                    size_t sbegin, size_t send)
    {
        if(tend < sbegin or send < tbegin)
            return NONE;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return F(get(left(i),  tbegin, (tbegin+tend)/2, sbegin, send),
                     get(right(i), (tbegin+tend)/2+1, tend, sbegin, send));
    }
    // iterative
    T get(size_t sbegin, size_t send)
    {
        //return get(0, 0, N/2 - 1, sbegin, send);
        send++;
        T result = NONE;
        for(sbegin += offset(), send += offset(); sbegin < send;
            sbegin = parent(sbegin), send = parent(send))
        {
            if(sbegin % 2 == 0) result = F(result, values[sbegin++]);
            if(send % 2 == 0)   result = F(result, values[--send]);
        }
        return result;
    }
    const T& operator[] (size_t i) const
    {
        return values[offset() + i];
    }
};


// Segment tree, interval set, interval query
// (set new max on interval, query sum on interval)
// Designed with customability in mind
// F: vertex value function for values of children.
// P: apply changes from to_set. If to_set is SET_NONE, it should do nothing.
// S: merge set values, e.g. during add this function is addition,
//    and during set-max this is maximum.
//    NOTE: F is used by default, but will not be enough in many cases.
//          (e.g. in a add-interval/max tree)
//    Note that the previous set value is the first argument,
//    and the new is second.
template<typename T, size_t N, T(*F)(T, T), T NONE,
        void(*P)(size_t, size_t, size_t, array<T, N>&, array<T, N>&), T SET_NONE,
        T(*S)(T, T) = F>
struct segment_tree_i
{
    array<T, N> values, to_set;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree_i()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
        fill(to_set.begin(), to_set.end(), SET_NONE);
    }
    void pull(size_t i, size_t tbegin, size_t tend)
    {
        if(to_set[i] != SET_NONE)
        {
            P(i, tbegin, tend, values, to_set);
            to_set[i] = SET_NONE;
        }
    }
    void set(size_t i, size_t tbegin, size_t tend,
                       size_t sbegin, size_t send, T value)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_set[i] = S(to_set[i], value);
            pull(i, tbegin, tend);
        }
        else
        {
            set(left(i),  tbegin, (tbegin+tend)/2, sbegin, send, value);
            set(right(i), (tbegin+tend)/2+1, tend, sbegin, send, value);
            values[i] = F(values[left(i)], values[right(i)]);
        }
    }
    void set(size_t sbegin, size_t send, T value)
        { return set(0, 0, N/2 - 1, sbegin, send, value); }
    T get(size_t i, size_t tbegin, size_t tend,
                    size_t sbegin, size_t send)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return NONE;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return F(get(left(i),  tbegin, (tbegin+tend)/2, sbegin, send),
                     get(right(i), (tbegin+tend)/2+1, tend, sbegin, send));
    }
    T get(size_t sbegin, size_t send)
        { return get(0, 0, N/2 - 1, sbegin, send); }
};

// Hashing
// Mods: 1e9+7, 1e9+11, 1e9+21, 1e9+33
template<typename T, T MOD, T BASE, size_t N>
struct rolling_hash
{
    T H[N];
    T base_pow[N];
    size_t n;
    template<typename Iterator>
    rolling_hash(Iterator begin, Iterator end, T fix = 0)
    {
        n = distance(begin, end);
        Iterator it = begin;
        for(uint32_t i = 0; i < n; i++)
        {
            if(i > 0)
                H[i] = H[i-1] * BASE, H[i] %= MOD;
            H[i] += T(*it) + fix;
            H[i] %= MOD;

            if(i > 0)
                base_pow[i] = (base_pow[i-1] * BASE) % MOD;
            else
                base_pow[i] = 1;
            it++;
        }
    }
    const T& operator[] (size_t i) const { return H[i]; }
    T operator() (size_t i, size_t j) const
    {
        if(i == 0)
            return H[j];
        else
            return (2*MOD + H[j] - ((H[i-1]*base_pow[j - i + 1]) % MOD)) % MOD;
    }
};

// Binary search
// Note: faster than STL's std::lower_bound, std::upper_bound
uint32_t own_lower_bound(uint32_t A[], size_t n, uint32_t a)
{
    uint32_t lo = 0, hi = n;
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        if(A[mid] >= a)
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}
uint32_t own_upper_bound(uint32_t A[], size_t n, uint32_t a)
{
    uint32_t lo = 0, hi = n;
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        if(A[mid] > a)
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

// Constants: pi, phi
const long double A_PI = acos(-1.0L);
const long double PHI = (1 + sqrt(5)) / 2;

// Golden section method
// Work on functions with exactly one extremum
double function_minimum(double(*F)(double), double lo, double hi,
                        uint32_t iterations)
{
    double a = lo, b = hi, c = b - (b-a)/PHI, d = a + (b-a)/PHI;
    for(uint32_t k = 0; k < iterations; k++)
    {
        if(F(c) < F(d))
            b = d;
        else
            a = c;
        c = b - (b-a)/PHI;
        d = a + (b-a)/PHI;
    }
    return (a + b) / 2;
}
double function_maximum(double(*F)(double), double lo, double hi,
                        uint32_t iterations)
{
    double a = lo, b = hi, c = b - (b-a)/PHI, d = a + (b-a)/PHI;
    for(uint32_t k = 0; k < iterations; k++)
    {
        if(F(c) > F(d))
            b = d;
        else
            a = c;
        c = b - (b-a)/PHI;
        d = a + (b-a)/PHI;
    }
    return (a + b) / 2;
}


// LCA and jump pointers
// Construction
// (assumes current vertex v, and none value -1u):
/*
```
for(uint32_t i = 1; i < JUMP_POINTERS; i++)
{
    uint32_t x = J[v][i-1];
    if(x == -1u) break;
    J[v][i] = J[x][i-1];
}
```
*/
template<size_t JUMP_POINTERS, size_t MAX>
uint32_t lca(const array<array<uint32_t, JUMP_POINTERS>, MAX>& J,
             const array<uint32_t, MAX>& D,
             uint32_t u, uint32_t v)
{
    if(D[u] < D[v])
        swap(u, v);
    for(uint32_t i = JUMP_POINTERS; i --> 0;)
        if(J[u][i] != -1u and D[J[u][i]] >= D[v])
            u = J[u][i];
    if(u == v)
        return u;
    for(uint32_t i = JUMP_POINTERS; i --> 0;)
    {
        if(J[u][i] != J[v][i] and J[u][i] != -1u)
            u = J[u][i], v = J[v][i];
    }
    return J[u][0];
}


template<typename T>
constexpr T log2floor(T n)
{
    return (numeric_limits<T>::digits-1) - __builtin_clz(n);
}

// Fenwick tree - O(2n) = O(n) construction, O(1) queries.
// Note: memory usage is not optimized in this implementation
// (O(n log n) instead of O(n))
// A.k.a. power tree.
// Requires F(a, b) == F(F(a, b), b), and F(a, b) == F(b, a)
// Examples: min, max, and, or
template<typename T, size_t N, T(*F)(T, T)>
struct fenwick_tree
{
    size_t n, t;
    array<array<T, N>, log2floor(N)+1> A;
    template<typename Iterator>
    fenwick_tree(Iterator tbegin, Iterator tend)
    {
        size_t i = 0;
        for(auto it = tbegin; it != tend; it++, i++)
            A[0][i] = *it;
        n = i;
        t = log2floor(n)+1;
        for(size_t i = 1; i < t and (1u << i) <= n + 1; i++)
            for(size_t j = 0; j < n + 1 - (1 << i); j++)
                A[i][j] = F(A[i-1][j], A[i-1][j + (1u << (i-1))]);
    }
    T operator() (size_t a, size_t b)
    {
        uint32_t p = log2floor(b - a + 1);
        return F(A[p][a], A[p][b + 1 - (1 << p)]);
    }
};

// Randomization utility
// random_device{}() - randomizes seed
// uniform_int_distribution<T>{a, b} - uses the generator.
// Works on any range contained in numeric_limits<T>::min(), ~::max()
// Use gen.seed() before usage, with some random integer
//      (time(0) should be enough)
mt19937 gen{random_device{}()};
template<typename T>
T randint(T a, T b)
    { return uniform_int_distribution<T>{a, b}(gen); }


template<typename T, size_t W, size_t H, T MOD = 0>
struct matrix
{
    T A[W*H];
    size_t w = W, h = H;
    matrix(size_t w, size_t h) : w(w), h(h) { fill(A, A+w*h, 0); }
    matrix() : matrix(W, H) {}
    template<size_t AW, size_t AH>
    matrix(const T(&Q)[AH][AW])
    {
        w = AW; h = AH;
        for(size_t y = 0; y < AH; y++)
            for(size_t x = 0; x < AW; x++)
                (*this)(x, y) = Q[y][x];
    }
    T& operator() (size_t x, size_t y) { return A[w*y+x]; }
    T& operator[] (size_t i) { return A[i]; }
    template<size_t L>
    matrix<T, L, H, MOD> operator* (matrix<T, L, W, MOD>& o)
    {
        matrix<T, L, H, MOD> r(o.w, h);
        for(size_t x = 0; x < o.w; x++)
          for(size_t y = 0; y < h; y++)
            for(size_t i = 0; i < max(w, o.h); i++)
        {
            r(x, y) += (*this)(i, y) * o(x, i);
            if(MOD != 0)
                r(x, y) %= MOD;
        }
        return r;
    }
    matrix& operator*= (matrix& o)
        { return (*this = operator*(o)); }
    template<typename PT>
    matrix<T, W, H, MOD> operator^ (PT p)
    {
        matrix<T, W, H, MOD> r, a;
        if(p > 0)
            r = a = *this;
        while(p)
        {
            if(p % 2 == 1)
                r *= a;
            p /= 2;
            a *= a;
        }
        return r;
    }
    template<typename PT>
    matrix& operator^= (PT p)
        { return (*this = operator^(p)); }
};

template<typename Iterator, class T = typename iterator_traits<Iterator>::value_type >
vector<uint32_t> manacher(Iterator first, Iterator last, T leaf = '$')
{
    vector<T> A(distance(first, last)*2 + 1);
    for(auto it = A.begin(); first != last; first++)
    {
        *it++ = leaf;
        *it++ = *first;
    }
    A.back() = '$';
    vector<uint32_t> P(A.size(), 0);
    uint32_t right = 0, center = 0;
    for(uint32_t i = 1; i < A.size(); i++)
    {
        uint32_t mirror = 2*center - i;
        if(i + P[mirror] <= min(right, A.size() - 1))
            P[i] = P[mirror];
        while(i >= P[i]+1 and i+P[i]+1 < A.size()
              and A[i-P[i]-1] == A[i+P[i]+1])
            P[i]++;
        if(i + P[i] > right)
        {
            center = i;
            right = center + P[i];
        }
    }
    for(uint32_t i = 0; i < A.size(); i++)
        P[i] = P[i]/2 + i%2;
    return P;
}

int main()
{
    cout << "Transmission interpreted successfully" << endl;
    matrix<uint64_t, 2, 2> M({{0LLU, 1LLU}, {5LLU, 3LLU}});
    matrix<uint64_t, 1, 2> V({{1LLU}, {2LLU}});
    cout << ((M^5) * V)(0, 0);
}
