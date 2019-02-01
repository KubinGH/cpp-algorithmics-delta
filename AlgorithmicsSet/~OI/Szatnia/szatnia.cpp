#include <bits/stdc++.h>

using namespace std;

const uint32_t K = 1 << 18;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<tuple<uint32_t, char, uint32_t, uint32_t>> events;
    vector<uint32_t> breakpoints;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t c, a, b;
        cin >> c >> a >> b;
        events.emplace_back(a, '+', b, c);
        breakpoints.push_back(a);
        breakpoints.push_back(b);
    }
    uint32_t p;
    cin >> p;
    vector<uint32_t> needed_length(p);
    vector<bool> result(p);
    for(uint32_t i = 0; i < p; i++)
    {
        uint32_t m, k, s;
        cin >> m >> k >> s;
        events.emplace_back(m, '?', k, i);
        needed_length[i] = s;
    }
    sort(events.begin(), events.end());
    vector<uint32_t> at_most(K);
    at_most[0] = -1u;
    for(auto T : events)
    {
        uint32_t t = get<1>(T);
        if(t == '+')
        {
            uint32_t a = get<0>(T), b = get<2>(T), c = get<3>(T);
            for(uint32_t i = K; i --> c; )
                at_most[i] = max(at_most[i], min(b, at_most[i-c]));
        }
        else if(t == '?')
        {
            uint32_t m = get<0>(T), k = get<2>(T), i = get<3>(T), s = needed_length[i];
            result[i] = at_most[k] > m+s;
        }
    }
    for(uint32_t i = 0; i < p; i++)
        cout << (result[i] ? "TAK\n" : "NIE\n");
}
