#include <bits/stdc++.h>

using namespace std;

typedef int64_t TreeT;
typedef tuple<TreeT, TreeT, size_t, size_t> pre_dt;
const size_t TSIZE = 1 << 20;

TreeT sigma(TreeT a, TreeT b)
{
    // a + a+1 + a+2 + ... + b
    return (b*(b+1) - a*(a-1))/2;
}

template<typename T, T(*F)(T, T), T NONE, size_t N, T SET_NONE,
        void(*P)(size_t, size_t, size_t, array<T, N>&, array<T, N>&)>
struct segment_tree_intervalop
{
    array<T, N> values, to_set;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree_intervalop()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
        fill(to_set.begin(), to_set.end(), SET_NONE);
    }
    void pull(size_t i, size_t tbegin, size_t tend)
    {
        if(to_set[i] == SET_NONE)
            return;
        P(i, tbegin, tend, values, to_set);
        to_set[i] = SET_NONE;
    }
    void set(size_t i, size_t tbegin, size_t tend,
                       size_t sbegin, size_t send, T value)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_set[i] = F(to_set[i], value);
            pull(i, tbegin, tend);
        }
        else
        {
            set(left(i),  tbegin, (tbegin+tend)/2, sbegin, send, value);
            set(right(i), (tbegin+tend)/2+1, tend, sbegin, send, value);
            values[i] = F(values[left(i)], values[right(i)]);
        }
    }
    void set(size_t sbegin, size_t send, T value)
        { return set(0, 0, N/2 - 1, sbegin, send, value); }
    T get(size_t i, size_t tbegin, size_t tend,
                    size_t sbegin, size_t send)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return NONE;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return F(get(left(i),  tbegin, (tbegin+tend)/2, sbegin, send),
                     get(right(i), (tbegin+tend)/2+1, tend, sbegin, send));
    }
    T get(size_t sbegin, size_t send)
        { return get(0, 0, N/2 - 1, sbegin, send); }
};
void pull_linear_add(
        size_t i, size_t tbegin, size_t tend,
        array<TreeT, TSIZE>& values,
        array<TreeT, TSIZE>& to_set)
{
    if(tbegin < tend)
    {
        to_set[2*i+1] += to_set[i];
        to_set[2*i+2] += to_set[i];
    }
    values[i] += to_set[i] * sigma(tbegin, tend);
}
void pull_constant_add(
        size_t i, size_t tbegin, size_t tend,
        array<TreeT, TSIZE>& values,
        array<TreeT, TSIZE>& to_set)
{
    if(tbegin < tend)
    {
        to_set[2*i+1] += to_set[i];
        to_set[2*i+2] += to_set[i];
    }
    values[i] += to_set[i] * TreeT(tend - tbegin + 1);
}
TreeT add(TreeT a, TreeT b) { return a + b; }

template<typename TreeLinear, typename TreeConstant>
void add_function(TreeLinear& linear, TreeConstant& constant,
                  TreeT a, TreeT b, size_t tbegin, size_t tend)
{
    //cout << "func " << a << " " << b << " " << tbegin << ".." << tend << endl;
    linear.set(tbegin, tend, a);
    constant.set(tbegin, tend, b);
}
template<typename TreeLinear, typename TreeConstant>
TreeT sum_functions(TreeLinear& linear, TreeConstant& constant,
                    size_t tbegin, size_t tend)
{
    return linear.get(tbegin, tend) + constant.get(tbegin, tend);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static segment_tree_intervalop
        <TreeT, add, 0, TSIZE, 0, pull_linear_add>
            linear;
    static segment_tree_intervalop
        <TreeT, add, 0, TSIZE, 0, pull_constant_add>
            constant;
    uint32_t n, m;
    cin >> n >> m;
    unordered_map<size_t, pair<pre_dt, pre_dt>> pre;
    pre.reserve(2 * m);
    for(uint32_t i = 0; i < m; i++)
    {
        char c;
        cin >> c;
        if(c == 'P')
        {
            TreeT x, s, a;
            cin >> x >> s >> a;
            double d = (double)s/(double)a, x1 = x - d, x2 = x + d;
            pair<TreeT, TreeT> f, g;
            f.first = a; g.first = -a;
            f.second = s - f.first*x; g.second = s - g.first*x;
            size_t ax1 = max(ceil(x1), 1.0),
                   ax2 = min(floor(x2), (double)n);
            add_function(linear, constant, f.first, f.second, ax1, x);
            add_function(linear, constant, g.first, g.second, x+1, ax2);
            pre[x] = make_pair(pre_dt(f.first, f.second, ax1, x),
                               pre_dt(g.first, g.second, x+1, ax2));
        }
        else if(c == 'Z')
        {
            size_t x1, x2;
            cin >> x1 >> x2;
            TreeT s = sum_functions(linear, constant, x1, x2);
            cout << s / TreeT(x2 - x1 + 1) << "\n";
            //cout << "(" << s << ")" << endl;
        }
        else if(c == 'U')
        {
            size_t x;
            cin >> x;
            pre_dt t1 = pre[x].first, t2 = pre[x].second;
            add_function(linear, constant, -get<0>(t1), -get<1>(t1),
                         get<2>(t1), get<3>(t1));
            add_function(linear, constant, -get<0>(t2), -get<1>(t2),
                         get<2>(t2), get<3>(t2));
            pre.erase(x);
        }
    }
}
