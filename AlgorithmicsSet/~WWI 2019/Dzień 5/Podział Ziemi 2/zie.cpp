#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("tune=native")

using namespace std;

const size_t NAX = 1024;

struct plot_division
{
    size_t x1, y1, x2, y2;
    uint64_t s;

    size_t area() const
    {
        return (x2 - x1) * (y2 - y1);
    }

    friend bool operator< (const plot_division& a, const plot_division& b)
    {
        size_t aa = a.area(), ba = b.area();
        if(aa != ba)
            return aa < ba;
        else
        {
            if(a.s != b.s)
                return a.s < b.s;
            else
                return tie(a.x1, a.y1, a.x2, a.y2) > tie(b.x1, b.y1, b.x2, b.y2);
        }
    }

    friend bool fixed_less (const plot_division& a, const plot_division& b)
    {
        uint64_t aa = a.area(), ba = b.area();
        if(aa != ba)
            return aa < ba;
        else
        {
            if(a.s != b.s)
                return a.s < b.s;
            else
                return tie(a.x1, a.x2) > tie(b.x1, b.x2);
        }
    }
};

string quotient_fmt3(uint64_t a, uint64_t b)
{
    uint64_t c = (a * 1000) / b;
    auto i = to_string(c / 1000), f = to_string(c % 1000);
    while(f.size() < 3)
        f = '0' + f;
    return i + "." + f;
}


size_t w, h;
static uint64_t a[NAX][NAX];
static bool e[NAX][NAX];
static uint64_t s[NAX];
static size_t d[NAX];

template<size_t k>
plot_division solve()
{
    plot_division result = {0, 0, 0, 0, 0};
    for(size_t i = 0; i < h; i++)
    {
        fill(s, s + w, 0);
        fill(d, d + w, 0);
        for(size_t j = i+1; j <= h; j++)
        {
            for(size_t x = 0; x < w; x++)
            {
                s[x] += a[j-1][x];
                d[x] += e[j-1][x];
            }

            plot_division curr = {0, i, 0, j, 0}, sub_result = curr;

            size_t k1 = 0;
            for(size_t l = 0, r = 1; r <= w; r++)
            {
                curr.s += s[r - 1];
                k1 += d[r - 1];
                while(k1 > k)
                {
                    curr.s -= s[l];
                    k1 -= d[l];
                    l++;
                }

                curr.x1 = l;
                curr.x2 = r;

                if(fixed_less(sub_result, curr))
                    sub_result = curr;
            }
            if(result < sub_result)
                result = sub_result;
        }
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t k; uint64_t b;
    cin >> w >> h >> k >> b;

    for(size_t y = 0; y < h; y++)
      for(size_t x = 0; x < w; x++)
    {
        cin >> a[y][x];
        e[y][x] = (a[y][x] % b != 0);
    }

    plot_division result;
    if(k == 0)
        result = solve<0>();
    else if(k == 1)
        result = solve<1>();
    else if(k == 2)
        result = solve<2>();
    else if(k == 3)
        result = solve<3>();
    else if(k == 4)
        result = solve<4>();

    if(not result.area())
        cout << "NYET";
    else
    {
        cout << result.area() << " " << (result.x2 - result.x1) << " " << (result.y2 - result.y1) << " ";
        cout << quotient_fmt3(result.s, result.area()) << '\n';
        for(size_t y = result.y1; y < result.y2; y++, cout << '\n')
            for(size_t x = result.x1; x < result.x2; x++, cout << " ")
                cout << a[y][x];
    }
}
