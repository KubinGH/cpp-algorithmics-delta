#include <bits/stdc++.h>

using namespace std;

const size_t MAXN = 1<<19;

namespace FFT
{
    // Sources:
    // http://e-maxx.ru/algo/fft_multiply
    // https://github.com/mareksom/acmlib/blob/master/code/blazej/FFT_v2_festfast.cpp
    struct base{
      double re, im;
      base(double r=0., double i=0.) : re(r), im(i) {}

      base operator+(base const& x) const {
        return base(re+x.re,im+x.im);
      }

      base operator-(base const& x) const {
        return base(re-x.re,im-x.im);
      }

      base operator*(base const& x) const {
        return base(re*x.re-im*x.im,re*x.im+im*x.re);
      }

      base operator/(double d) const {
        return base(re/d,im/d);
      }
    };


    const double PI = acos(-1.0);

    int rev[MAXN];
    base wlen_pw[MAXN];

    void fft (base a[], int n, bool invert) {
        for (int i=0; i<n; ++i)
            if (i < rev[i])
                swap (a[i], a[rev[i]]);

        for (int len=2; len<=n; len<<=1) {
            double ang = 2*PI/len * (invert?-1:+1);
            int len2 = len>>1;

            base wlen (cos(ang), sin(ang));
            wlen_pw[0] = base (1, 0);
            for (int i=1; i<len2; ++i)
                wlen_pw[i] = wlen_pw[i-1] * wlen;

            for (int i=0; i<n; i+=len) {
                base t,
                    *pu = a+i,
                    *pv = a+i+len2,
                    *pu_end = a+i+len2,
                    *pw = wlen_pw;
                for (; pu!=pu_end; ++pu, ++pv, ++pw) {
                    t = *pv * *pw;
                    *pv = *pu - t;
                    *pu = *pu + t;
                }
            }
        }

        if (invert)
            for (int i=0; i<n; ++i)
                a[i] = a[i] / n;
    }

    void calc_rev (int n, int log_n) {
        for (int i=0; i<n; ++i) {
            rev[i] = 0;
            for (int j=0; j<log_n; ++j)
                if (i & (1<<j))
                    rev[i] |= 1<<(log_n-1-j);
        }
    }

    void fft (vector<base>& a, bool invert) { return fft(a.data(), a.size(), invert); }

    uint32_t last_rev_n = -1u;
    int* polymul (int* a, uint32_t s_a, int* b, uint32_t s_b, int* output) {
        static base fa[MAXN], fb[MAXN];
        for(uint32_t i = 0; i < s_a; i++) fa[i] = {(double)a[i], 0.0};
        for(uint32_t i = 0; i < s_b; i++) fb[i] = {(double)b[i], 0.0};
        size_t n = 1, k = 0;
        while (n < max (s_a, s_b))  n <<= 1, k++;
        n <<= 1;
        if(last_rev_n != n) last_rev_n = n, calc_rev(n, k+1);
        for(uint32_t i = s_a; i < n; i++) fa[i] = {0.0, 0.0};
        for(uint32_t i = s_b; i < n; i++) fb[i] = {0.0, 0.0};
        fft (fa, n, false),  fft (fb, n, false);
        for (size_t i=0; i<n; ++i)
            fa[i] = (fa[i] * fb[i]);
        fft (fa, n, true);

        for (size_t i=0; i<n; ++i)
            *output++ = int (fa[i].re + 0.5);
        return output;
    }
}

template<typename Iterator>
Iterator pairwise_sums_double(const vector<int>& A, const vector<int>& B,
                              const vector<int>& C, const vector<int>& D, Iterator output)
{
    if((A.empty() and C.empty()) or (B.empty() and D.empty())) return output;
    int lo = min(min(A.empty() ? (1<<30) : A.front(), B.empty() ? (1<<30) : B.front()), min(C.empty() ? (1<<30) : C.front(), D.empty() ? (1<<30) : D.front()));
    int hi = max(max(A.empty() ? 0 : A.back(), B.empty() ? 0 : B.back()), max(C.empty() ? 0 : C.back(), D.empty() ? 0 : D.back()));
    static int P[MAXN], Q[MAXN];
    fill(P, P + hi-lo+1, 0); fill(Q, Q + hi-lo+1, 0);
    for(int a : A) P[a-lo] = 1;
    for(int a : C) P[a-lo] = 1;
    for(int b : B) Q[b-lo] = 1;
    for(int b : D) Q[b-lo] = 1;
    static int R[MAXN];
    int* Re = FFT::polymul(P, hi-lo+1, Q, hi-lo+1, R), *r = R;
    for(uint32_t i = 0; r != Re; ++r, i++)
        if(*r > 0 and (int)i + 2*lo > 0) *output++ = (int)i + 2*lo;
    return output;
}

uint64_t micros()
{
    uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::
                  now().time_since_epoch()).count();
    return us;
}

pair<vector<int>, vector<int>> get_lengths(const vector<int>& A)
{
    uint64_t t1 = micros(), t2;
    uint32_t n = A.size();
    vector<int> E, F; E.reserve(n); F.reserve(n);
    int s = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        s ^= A[i];
        if(s)
            E.push_back(i+1);
    }
    for(uint32_t e = 0; e < E.size(); e++)
        for(uint32_t i = e ? E[e-1]+1 : 0; i < (uint32_t)E[e]; i++)
            F.push_back(i);
    for(uint32_t i = not E.empty() ? E.back()+1 : 0; i <= n; i++)
        F.push_back(i);
    t2 = micros(); cerr << "- 1: " << t2 - t1 << endl;
    vector<int> Em(E.size()), Fm(F.size());
    for(uint32_t i = 0; i < E.size(); i++)
        Em[i] = -E[E.size()-i-1];
    for(uint32_t i = 0; i < F.size(); i++)
        Fm[i] = -F[F.size()-i-1];
    vector<int> V, W; V.reserve(n); W.reserve(n);
    t1 = micros(); cerr << "- 2: " << t1 - t2 << endl;
    pairwise_sums_double(E, Fm, F, Em, back_inserter(V));
    pairwise_sums_double(E, Em, F, Fm, back_inserter(W));
    t2 = micros(); cerr << "- 3: " << t2 - t1 << endl;
    for(uint32_t v : V) cout << v << " "; cout << endl;
    for(uint32_t v : W) cout << v << " "; cout << endl;
    while(not V.empty() and (uint32_t)V.back() > n) V.pop_back();
    while(not W.empty() and (uint32_t)W.back() > n) W.pop_back();
    return {V, W};
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint32_t n, m;
        cin >> n >> m;
        vector<int> A(n), B(m);
        uint64_t t1 = micros(), t2;
        for(uint32_t i = 0; i < n; i++) cin >> A[i], A[i] %= 2;
        for(uint32_t i = 0; i < m; i++) cin >> B[i], B[i] %= 2;
        t2 = micros(); cerr << "1: " << t2 - t1 << endl;
        vector<int> VA, VB, WA, WB, V, W; V.reserve(min(n, m)); W.reserve(min(n, m));
        t1 = micros(); cerr << "2: " << t1 - t2 << endl;
        tie(VA, WA) = get_lengths(A);
        t2 = micros(); cerr << "3: " << t2 - t1 << endl;
        tie(VB, WB) = get_lengths(B);
        t1 = micros(); cerr << "4: " << t1 - t2 << endl;
        set_intersection(VA.begin(), VA.end(), VB.begin(), VB.end(), back_inserter(V));
        t2 = micros(); cerr << "5: " << t2 - t1 << endl;
        set_intersection(WA.begin(), WA.end(), WB.begin(), WB.end(), back_inserter(W));
        t1 = micros(); cerr << "6: " << t1 - t2 << endl;
        cout << max(V.empty() ? 0 : V.back(), W.empty() ? 0 : W.back()) << "\n";
    }
}
