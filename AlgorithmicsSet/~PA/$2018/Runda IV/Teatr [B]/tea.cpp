#include <bits/stdc++.h>
#include "message.h"

#ifdef XHOVA

#define cdbg cerr
namespace __test_space
{
    #include <ext/numeric>

    //#define TESTI
    //#define TESTR
    #define TEST1
    //#define TEST2

    using namespace std;
    using __gnu_cxx::power;

    template<typename T, T Divisor>
    struct modulo_multiplies
    {
        T operator() (T a, T b) { return (a*b) % Divisor; }
    };
    template<typename T, T Divisor>
    T identity_element(modulo_multiplies<T, Divisor>) { return T(1); }

    namespace teatr {

      bool initialized = false;
      int n;
      #ifdef TESTI
      vector <int> A;
      #endif
      #ifdef TESTR
      constexpr int seed = 15151515, prime = 999983;
      int base, lin;
      modulo_multiplies<int64_t, prime> M;
      #endif

      void init() {
        if(initialized) return;

        #ifdef TESTI
        cin >> n;
        A.resize(n);
        for(int i=0; i<n; i++) cin >> A[i];
        #endif

        #ifdef TESTR
        mt19937 gen = mt19937{seed};
        n = uniform_int_distribution<int>{int(1e7), int(1e8)}(gen);
        base = uniform_int_distribution<int>{1, 1234}(gen);
        lin = uniform_int_distribution<int>{1, 12}(gen);
        #endif

        #ifdef TEST1
        n = 1e8;
        #endif

        initialized = true;
      }

      int GetN() {
        init();
        return n;
      }

      int GetElement(int i) {
        init();
        assert(0 <= i and i < n);
        #ifdef TESTI
        return A[i];
        #endif
        #ifdef TESTR
        int64_t j = i;
        return (prime + (j*lin + j*j*base + power(base, j%127))%prime) % prime;
        #endif
        #ifdef TEST1
        //return (i * 1ll * i) % int(1e6) + 1;
        //return 1 + (((int64_t)i * 27) + i & (i %113) + ((i % 37) ^ (i % 20)) * 3571) % 1000000;
        //return i < 100 * 1000 * 1000 - 3 ? 1 + i / 100 : 100 * 1000 * 1000 - i;
        return (i * 1ll * i) % 10 + 723456;
        #endif // TEST1
      }

    }


    #ifdef __cplusplus
    extern "C" {
    #endif
    int GetN() {
      return teatr::GetN();
    }
    int GetElement(int i) {
      return teatr::GetElement(i);
    }
    #ifdef __cplusplus
    }
    #endif
}
using __test_space::GetN; using __test_space::GetElement;

#else

#define cdbg if(0) cerr
#include "teatr.h"

#endif // XHOVA

using namespace std;

const uint32_t Host = 0, Merger = 1;
const uint32_t A = (1 << 20) - 1, N = 1e8;

struct socket
{
    uint32_t conn;
    socket(uint32_t _conn) : conn(_conn) {}
    void rebind(uint32_t _conn) { conn = _conn; }
    socket& operator+ ()
    {
        uint32_t that = Receive(conn);
        if(conn == -1u) conn = that;
        return *this;
    }
    socket& operator- () { Send(conn); return *this; }
    #define BYTES(_b) template<typename T> typename enable_if<(_b) == sizeof(T), socket&>::type
    BYTES(1) operator<< (T val) { PutChar(conn, val); return *this; }
    BYTES(1) operator>> (T& var) { var = GetChar(conn); return *this; }
    BYTES(4) operator<< (T val) { PutInt(conn, val); return *this; }
    BYTES(4) operator>> (T& var) { var = GetInt(conn); return *this; }
    BYTES(8) operator<< (T val) { PutLL(conn, val); return *this; }
    BYTES(8) operator>> (T& var) { var = GetLL(conn); return *this; }
    #undef BYTES
    socket& operator<< (const string& str)
    {
        for(char c : str) (*this) << c;
        (*this) << '\0';
        return (*this);
    }
    socket& operator>> (string& out)
    {
        out.clear();
        char c; (*this) >> c;
        while(c != '\0') out += c, (*this) >> c;
        return (*this);
    }
};

template<typename T>
constexpr inline T lsb(T x) { return x & (-x); }

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;
    fenwick_tree(size_t _n) : n(_n+1), F(n, 0) {}
    T get_prefix(size_t p) const // Sum in [0, p)
        { T r = 0; while(p) r += F[p], p -= lsb(p); return r; }
    void delta(size_t p, T v)
        { p++; while(p <= n) F[p] += v, p += lsb(p); }

    T get(size_t a, size_t b) const // Get on interval [a, b]
        { return get_prefix(b+1) - get_prefix(a); }
    T get(size_t p) const // Get on point [p]
        { return get(p, p); }
    void set(size_t p, T v)
        { return delta(p, v - get(p)); }
};

uint64_t solve_segment(uint32_t a, uint32_t b)
{
    fenwick_tree<uint32_t> F(A+1);
    uint64_t r = 0;
    for(uint32_t i = a; i < b; i++)
    {
        uint32_t h = GetElement(i);
        r += F.get(h+1, A);
        F.delta(h, 1);
    }
    return r;
}

int main()
{
    const uint32_t n = GetN(), I = NumberOfNodes(), W = I - 2, this_id = MyNodeId();
    if(n < (1 << 20))
    {
        if(this_id == Host)
            cout << solve_segment(0, n);
        return 0;
    }
    vector<uint32_t> node_fragment_len(W), node_fragment(W+1);
    {
        fill(node_fragment_len.begin(), node_fragment_len.end(), n / W);
        for(uint32_t i = 0; i < n - (n/W)*W; i++)
            node_fragment_len[i]++;
        partial_sum(node_fragment_len.begin(), node_fragment_len.end(),
                    node_fragment.begin()+1);
    }
    if(this_id == Host)
    {
        uint64_t r = 0;
        for(uint32_t v = I; v --> 1; )
        {
            uint64_t p;
            cdbg << "Host wait for " << v << endl;
            (+(socket(v))) >> p;
            cdbg << "Host receive from " << v << ", done " << I-v << "/" << I-1 << endl;
            r += p;
        }
        cout << r;
    }
    else if(this_id == Merger)
    {
        static uint32_t elem_count[A+1], ge_elem_count[A+1];
        uint64_t r = 0;
        for(uint32_t v = 0; v < W; v++)
        {
            cdbg << "Merger done job " << v << endl;
            cdbg << "TEST INFO: " << GetElement(node_fragment[v]) << endl;
            const uint32_t a = node_fragment[v], b = node_fragment[v+1];
            for(uint32_t i = a; i < b; i++)
            {
                uint32_t h = GetElement(i);
                r += ge_elem_count[h+1];
                elem_count[h]++;
            }
            uint32_t suffix_count = 0;
            for(uint32_t h = A+1; h --> 0; )
            {
                ge_elem_count[h] += (suffix_count += elem_count[h]);
                elem_count[h] = 0;
            }
        }
        -(socket(Host) << r);
    }
    else // Worker
    {
        const uint32_t worker_id = this_id - 2;
        cdbg << "Worker begin " << worker_id << endl;
        uint64_t r = solve_segment(node_fragment[worker_id], node_fragment[worker_id+1]);
        cdbg << "Worker done " << worker_id << endl;
        -(socket(Host) << r);
    }
}
