#include <bits/stdc++.h>
#define FORCE_HEURISTIC 1

using namespace std;

const size_t MAX = 1e6;

template<typename T>
void uprint(T o)
{
    cerr << o;
}

template<typename A, typename B>
void uprint(pair<A, B> p)
{
    cerr << "(" << p.first << ", " << p.second << ")";
}

template <typename T, template <typename, typename...> class V, typename... Args>
void uprint(V<T, Args...>& it)
{
    cerr << "{";
    for(T i : it)
        uprint(i), cerr << "; ";
    cerr << "}";
}

uint32_t n;
array<vector<uint32_t>, MAX> graph;
unordered_set<uint32_t> burning, burning_start;
array<uint32_t, MAX> burning_next, burning_next_start;
unordered_set<uint32_t> not_burning, not_burning_start;
uint32_t burning_count, burning_count_start;
array<uint32_t, MAX> flammable_next;

void set_aflame(uint32_t i, bool count_flammable_neighbours = true)
{
    burning_count++;
    burning.insert(i);
    for(uint32_t x : graph[i])
    {
        burning_next[x]++;
        if(count_flammable_neighbours and burning_next[x] == 1)
            for(uint32_t y : graph[x])
                if(i != y) flammable_next[y]++;
        if(count_flammable_neighbours and flammable_next[x])
            flammable_next[x]--;
    }
}

void find_new_burning(bool count_flammable_neighbours = true)
{
    bool done = false;
    while(not done)
    {
        done = true;
        vector<uint32_t> to_erase;
        for(uint32_t i : not_burning)
        {
            if(burning_next[i] >= 2)
            {
                done = false;
                set_aflame(i, count_flammable_neighbours);
                to_erase.push_back(i);
            }
        }
        for(uint32_t x : to_erase)
            not_burning.erase(x);
        to_erase.clear();
    }
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    if(n <= 2) { cout << n; return 0; }
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        graph[a].push_back(b); graph[b].push_back(a);
    }
    uint32_t result = 0, leaves = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(graph[i].size() == 1)
        {
            set_aflame(i);
            leaves++;
        }
        else
            not_burning.insert(i);
    }
    find_new_burning();
    if(burning_count == n) { result = leaves; }
    else if(not FORCE_HEURISTIC and n < 25)
    {
        burning_count_start = burning_count;
        burning_start = burning;
        not_burning_start = not_burning;
        copy(burning_next.begin(), burning_next.begin() + n, burning_next_start.begin());
        result = -1;
        for(uint32_t i = 0; i < (1u << n); i++)
        {
            burning_count = burning_count_start;
            burning = burning_start;
            not_burning = not_burning_start;
            copy(burning_next_start.begin(), burning_next_start.begin() + n, burning_next.begin());
            uint32_t b = n - 1, c = 0, ci = i;
            bool ok = true;
            while(i)
            {
                if(i % 2 and burning.find(b) != burning.end())
                {
                    ok = false; break;
                }
                i /= 2; b--;
            }
            b = n - 1; c = 0; i = ci;
            if(not ok) continue;
            while(i)
            {
                if(i % 2 and burning.find(i) == burning.end())
                    set_aflame(b), c++;
                i /= 2; b--;
            }
            i = ci;
            find_new_burning(false);
            if(burning_count >= n) result = min(result, leaves + c);
        }

    }
    else
    {
        result = leaves;
        while(burning_count < n)
        {
            uint32_t bi = 0, bir = 0;
            for(uint32_t i : not_burning)
                if(flammable_next[i] > bir)
                    bi = i, bir = flammable_next[i];
            set_aflame(bi);
            find_new_burning();
            result++;
        }
    }
    cout << result;
}
