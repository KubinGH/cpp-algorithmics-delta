#include "arc.h"

#include <algorithm>
#include <vector>
#include <deque>

#include <cassert>

using namespace std;

int main()
{
    size_t k = inicjuj();

    vector<int> opt_pref;
    deque<int> suff;

    auto push_to_pref = [&](int x) {
//        while(not opt_pref.empty() and opt_pref.back() < x)
//            opt_pref.pop_back();
        opt_pref.push_back(x);
    };

    int curr;
    while((curr = wczytaj()))
    {
        suff.push_back(curr);
        if(suff.size() > k)
        {
            push_to_pref(suff.front());
            suff.pop_front();
        }
    }

    vector<int> seq;
    for(auto x : opt_pref) seq.push_back(x);
    for(auto x : suff)     seq.push_back(x);

    vector<int> result;
    assert(seq.size() < 30);
    for(size_t mask = 0; mask < (1u << seq.size()); mask++)
      if(__builtin_popcount(mask) == k)
    {
        vector<int> sub;
        for(size_t i = 0; i < seq.size(); i++)
            if(mask >> i & 1)
                sub.push_back(seq[i]);
        if(sub > result)
            result = sub;
    }

    for(auto x : result)
        wypisz(x);
}
