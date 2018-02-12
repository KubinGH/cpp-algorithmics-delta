#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 100000;

inline double unlit_area(double x, double l)
{
    return x/(l+1)*x/4.0;
}

int main()
{
    uint32_t n, k, d;
    scanf("%u %u %u", &n, &k, &d);
    static double P[MAX];
    for(uint32_t i = 0; i < n; i++)
        scanf("%lf", P+i);
    static double L[MAX-1];
    priority_queue<pair<double, uint32_t> > D;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        double x = P[i+1] - P[i];
        D.push(make_pair(unlit_area(P[i+1]-P[i], 0) - unlit_area(P[i+1]-P[i], 1), i));
    }
    for(uint32_t ki = 0; ki < k; ki++)
    {
        pair<double, uint32_t> p = D.top(); D.pop();
        uint32_t i = p.second;
        double x = P[i+1] - P[i];
        L[i]++;
        D.push(make_pair(unlit_area(x, L[i]) - unlit_area(x, L[i]+1), i));
    }
    double r = 0;
    for(uint32_t i = 0; i < n - 1; i++)
        r += unlit_area(P[i+1]-P[i], L[i]);
    printf("%.8f", r);
}
