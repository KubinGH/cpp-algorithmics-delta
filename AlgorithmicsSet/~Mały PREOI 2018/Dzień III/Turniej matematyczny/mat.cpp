#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const size_t N = 1<<10;
const uint64_t MOD = 1e9 + 7;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) { return (a*b) % MOD; }
} M;
struct rects
{
    uint64_t width, height;
};
template<typename T>
void clear(stack<T>& s) { while(not s.empty()) s.pop(); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static bool arr[N][N];
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            char c; cin >> c;
            arr[y][x] = (c == '1');
        }
    }
    static uint64_t mod_inverse[N];
    for(uint32_t i = 1; i < N; i++)
        mod_inverse[i] = power(i, MOD - 2, M);
    static stack<rects> colstack[N];
    static uint64_t colstack_the_sum[N], colstack_width_sum[N];
    uint64_t r = 0;
    for(uint32_t _ = 0; _ < 2; _++)
    {
        uint64_t _r = r;
        cout << " == calc " << _ << " == " << endl;
        uint64_t row_width = 0;
        cout << "y = 0" << endl;
        for(uint32_t x = 0; x < n; x++)
        {
            clear(colstack[x]);
            colstack_the_sum[x] = 0;
            colstack_width_sum[x] = 0;
            cout << " " << x << endl;
            if(arr[0][x])
            {
                row_width++;
                cout << "push " << row_width << " " << row_width << " " << 1 << endl;
                colstack[x].push({row_width, 1});
                colstack_the_sum[x] += row_width*(row_width+1) / 2;
                colstack_width_sum[x] += row_width;
                r += row_width;
            }
            else
                row_width = 0;
        }
        for(uint32_t y = 1; y < n; y++)
        {
            row_width = 0;
            cout << "y = " << y << endl;
            for(uint32_t x = 0; x < n; x++)
            {
                cout << " " << x << endl;
                if(arr[y][x])
                {
                    row_width++;
                    uint64_t re_rows = 1;
                    while(not colstack[x].empty() and colstack[x].top().width >= row_width)
                    {
                        uint32_t e = colstack[x].top().height, f = colstack[x].top().width;
                        colstack_width_sum[x] -= e * f;
                        colstack_the_sum[x] -= e * f*(f + 1)/2;
                        re_rows += e;
                        colstack[x].pop();
                    }
                    r += (row_width * (row_width+1)) * (re_rows * (re_rows+1)) / 4;
                    r += colstack_the_sum[x] * re_rows;
                    r %= MOD;
                    colstack[x].push({row_width, re_rows});
                }
                else
                {
                    clear(colstack[x]);
                    colstack_the_sum[x] = 0;
                    colstack_width_sum[x] = 0;
                    row_width = 0;
                }
            }
        }

        for(uint32_t y = 0; y < n; y++)
            for(uint32_t x = 0; x < n; x++)
                arr[y][x] = not arr[y][x];
        cout << "   diff " << r - _r << endl;
    }
    cout << r;
}
