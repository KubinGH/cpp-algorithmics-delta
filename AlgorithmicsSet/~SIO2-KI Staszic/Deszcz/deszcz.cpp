#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 3e5, MAXQ = 1e5;
const size_t TSIZE = 1 << 20;

struct interval_tree
{
    uint32_t nodes = MAX;
    array<uint32_t, TSIZE> values, to_add;
    void interval_add(uint32_t node, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send, uint32_t value)
    {
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
            to_add[node] += value;
        else
        {
            interval_add(2*node+1, tbegin, (tbegin+tend)/2, sbegin, send, value);
            interval_add(2*node+2, (tbegin+tend)/2+1, tend, sbegin, send, value);
        }
    }
    void interval_add(uint32_t sbegin, uint32_t send, uint32_t value)
    {
        interval_add(0, 0, TSIZE/2 - 1, sbegin, send, value);
    }
    void add_queued(uint32_t node, uint32_t tbegin, uint32_t tend)
    {
        if(to_add[node])
        {
            values[node] += (min(nodes - 1, tend) - tbegin + 1) * to_add[node];
            if(min(tend, nodes - 1) - tbegin > 0)
            {
                to_add[2*node+1] += to_add[node];
                to_add[2*node+2] += to_add[node];
            }
            to_add[node] = 0;
        }
    }
    uint32_t interval_value(uint32_t node, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
        {
            add_queued(node, tbegin, tend);
            return values[node];
        }
        else
        {
            add_queued(node, tbegin, tend);
            return interval_value(2*node+1, tbegin, (tbegin+tend)/2, sbegin, send) +
                   interval_value(2*node+2, (tbegin+tend)/2+1, tend, sbegin, send);
        }
    }
    uint32_t interval_value(uint32_t sbegin, uint32_t send)
    {
        return interval_value(0, 0, TSIZE/2 - 1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q1, q2;
    cin >> q1 >> n >> q2;
    static array<array<uint32_t, 3>, MAXQ> Q1;
    static array<uint32_t, MAXQ> Q2;
    static array<uint32_t, MAX> V; uint32_t vi = 0;
    unordered_map<uint32_t, uint32_t> M;
    for(uint32_t i = 0; i < q1; i++)
    {
        uint32_t a, b, c; cin >> a >> b >> c; a--; b--;
        V[vi++] = a; V[vi++] = b;
        Q1[i][0] = a; Q1[i][1] = b; Q1[i][2] = c;
    }
    for(uint32_t i = 0; i < q2; i++)
    {
        uint32_t a; cin >> a; a--;
        V[vi++] = a; Q2[i] = a;
    }
    sort(V.begin(), V.begin() + vi);
    for(uint32_t i = 0, f = 0; i < vi; i++)
    {
        if(i > 0 and V[i] == V[i-1]) f++;
        M[V[i]] = i-f;
    }
    static interval_tree tree;
    tree.nodes = n;
    for(uint32_t i = 0; i < q1; i++)
    {
        tree.interval_add(M[Q1[i][0]], M[Q1[i][1]], Q1[i][2]);
    }
    for(uint32_t i = 0; i < q2; i++)
    {
        cout << tree.interval_value(M[Q2[i]], M[Q2[i]]) << '\n';
    }
}
