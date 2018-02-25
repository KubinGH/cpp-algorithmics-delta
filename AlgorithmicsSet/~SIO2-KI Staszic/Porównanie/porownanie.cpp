#include <bits/stdc++.h>

using namespace std;

const double inf = 1e30;
const double phi = (1 + sqrt(5)) / 2;

double A, B, C, D;
double f(double x)
{
    return floor(A / (x + B));
}
double g(double x)
{
    return C * log(x + D);
}
double q(double x)
{
    return abs(f(x) - g(x));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    cout << fixed << setprecision(0);
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A >> B >> C >> D;
        if(A < 1e5)
        {
            double x = 1, p = log(A / C)-1.8;
            if(A / C > 1e6 and A > p*C*B)
                x = floor(A / (p*C) - B) - 1e5;
            if(q(x) < q(x+1)) x = 1;
            double a = q(x), b = q(x+1);
            while(b < a)
            {
                x += 1;
                a = b;
                b = q(x+1);
            }
            cout << floor(x) << '\n';
        }
        else
        {
            double a = 1, b = 1e9, c = b - (b-a)/phi, d = a + (b-a)/phi;
            double rx = 1, r = q(1);
            while(b - a > 0.1)
            {
                if(q(c) < q(d))
                    b = d;
                else
                    a = c;
                c = b - (b-a)/phi;
                d = a + (b-a)/phi;
                if(q(floor((a+b)/2)) < r)
                    rx = floor((a+b)/2), r = q(floor((a+b)/2));
                if(q(ceil((a+b)/2)) < r)
                    rx = ceil((a+b)/2), r = q(ceil((a+b)/2));
            }
            cout << floor(rx) << '\n';
        }
    }
}
