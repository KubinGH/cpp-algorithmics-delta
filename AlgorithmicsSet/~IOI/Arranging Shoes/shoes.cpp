#include <map>
#include <ext/pb_ds/assoc_container.hpp>
#include "shoes.h"

using namespace std;
using namespace __gnu_pbds;

template<typename T, typename Tk>
using os_map = tree<
    T, Tk, less<T>, rb_tree_tag, tree_order_statistics_node_update
>;
template<typename T>
using os_set = os_map<T, null_type>;

long long count_swaps(vector<int> S)
{
    const size_t n = S.size();

    vector<vector<size_t>> pos(2*n);
    for(size_t i = n; i --> 0; )
        pos[S[i] + n].push_back(i);

    os_set<size_t> erased;
    size_t mex = 0;
    long long result = 0;
    while(erased.size() < n)
    {
        while(erased.find(mex) != erased.end())
            mex++;

        auto i = pos[-S[mex] + n].back();

        result += i - (mex + 1) - (erased.order_of_key(i) - erased.order_of_key(mex));

        if(S[mex] > 0)
            result++;
        erased.insert(mex);
        pos[S[mex] + n].pop_back();
        erased.insert(i);
        pos[-S[mex] + n].pop_back();
    }

    return result;
}
