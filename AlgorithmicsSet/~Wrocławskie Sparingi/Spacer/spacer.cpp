#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 500000;

template<typename T, size_t SIZE>
struct fstack
{
    array<T, SIZE> A;
    uint32_t i = 0;
    void push(T o) { A[i] = o; i++; }
    void pop() { i--; }
    T& top() { return A[i-1]; }
    bool empty() const { return i == 0; }
    void clear() { i = 0; }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX_N> next, result, visited_time;
    for(uint32_t i = 0; i < n; i++)
        cin >> next[i], next[i]--;
    static bitset<MAX_N> visited;
    for(uint32_t s = 0; s < n; s++)
    {
        if(visited[s])
            continue;
        static fstack<uint32_t, MAX_N> to_set; to_set.clear();
        uint32_t u = s, i = 1, p = -1u, b = -1u;
        while(not visited[u])
        {
            visited[u] = true;
            to_set.push(u);
            visited_time[u] = i;
            if(visited[next[u]])
            {
                if(visited_time[next[u]] != 0)
                {
                    result[u] = visited_time[u] - visited_time[next[u]] + 1;
                    p = next[u];
                }
                else
                    result[u] = result[next[u]] + 1;
                b = u;
            }
            u = next[u];
            i++;
        }
        visited_time[u] = 0;
        uint32_t r = result[b];
        bool f = false;
        while(not to_set.empty())
        {
            if(f)
                r++;
            if(to_set.top() == p or p == -1u)
                f = true;
            result[to_set.top()] = r;
            visited_time[to_set.top()] = 0;
            to_set.pop();
            i++;
        }
    }
    cout << *max_element(result.begin(), result.begin() + n);
}
/*
8
4 3 8 2 6 4 5 2
*/
