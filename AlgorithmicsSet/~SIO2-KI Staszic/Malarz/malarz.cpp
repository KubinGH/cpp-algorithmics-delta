#include <bits/stdc++.h>

using namespace std;

const size_t MAXQ = 10;//5e5;
const size_t MAX = MAXQ*2;
const size_t TSIZE = 1 << 5;//21;

struct interval_tree
{
    uint32_t nodes = MAX;
    array<bool, TSIZE> toggle;
    array<uint32_t, TSIZE> values;
    void interval_toggle(uint32_t node, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
            toggle[node] = ~toggle[node];
        else
        {
            interval_toggle(2*node+1, tbegin, (tbegin+tend)/2, sbegin, send);
            interval_toggle(2*node+2, (tbegin+tend)/2+1, tend, sbegin, send);
        }
    }
    void interval_toggle(uint32_t sbegin, uint32_t send)
    {
        interval_toggle(0, 0, TSIZE/2-1, sbegin, send);
    }
    void toggle_queued(uint32_t node, uint32_t tbegin, uint32_t tend)
    {
        if(toggle[node])
        {
            cout << nodes - 1 << " " << tend << " " << tbegin << " " << values[node] << endl;
            values[node] = (min(nodes - 1, tend) - tbegin + 1) - values[node];
            toggle[2*node+1] = ~toggle[2*node+1];
            toggle[2*node+2] = ~toggle[2*node+2];
            toggle[node] = false;
        }
    }
    uint32_t interval_value(uint32_t node, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
        {
            toggle_queued(node, tbegin, tend);
            return values[node];
        }
        else
        {
            toggle_queued(node, tbegin, tend);
            return interval_value(2*node+1, tbegin, (tbegin+tend)/2, sbegin, send) +
                   interval_value(2*node+2, (tbegin+tend)/2+1, tend, sbegin, send);
        }
    }
    uint32_t interval_value(uint32_t sbegin, uint32_t send)
    {
        return interval_value(0, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static array<bool, MAXQ> T;
    static array<array<uint32_t, 2>, MAXQ> E;
    static array<uint32_t, MAX> V; uint32_t vi = 0;
    for(uint32_t i = 0; i < q; i++)
    {
        char t; uint32_t a, b;
        cin >> t >> a >> b; a--; b--;
        T[i] = (t == '*');
        E[i][0] = a; E[i][1] = b;
        V[vi++] = a; V[vi++] = b;
    }
    sort(V.begin(), V.begin() + vi);
    unordered_map<uint32_t, uint32_t> M;
    for(uint32_t i = 0, f = 0; i < vi; i++)
    {
        if(i > 0 and V[i] == V[i-1]) f++;
        M[V[i]] = i - f;
    }
    static interval_tree tree; tree.nodes = V[vi-1] + 1;
    for(uint32_t i = 0; i < q; i++)
    {
        cout << T[i] << " " << M[E[i][0]] << " " <<  M[E[i][1]] << endl;
        if(T[i])
            tree.interval_toggle(M[E[i][0]], M[E[i][1]]);
        else
            cout << tree.interval_value(M[E[i][0]], M[E[i][1]]) << endl;
        for(uint32_t j = 0; j < TSIZE; j++)
            cout << tree.values[j] << " "; cout << endl;
        for(uint32_t j = 0; j < TSIZE; j++)
            cout << tree.toggle[j] << " "; cout << endl;
    }
}
