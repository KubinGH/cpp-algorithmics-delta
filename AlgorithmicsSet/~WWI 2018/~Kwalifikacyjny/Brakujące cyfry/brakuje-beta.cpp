#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;

int main()
{
    uint32_t n; string S;
    cin >> S >> n;
    uint32_t D[10], d = S.size();
    for(uint32_t i = 0; i < d; i++)
        D[i] = S[i] - '0';
    sort(D, D + d);
    for(uint32_t i = 0; i < d; i++)
    {
        if(D[i] != 0 and D[i] % n == 0)
        {
            cout << D[i];
            return 0;
        }
    }
    static vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = 0; j < d; j++)
            graph[i].push_back((10*i + D[j]) % n);
    }
    static uint32_t prev[MAX], prev_digit[MAX];
    fill(prev, prev + MAX, UINT32_MAX);
    queue<uint32_t> to_visit;
    static bitset<MAX> visited;
    for(uint32_t i = 0; i < d; i++)
    {
        if(D[i] == 0 or visited[D[i] % n])
            continue;
        uint32_t c = D[i] % n;
        to_visit.push(c);
        visited[c] = true;
        prev[c] = MAX;
        prev_digit[c] = D[i];
    }
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.front(); to_visit.pop();
        for(uint32_t i = 0; i < graph[u].size(); i++)
        {
            uint32_t v = graph[u][i], c = D[i];
            if(not visited[v])
            {
                to_visit.push(v);
                visited[v] = true;
                prev[v] = u;
                prev_digit[v] = c;
            }
        }
    }
    uint32_t c = 0;
    while(prev[c] != MAX and prev[c] != UINT32_MAX)
        c = prev[c];
    if(prev[c] == UINT32_MAX)
        cout << "nie istnieje";
    else
    {
        stack<char> R;
        uint32_t c = 0;
        while(prev[c] != MAX)
            R.push(prev_digit[c] + '0'), c = prev[c];
        R.push(prev_digit[c] + '0');
        while(not R.empty())
            cout << R.top(), R.pop();
    }
}
