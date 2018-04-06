#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 100, MAX_M = 2000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t places, cars;
    cin >> places >> cars;
    static array<uint32_t, MAX_N> cost;
    static array<uint32_t, MAX_M> weight;
    for(uint32_t i = 0; i < places; i++)
        cin >> cost[i];
    for(uint32_t i = 0; i < cars; i++)
        cin >> weight[i];
    static array<uint32_t, MAX_M> occupies { -1u };
    static bitset<MAX_N> free; free.set();
    uint32_t free_count = places;
    queue<uint32_t> to_enter;
    uint64_t result = 0;
    for(uint32_t i = 0; i < 2 * cars; i++)
    {
        int32_t x;
        cin >> x;
        bool type = x > 0;
        uint32_t k = abs(x) - 1;
        uint32_t nf = places;
        if(type == 1)
            to_enter.push(k);
        else
        {
            free[occupies[k]] = true;
            free_count++;
            if(free_count == places - 1)
                nf = occupies[k];
            occupies[k] = -1u;
        }
        if(free_count > 0 and not to_enter.empty())
        {
            uint32_t p = to_enter.front(); to_enter.pop();
            uint32_t o = nf;
            if(o == places) for(uint32_t j = 0; j < places; j++)
            {
                if(free[j])
                {
                    o = j;
                    break;
                }
            }
            result += cost[o] * weight[p];
            occupies[p] = o;
            free_count--;
            free[o] = false;
        }
    }
    cout << result;
}
