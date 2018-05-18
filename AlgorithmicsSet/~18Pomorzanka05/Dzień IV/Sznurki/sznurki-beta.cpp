#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6+16, TSIZE = 1 << 21;

// Jedno zapytanie:
// Drzewo przedzialowe
// ilosc przedzialow gdzie nie ma zadnych punktow
// Posortowanie punktow i przedzialow
// Dla kazdego przedzialu, punktu:
//   Dodawanie 1 w punkcie poczatku przedzialu gdy napotykamy jego koniec
// O(n log n)

template<typename T, T(*F)(T, T), T NONE, size_t N>
struct segment_tree
{
    array<T, N> values;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
    }
    void set(size_t i, T value)
    {
        i += offset();
        values[i] = value;
        while(i > 0)
            i = parent(i), values[i] = F(values[left(i)], values[right(i)]);
    }
    T get(size_t sbegin, size_t send)
    {
        if(sbegin > send)
            return NONE;
        send++;
        T result = NONE;
        for(sbegin += offset(), send += offset(); sbegin < send;
            sbegin = parent(sbegin), send = parent(send))
        {
            if(sbegin % 2 == 0) result = F(result, values[sbegin++]);
            if(send % 2 == 0)   result = F(result, values[--send]);
        }
        return result;
    }
    const T& operator[] (size_t i) const
    {
        return values[offset() + i];
    }
};
uint32_t add_u32(uint32_t a, uint32_t b) { return a + b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static pair<uint32_t, uint32_t> intervals[MAX];
    vector<tuple<uint32_t, uint32_t, uint32_t>> events;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> intervals[i].first >> intervals[i].second;
        events.emplace_back(intervals[i].second, -1u, i);
    }
    static vector<uint32_t> groups[MAX];
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t k;
        cin >> k;
        groups[i].push_back(0);
        events.emplace_back(groups[i].back(), groups[i].size()-1, i);
        for(uint32_t j = 0; j < k; j++)
        {
            uint32_t a;
            cin >> a;
            groups[i].push_back(a);
            events.emplace_back(groups[i].back(), groups[i].size()-1, i);
        }
        groups[i].push_back(MAX-1);
        events.emplace_back(groups[i].back(), groups[i].size()-1, i);
    }
    sort(events.begin(), events.end());
    static segment_tree<uint32_t, add_u32, 0, TSIZE> tree;
    static uint32_t result[MAX];
    for(auto event : events)
    {
        uint32_t t, i, j;
        tie(t, i, j) = event;
        if(i == -1u)
        {
            //cout << "mark begin " << i << " (" << j << ")" << endl;
            tree.set(intervals[j].first, tree[intervals[j].first] + 1);
        }
        else
        {
            if(i == 0)
                continue;
            //cout << "get " << groups[j][i-1]+1 << ".." << t-1 << " for " << i << " " << j << endl;
            //cout << " -> " << tree.get(groups[j][i-1]+1, t-1) << endl;
            result[j] += tree.get(groups[j][i-1]+1, t-1);
        }
    }
    for(uint32_t i = 0; i < m; i++)
        cout << n - result[i] << "\n";

}
