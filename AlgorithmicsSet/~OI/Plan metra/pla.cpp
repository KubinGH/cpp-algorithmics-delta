#include <bits/stdc++.h>
#define MAX 500000
#define MINF (a) < (b) ? (a) : (b)

using namespace std;

enum relative
{
    included,
    between,
    out_close_first,
    out_close_last,
    between_common
};

struct tunnel_t
{
    int64_t first, second, length;
    tunnel_t(int64_t afirst, int64_t asecond, int64_t alength)
    {
        first = afirst; second = asecond; length = alength;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int64_t N, i, j;
    cin >> N;
    static int64_t cost_first[MAX], cost_last[MAX];
    cost_first[0] = cost_last[N - 1] = 0;
    // Input
    for(i = 1; i < N - 1; i++)
        cin >> cost_first[i];
    for(i = 1; i < N - 1; i++)
        cin >> cost_last[i];
    // Find distance between first and last
    static relative rtypes[MAX];
    int64_t dist = cost_first[1] + cost_last[1];
    static int64_t sums[MAX], diffs[MAX];
    for(i = 1; i < N - 1; i++)
    {
        sums[i] = cost_first[i] + cost_last[i];
        diffs[i] = abs(cost_first[i] - cost_last[i]);
        if(sums[i] < dist) dist = sums[i];
    }
    cost_first[N - 1] = cost_last[0] = dist;
    rtypes[0] = rtypes[N - 1] = relative::included;
    vector<tunnel_t> tunnels;
    vector< pair<int64_t, int64_t> > bdists, cdists; // between, between_common
    // Find types of relativity between first and last and others
    for(i = 1; i < N - 1; i++)
    {
        sums[i] = cost_first[i] + cost_last[i];
        diffs[i] = abs(cost_first[i] - cost_last[i]);
        if(sums[i] == dist)
        {
            rtypes[i] = relative::between;
        }
        else if(diffs[i] == dist)
        {
            if(cost_first[i] > cost_last[i])
            {
                rtypes[i] = relative::out_close_last;
                tunnels.push_back(tunnel_t(N - 1, i, cost_last[i]));
            }
            else if(cost_first[i])
            {
                rtypes[i] = relative::out_close_first;
                tunnels.push_back(tunnel_t(0, i, cost_first[i]));
            }
            else
            {
                goto invalid;
            }
        }
        else
        {
            rtypes[i] = relative::between_common;
        }
    }
    // Create tunnels of stations between first and last
    for(i = 0; i < N; i++)
    {
        if(rtypes[i] == relative::between)
            bdists.push_back(make_pair(cost_first[i], i));
    }
    if(bdists.size() > 0)
    {
        sort(bdists.begin(), bdists.end());
        for(i = 0; i < bdists.size(); i++)
        {
            if(i > 0)
            {
                if(bdists[i - 1].first == bdists[i].first)
                {
                    goto invalid;
                }
                tunnels.push_back(tunnel_t(bdists[i - 1].second, bdists[i].second, bdists[i].first - bdists[i - 1].first));
            }
            else
            {
                tunnels.push_back(tunnel_t(0, bdists[i].second, bdists[i].first));
            }
        }
        tunnels.push_back(tunnel_t(bdists[bdists.size() - 1].second, N - 1, cost_first[N - 1] - bdists[bdists.size() - 1].first));
    }
    else
    {
        tunnels.push_back(tunnel_t(0, N - 1, dist));
    }

    // Create tunnels of stations between first and last with common added
    for(i = 0; i < N; i++)
    {
        if(rtypes[i] == relative::between_common)
            cdists.push_back(make_pair(cost_first[i], i));
    }
    if(bdists.size() == 0 and cdists.size() > 0) goto invalid;
    sort(cdists.begin(), cdists.end());
    for(i = 0; i < cdists.size(); i++)
    {
        for(j = 0; j < bdists.size(); j++)
        {
            int64_t ix = cdists[i].second;
            int64_t v1 = cost_first[cdists[i].second] - cost_first[bdists[j].second];
            int64_t v2 = cost_last[cdists[i].second] - cost_last[bdists[j].second];
            if(v1 > 0)
            {
                tunnels.push_back(tunnel_t(bdists[j].second, ix, v1));
                break;
            }
            else if(v2 > 0)
            {
                tunnels.push_back(tunnel_t(bdists[j].second, ix, v2));
                break;
            }
            else
            {
                goto invalid;
            }
        }
    }

    cout << "TAK" << endl;
    for(i = 0; i < tunnels.size(); i++)
    {
        cout << tunnels[i].first + 1 << " " << tunnels[i].second + 1 << " " << tunnels[i].length << endl;
    }
    goto finish;
invalid:
    cout << "NIE";
finish:
    return 0;
}
