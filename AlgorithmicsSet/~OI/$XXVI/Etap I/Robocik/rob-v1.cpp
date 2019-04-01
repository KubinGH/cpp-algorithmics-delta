#include <bits/stdc++.h>
#define cerr if(0) cerr

using namespace std;

const size_t MAX = 1 << 20;
const int64_t dirs[4][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};
template<typename T>
T umod(T a, T b) { return ((a%b)+b)%b; }

// a <= bk <= c, assume b > 0
int64_t first_multiple(int64_t a, int64_t b, int64_t c)
    { (void)c; return a + umod((b - umod(a, b)), b); }
int64_t last_multiple(int64_t a, int64_t b, int64_t c)
    { (void)a; return c - umod(c, b); }

int64_t count_multiples(int64_t a, int64_t b, int64_t c)
{
    int64_t p = first_multiple(a, b, c), q = last_multiple(a, b, c);
    cerr << a << ".." << c << " # " << b << " (" << p << ":" << q << ") -> " << (p <= q ? (q - p)/b + 1 : 0) << endl;
    return a <= c and p <= q ? (q - p)/b + 1 : 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; int64_t t;
    cin >> n >> t;
    static int64_t D[MAX], XS[MAX], YS[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> D[i];
    uint32_t n_mul;
    for(n_mul = 1; (n*n_mul) % 4 != 0; n_mul++)
        copy(D, D + n, D + n_mul*n);
    n *= n_mul;
    int64_t ts = 0;
    for(uint32_t i = 0; i < n; i++)
        ts += D[i];
    int64_t p_base = t / (ts + n);
    int64_t t_after = t % (ts + n), i_after = n;
    static int64_t P[MAX];
    fill(P, P + n, p_base);
    cerr << "P: ";
    for(uint32_t i = 0; i < n; i++)
    {
        if(t_after >= D[i] + 1)
        {
            P[i]++;
            t_after -= D[i] + 1;
        }
        else
        {
            i_after = i;
            break;
        }
    }
    for(uint32_t i = 0; i < n; i++)
        cerr << P[i] << " ";
    cerr << endl;
    cerr << "after: " << i_after << " " << t_after << endl;
    int64_t xt, yt;
    cin >> xt >> yt;
    uint32_t r = 0;
    if(xt == 0 and yt == 0) r++;
    for(uint32_t rot = 0; rot < 4; rot++)
    {
        cerr << "=== ROTATION " << rot << " ===" << endl;
        cerr << "== tx = " << xt << " ty = " << yt << " ==" << endl;
        int64_t xs = 0, ys = 0;
        for(uint32_t i = 0; i < n; i++)
        {
            XS[i+1] = (xs += dirs[(i+rot)%4][0] * D[i]);
            YS[i+1] = (ys += dirs[(i+rot)%4][1] * D[i]);
        }
        auto pred_xs0 = [&](uint32_t i) {
            return xt - D[i] <= XS[i] and XS[i] < xt;
        };
        auto pred_ys0 = [&](uint32_t i) {
            return yt == YS[i];
        };
        auto pred_ysX = [&](uint32_t i) {
            return (yt-YS[i]) % ys == 0 and 0 <= (yt-YS[i]) / ys and (yt-YS[i]) / ys < P[i];
        };
        cerr << "xs = " << xs << endl;
        cerr << "ys = " << ys << endl;
        for(uint32_t i = (5-rot)%4; i < n; i += 4)
        {
            cerr << " = " << i << " = (" << D[i] << "/" << P[i] << ")" << endl;
            int64_t _r = r;
            if(P[i] == 0) continue;
            else if(xs == 0 and ys == 0)
                r += (pred_ys0(i) and pred_xs0(i)) * P[i];
            else if(xs == 0)
                r += (pred_ysX(i) and pred_xs0(i));
            else if(ys == 0)
            {
                if(pred_ys0(i))
                {
                    int64_t e = xt - XS[i] - D[i], f = xt - XS[i];
                    // e <= xs * k < f
                    cerr << e << " <= " << xs << " * k < " << f << endl;
                    if(xs > 0)
                        r += count_multiples(max(e, 0LL), xs, min(f-1, xs*P[i]-1));
                    else
                        r += count_multiples(max(-f+1, 0LL), -xs, min(-e, -xs*P[i]-1));
                }
            }
            else
            {
                int64_t k = (yt - YS[i]) / ys;
                cerr << "k = " << k << ", " << XS[i] << ", " << D[i] << endl;
                cerr << "x in range " << xs*k + XS[i] << " -> " << xs*k + XS[i] + D[i] << endl;
                int64_t e = xt - XS[i] - D[i], f = xt - XS[i];
                cerr << "| " << k*xs << " " << e << " " << f << endl;
                r += (pred_ysX(i) and e <= k*xs and k*xs < f);
            }
            cerr << "+++ " << r-_r << " +++" << endl;
        }
        cerr << i_after << " " << i_after%4 << endl;
        if(i_after < n and i_after%4 == (5-rot)%4)
        {
            int64_t k = P[i_after];
            cerr << "use after with " << k << endl;
            if(yt == ys*k + YS[i_after] and xs*k + XS[i_after] < xt and xt <= xs*k + XS[i_after] + t_after)
            {
                r++;
                cerr << "+1" << endl;
            }
        }
        tie(xt, yt) = make_tuple(yt, -xt);
        cerr << endl << endl;
    }
    cout << r;
}
