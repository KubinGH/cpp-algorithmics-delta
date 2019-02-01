#include <bits/stdc++.h>

using namespace std;

template<typename T, T MOD>
struct pos_integer
{
    struct digit
    {
        size_t p; T v;
        bool operator== (const digit& o) const { return p == o.p and v == o.v; }
        bool operator<  (const digit& o) const { return tie(p, v) < tie(o.p, o.v); }
    };
    list<digit> A;
    void normalize()
    {
        T carry = 0; size_t carry_pos = -1u;
        for(auto it = A.begin(); it != A.end(); ++it)
        {
            while(carry != 0)
            {
                if(carry_pos == it->p)
                    it->v += carry, carry = 0;
                else
                {
                    A.insert(it, {carry_pos, carry % MOD});
                    carry /= MOD; carry_pos++;
                }
            }
            if(it->v >= MOD)
                carry = it->v / MOD, it->v %= MOD, carry_pos = it->p+1;
        }
        while(carry != 0)
        {
            A.push_back({carry_pos, carry % MOD});
            carry /= MOD; carry_pos++;
        }
        for(auto it = A.begin(), itx = ++A.begin(); it != A.end(); it = itx, itx++)
        {
            if(it->v == 0)
                A.erase(it);
        }
    }
    pos_integer& operator+= (const pos_integer& o)
    {
        auto it = A.begin(), it1 = o.A.begin();
        for(; it != A.end(); ++it)
        {
            while(it1 != o.A.end() and it1->p < it->p)
                A.insert(it, *it1), ++it1;
            if(it1 != o.A.end() and it1->p == it->p)
                it->v += it1->v, ++it1;
        }
        while(it1 != o.A.end())
            A.push_back(*it1), ++it1;
        normalize();
        return *this;
    }
    bool operator== (const pos_integer& o) const
    {
        return A == o.A;
    }
    bool operator< (const pos_integer& o) const
    {
        return lexicographical_compare(A.rbegin(), A.rend(), o.A.rbegin(), o.A.rend());
    }
};
using posint = pos_integer<int32_t, 10>;

template<typename T>
string to_string(T x)
{
    stringstream str;
    str << x;
    return str.str();
}

ostream& operator<< (ostream& out, const posint& o)
{
    string S;
    uint32_t i = 0;
    for(auto d : o.A)
    {
        while(i < d.p) S += '0', i++;
        if(d.v < 10)
            S += char(d.v)+'0';
        else
        {
            string e = to_string(d.v); reverse(e.begin(), e.end());
            S += ']', S += e, S += '[';
        }
        i++;
    }
    if(o.A.empty()) S += '0';
    reverse(S.begin(), S.end());
    return out << S;
}

using graph_t = vector<vector<pair<uint32_t, uint32_t>>>;

pair<posint, map<uint32_t, uint32_t>> calc_cost(const graph_t& G, uint32_t u, uint32_t block = -1u, uint32_t depth = 0)
{
    map<uint32_t, uint32_t> depths;
    posint result;
    for(auto e : G[u]) if(e.first != block)
    {
        uint32_t v, w; tie(v, w) = e;
        auto sub = calc_cost(G, v, u, depth + 1);
        auto subresult = sub.first; auto subdepths = sub.second;

        posint extend;
        for(auto p : subdepths)
            extend.A.push_back({p.first - depth - 1, int32_t(w * p.second)});
        if(depths.size() < subdepths.size()) depths.swap(subdepths);
        for(auto p : subdepths)
            depths[p.first] += p.second;

        extend.normalize();
        subresult += extend;
        result += subresult;
    }
    if(G[u].size() == 1 and G[u][0].first == block) depths[depth]++;
    return {result, depths};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    graph_t G(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t a, b, c;
        cin >> a >> b >> c; a--; b--;
        G[a].emplace_back(b, c);
        G[b].emplace_back(a, c);
    }
    vector<uint32_t> B;
    posint r;
    for(uint32_t i = 0; i < 2*n; i++)
        r.A.push_back({i, 9});
    for(uint32_t i = 0; i < n; i++)
    {
        posint c = calc_cost(G, i).first;
        if(c < r)
            B.clear(), r = c;
        if(c == r)
            B.push_back(i);
    }
    sort(B.begin(), B.end());
    cout << B.size() << "\n";
    for(uint32_t i = 0; i < B.size(); i++)
        cout << B[i]+1 << " ";
}
