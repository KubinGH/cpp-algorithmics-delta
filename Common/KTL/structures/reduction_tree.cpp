#include <algorithm>
#include <cstddef>
#include <vector>

using std::vector;
using std::size_t;
using std::min; using std::__lg;

template<typename T, typename BinaryOperation>
struct reduction_tree
{
    BinaryOperation F;
    size_t n;
    vector<vector<T>> R;

    template<typename Iterator>
    reduction_tree(Iterator first, Iterator last, BinaryOperation f = {}) : F(f)
    {
        R.emplace_back(first, last); n = R.front().size();
        for(size_t block = 2; block <= n; block *= 2)
        {
            R.push_back(R.front());
            auto& r = R.back();
            for(size_t t = block; t <= n; t += 2*block)
            {
                for(size_t i = min(t-1, n-1); i --> t - block; )
                    r[i] = F(r[i], r[i+1]);
                for(size_t i = t+1; i < t + block and i < n; i++)
                    r[i] = F(r[i-1], r[i]);
            }
        }
    }

    T operator() (size_t a, size_t b) const
    {
        if(a == b) return R[0][a];
        auto e = __lg(a ^ b);
        return F(R[e][a], R[e][b]);
    }
};
