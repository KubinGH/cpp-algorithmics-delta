#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 18;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static bool A[MAX/2 + 16];
    static int32_t X[MAX/2 + 16], Y[MAX/2 + 16];
    uint32_t xi = 0, yi = 0;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    int32_t gx, gy;
    cin >> gx >> gy;
    bool d = false, any1 = false;
    uint32_t b = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i] == 0)
        {
            if(not any1)
                gy--;
            else
                b++;
        }
        else
        {
            if(b)
                (d ? X : Y)[(d ? xi : yi)++] = b, b = 0;
            d = not d;
            any1 = true;
        }
    }
    if(b)
        (d ? X : Y)[(d ? xi : yi)++] = b, b = 0;

    static bitset<MAX> PX, PY; // O(1/32) * O(n^2) = O(n^2 / 32)

    int32_t sx = accumulate(X, X + xi, 0);
    PX[0] = 1;
    for(uint32_t i = 0; i < xi; i++)
        PX |= (PX << (2 * X[i]));

    int32_t sy = accumulate(Y, Y + yi, 0);
    PY[0] = 1;
    for(uint32_t i = 0; i < yi; i++)
        PY |= (PY << (2 * Y[i]));
    if(gx + sx >= 0 and PX[gx + sx] and gy + sy >= 0 and PY[gy + sy])
        cout << "TAK";
    else
        cout << "NIE";
}
