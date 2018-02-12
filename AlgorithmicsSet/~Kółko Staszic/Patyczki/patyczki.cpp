#include <bits/stdc++.h>

using namespace std;

typedef uint32_t(*tree_func)(uint32_t a, uint32_t b);

const size_t MAX = 7e6;
const size_t TSIZE = 1 << 24;
const char* MESSAGE_YES = "Happy Euklides!";
const char* MESSAGE_NO = "Motyla noga...";

uint32_t sum(uint32_t a, uint32_t b)
{
    return a + b;
}
uint32_t max(uint32_t a, uint32_t b)
{
    return a > b ? a : b;
}

template<tree_func F>
struct interval_tree
{
    array<uint32_t, TSIZE> values;
    void set_value(uint32_t i, uint32_t value)
    {
        values[i] = value;
        while(i)
            i = (i - 1) / 2, values[i] = F(values[2*i+1], values[2*i+2]);
    }
    uint32_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return F(find_value(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send),
                     find_value(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t find_value(uint32_t sbegin, uint32_t send)
    {
        return find_value(0, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static interval_tree<sum> sum_tree;
    static interval_tree<max> max_tree;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        sum_tree.set_value(i+TSIZE/2-1, a);
        max_tree.set_value(i+TSIZE/2-1, a);
    }
    uint32_t q;
    cin >> q;
    uint32_t p = 1;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        char c;
        cin >> c;
        if(c == 'W')
        {
            uint32_t i, j;
            cin >> i >> j; i--; j--;
            cout << p << " "; p++;
            if(sum_tree.find_value(i, j) > 2 * max_tree.find_value(i, j))
                cout << MESSAGE_YES << '\n';
            else
                cout << MESSAGE_NO << '\n';
        }
        else if(c == 'Z')
        {
            uint32_t i; int32_t d;
            cin >> i >> d; i--;
            uint32_t a = static_cast<int32_t>(sum_tree.values[i+TSIZE/2-1]) + d;
            sum_tree.set_value(i+TSIZE/2-1, a);
            max_tree.set_value(i+TSIZE/2-1, a);
        }
    }
}
