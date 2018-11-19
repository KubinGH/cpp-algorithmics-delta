#include <bits/stdc++.h>

using namespace std;

uint32_t log2floor(uint32_t n) { return 31 - __builtin_clz(n); }
uint64_t log2floor(uint64_t n) { return 63 - __builtin_clz(n); }

template<typename Arg, typename MonoOperation>
Arg first_true(Arg lo, Arg hi, MonoOperation f)
{
    while(lo < hi)
    {
        Arg mid = (lo + hi) / 2;
        if(f(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

template<typename T>
struct wavelet_tree
{
    struct wavelet_node
    {
        size_t n;
        T a, b;
        vector<bool> B;
        const size_t s = 32;
        vector<size_t> Bc;
        wavelet_node *left, *right;
        template<typename Iterator>
        wavelet_node(Iterator first, Iterator last, T _a, T _b)
            : n(distance(first, last)), a(_a), b(_b), B(n)
        {
            T c = a + (b-a)/2;
            size_t v[2] = {0, 0};
            auto itc = first;
            for(size_t i = 0; i < n; i++, itc++)
                B[i] = (*itc > c), v[B[i]]++;
            Bc.reserve(n/s+4); Bc = {0, 0};
            for(size_t i = 0, j = 0; i < n; i++, j++)
            {
                if(j == s)
                    Bc.push_back(Bc.back()), j = 0;
                if(B[i] == 0)
                    Bc.back()++;
            }
            if(a < b)
            {
                auto mid = stable_partition(first, last, [c](uint32_t x) { return x <= c; });
                left = first == mid ? nullptr : new wavelet_node(first, mid, a, c);
                right = mid == last ? nullptr : new wavelet_node(mid, last, c+1, b);
            }
        }
        size_t rank0(size_t i)
        {
            size_t r = Bc[i/s];
            for(uint32_t j = (i/s)*s; j < i; j++)
                if(B[j] == 0)
                    r++;
            return r;
        }
        size_t rank1(size_t i) { return i - rank0(i); }
        size_t select0(size_t x)
            { return first_true(0, n, [x](size_t i) { return rank0(i+1) >= x; }); }
        size_t select1(size_t x)
            { return first_true(0, n, [x](size_t i) { return rank1(i+1) >= x; }); }
        size_t count_greater_or_equal(size_t i, T k)
        {
            if(b < k)
            {
                //cerr << "([" << a << ".." << b << "]" << ", " << i << ", " << k << ") := " << 0 << endl;
                return 0;
            }
            else if(a >= k)
            {
                //cerr << "([" << a << ".." << b << "]" << ", " << i << ", " << k << ") := " << i << endl;
                return i;
            }
            else
            {
                size_t r = 0;
                if(left != nullptr)
                    r += left->count_greater_or_equal(rank0(i), k);
                if(right != nullptr)
                    r += right->count_greater_or_equal(rank1(i), k);
                /*
                for(uint32_t j = 0; j < n; j++)
                    cerr << B[j]; cerr << endl;
                cerr << "([" << a << ".." << b << "]" << ", " << i << ", " << k << ") := " << r << endl;
                */
                return r;
            }
        }
    } *root;
    T a, b;
    template<typename Iterator>
    wavelet_tree(Iterator first, Iterator last,
                 T _a = numeric_limits<T>::min(),
                 T _b = numeric_limits<T>::max()) : a(_a), b(_b)
    {
        vector<T> S(first, last);
        root = new wavelet_node(S.begin(), S.end(), a, b);
    }
    size_t count_greater_or_equal(size_t i, size_t j, T k)
        { return root->count_greater_or_equal(j, k) - root->count_greater_or_equal(i, k); }
    size_t count_greater(size_t i, size_t j, T k)
        { return count_greater_or_equal(i, j, k+1); }
};

std::mt19937 gen{std::random_device{}()};
template<typename T>
T randint(T a, T b)
    { return std::uniform_int_distribution<T>{a, b}(gen); }

//#define DEBUG

int main()
{
    gen.seed(42);
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n);
    uint32_t X = 16;
    #ifdef DEBUG
    ofstream t("t.txt");
    for(uint32_t i = 0; i < n; i++)
        A[i] = randint(1u, X), t << A[i] << " ", cout << A[i] << " ";
    t.close();
    #else
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    #endif // DEBUG
    uint32_t minim = *min_element(A.begin(), A.end()), maxim = *max_element(A.begin(), A.end());
    wavelet_tree<uint32_t> W(A.begin(), A.end(), minim, maxim);
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint32_t i, j, k;
        #ifdef DEBUG
        i = randint(0u, n); j = randint(0u, n);
        if(i>j) swap(i, j);
        k = randint(1u, X);
        cout << i << " " << j << " " << k << endl;
        uint32_t r1 = W.count_greater(i, j, k), r2 = 0;
        for(uint32_t p = i; p < j; p++)
            if(A[p] > k)
                r2++;
        cout << r1 << " " << r2 << endl;
        assert(r1 == r2);
        #else
        cin >> i >> j >> k; i--;
        cout << W.count_greater(i, j, k) << "\n";
        #endif
    }
}
