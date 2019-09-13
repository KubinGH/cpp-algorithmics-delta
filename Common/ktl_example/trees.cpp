#include <bits/stdc++.h>

#include <ktl/structures/reduction_tree.cpp>
#include <ktl/structures/sparse_table.cpp>

#define get operator()
#include <ktl/structures/segment_tree.cpp>
#undef get

#include <ktl/math/modular.cpp>

using namespace std;


mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dis(-100, 100);


void test(vector<int> A)
{
    const size_t n = A.size();
    vector<int> S(n + 1);
    partial_sum(A.begin(), A.end(), S.begin() + 1);

    reduction_tree<int, plus<int>> R(A.begin(), A.end());

    for(size_t i = 0; i < n; i++)
      for(size_t j = i; j < n; j++)
    {
        auto p = S[j+1] - S[i], q = R(i, j);
        if(p != q)
            cout << i << ".." << j << ": " << p << " | " << q << endl;
        assert(p == q);
    }
}

uint64_t milliseconds()
{
    return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}

template<typename Call>
pair<result_of_t<Call()>, uint64_t> timed2(Call f)
{
    auto start = milliseconds();
    auto ret = f();
    auto finish = milliseconds();
    return {ret, finish - start};
}
template<typename Call>
uint64_t timed(Call f)
{
    auto start = milliseconds();
    f();
    auto finish = milliseconds();
    return finish - start;
}

template<typename T, typename BinaryOperation>
tuple<uint64_t, uint64_t, uint64_t, uint64_t> cons_ptest(size_t n, array<bool, 3> a, bool silent = true)
{
    BinaryOperation F;
#define cout if(not silent) cout
    cout << "n = " << n << endl;
    vector<T> A; uint64_t prep_tm;
    cout << "  prep: " << flush;
    tie(A, prep_tm) = timed2([&]() { A.resize(n); generate(A.begin(), A.end(), [&]() { return dis(gen); }); return A; });
    cout << prep_tm << "ms" << endl;

    uint64_t redt_tm, spat_tm, segt_tm;
if(a[0])
{
    cout << " *redt: " << flush;
    redt_tm = timed([&]() { reduction_tree<T, BinaryOperation> R(A.begin(), A.end(), F); });
    cout << redt_tm << "ms" << endl;
}
if(a[1])
{
    cout << "  spat: " << flush;
    spat_tm = timed([&]() { sparse_table<T, BinaryOperation> R(A.begin(), A.end(), F); });
    cout << spat_tm << "ms" << endl;
}
if(a[2])
{
    cout << "  segt: " << flush;
    segt_tm = timed([&]() { segment_tree<T, BinaryOperation> R(A.begin(), A.end(), F); });
    cout << segt_tm << "ms" << endl;
}
#undef cout
    return {prep_tm, redt_tm, spat_tm, segt_tm};
}

template<typename T, typename BinaryOperation>
tuple<uint64_t, uint64_t, uint64_t, uint64_t> ptest(size_t n, size_t m, array<bool, 3> a)
{
    BinaryOperation F;
    cout << "n = " << n << ", " << "m = " << m << endl;

    uint64_t redt_tm, spat_tm, segt_tm;
    auto cons = cons_ptest<T, BinaryOperation>(n, a);

    vector<T> A; uint64_t prep_tm;
    cout << "  prep: " << flush;
    tie(A, prep_tm) = timed2([&]() { A.resize(n); generate(A.begin(), A.end(), [&]() { return dis(gen); }); return A; });
    cout << prep_tm << "ms" << endl;

    auto run_queries = [&](auto& R) {
        T s = 0;
        for(size_t k = 0; k < m; k++)
          for(size_t i = 0; i < n; i++)
        {
            size_t j = n - i%(m-k);
            if(i < j)
                s += R(i, j);
        }
        return s;
    };

if(a[0])
{
    cout << " *redt: " << flush;
    redt_tm = max(timed([&]() { reduction_tree<T, BinaryOperation> R(A.begin(), A.end(), F); run_queries(R); }), get<1>(cons));
    cout << redt_tm-get<1>(cons) << "ms" << " + " << get<1>(cons) << "(cons)ms" << endl;
}
if(a[1])
{
    cout << "  spat: " << flush;
    spat_tm = max(timed([&]() { sparse_table<T, BinaryOperation> R(A.begin(), A.end(), F); run_queries(R); }), get<2>(cons));
    cout << spat_tm-get<2>(cons) << "ms" << " + " << get<2>(cons) << "(cons)ms" << endl;
}
if(a[2])
{
    cout << "  segt: " << flush;
    segt_tm = max(timed([&]() { segment_tree<T, BinaryOperation> R(A.begin(), A.end(), F); run_queries(R); }), get<3>(cons));
    cout << segt_tm-get<3>(cons) << "ms" << " + " << get<3>(cons) << "(cons)ms" << endl;
}
    return {prep_tm, redt_tm, spat_tm, segt_tm};
}

template<typename T>
struct ft_max { T operator() (const T& a, const T& b) const { return max(a, b); } };
template<typename T>
T identity_element(ft_max<T>) { return numeric_limits<T>::min(); }

int main()
{
    cout << "Correctness tests..." << endl;
    for(size_t n = 1; n <= 256; n++)
    {
        cout << "\rn = " << n << flush;
        vector<int> A(n);
        generate(A.begin(), A.end(), [&]() { return dis(gen); });
        test(A);
    }
    cout << endl << "Done!" << endl;

    vector<size_t> N = {(size_t)1e5, (size_t)5e5, (size_t)1e6, (size_t)5e6};

    cout << "Construction performance tests (+)..." << endl;
    for(size_t n : N)
        cons_ptest<int, plus<int>>(n, {true, false, true}, false);
    cout << endl;

    cout << "Construction performance tests (max)..." << endl;
    for(size_t n : N)
        cons_ptest<int, ft_max<int>>(n, {true, true, true}, false);
    cout << endl;

    vector<pair<size_t, size_t>> NM = {
        {(size_t)1e5, 4},
        {(size_t)1e5, 16},
        {(size_t)1e5, 64},
        {(size_t)5e5, 2},
        {(size_t)5e5, 4},
        {(size_t)5e5, 16},
        {(size_t)1e6, 1},
        {(size_t)1e6, 4},
        {(size_t)5e6, 1},
        {(size_t)5e6, 2}
    };
    cout << "Performance tests (* mod)..." << endl;
    using minty = mint<uint64_t, uint64_t(1e18+3)>;
    for(auto p : NM)
        ptest<minty, multiplies<minty>>(p.first, p.second, {true, false, true});
    cout << endl;

    cout << "Performance tests (max)..." << endl;
    for(auto p : NM)
        ptest<int, ft_max<int>>(p.first, p.second, {true, true, true});
    cout << endl;

}
