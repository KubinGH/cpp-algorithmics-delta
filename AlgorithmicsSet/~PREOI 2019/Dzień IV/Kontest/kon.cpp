#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#ifdef _WIN32
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#endif

using namespace std;
using namespace __gnu_pbds;

struct unlocked_cin
{
    unlocked_cin& operator>> (char& x)
    {
        x = getchar_unlocked();
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        char lchar; x = 0;
        while(isspace(lchar = getchar_unlocked())) {}
        do {
            x *= 10; x += lchar - '0';
        } while(isdigit(lchar = getchar_unlocked()));
        return *this;
    }
} ucin;

struct submit { uint32_t u, t, p; };

bool operator< (const submit& lhs, const submit& rhs)
{
    if(lhs.t == rhs.t)
        return lhs.u < rhs.u or (lhs.u == rhs.u and lhs.p < rhs.p);
    else
        return lhs.t < rhs.t;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, end_time;
    ucin >> n >> m >> end_time;

    vector<submit> submits(m);
    vector<uint32_t> users; users.reserve(m);
    for(uint32_t i = 0; i < m; i++)
    {
        ucin >> submits[i].u >> submits[i].t >> submits[i].p;
        users.push_back(submits[i].u);
    }
    sort(submits.begin(), submits.end());

    users.push_back(1);
    sort(users.begin(), users.end());
    users.erase(unique(users.begin(), users.end()), users.end());
    const uint32_t k = users.size();
    gp_hash_table<uint32_t, uint32_t> T;
    vector<uint32_t> Tr(k);
    for(uint32_t i = 0; i < k; i++)
        T[users[i]] = i, Tr[i] = users[i];

    vector<uint32_t> lead_time(k);
    vector<uint64_t> score(k);
    uint64_t lead_score = 0;
    vector<pair<uint32_t, uint32_t>> leaders(k);
    for(uint32_t i = 0; i < k; i++)
        leaders[i] = {i, 1};

    auto pop_leaders = [&](uint32_t curr_time) {
        for(auto p : leaders)
            lead_time[p.first] += curr_time - p.second;
        leaders.clear();
    };

    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u = T[submits[i].u], t = submits[i].t;
        uint64_t p = submits[i].p;
        score[u] += p;
        if(score[u] > lead_score)
        {
            pop_leaders(t);
            lead_score = score[u];
            leaders.emplace_back(u, t);
        }
        else if(p > 0 and score[u] == lead_score)
            leaders.emplace_back(u, t);
    }
    pop_leaders(end_time+1);

    uint32_t lleader = 0;
    for(uint32_t i = 0; i < k; i++)
        if(lead_time[i] > lead_time[lleader] or
           (lead_time[i] == lead_time[lleader] and Tr[i] < Tr[lleader]))
            lleader = i;
    cout << Tr[lleader];
}
