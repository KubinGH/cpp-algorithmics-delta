#include <bits/stdc++.h>
#define RESULT(a, b, c, d) out << double(a)/100.0 << " " << double(b)/100.0 << " " << double(c)/100.0 << " " << double(d)/100.0 << "\\n";

using namespace std;

const int64_t POW10[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
const int64_t SUMLIM = 2000, MULLIM = 2000 * POW10[6];

int main()
{
    ofstream out("out.txt");
    out << fixed << setprecision(2);
    for(int64_t a = 1; a <= 2000; a++)
    {
        cout << "a = " << a << endl;
        for(int64_t b = a; b <= 2000; b++)
        {
            if(a + b > SUMLIM or a * b > MULLIM)
                break;
            for(int64_t c = b; c <= 2000; c++)
            {
                if(a+b+c > SUMLIM or a*b*c > MULLIM)
                    break;
                int64_t f = a*b*c - POW10[6];
                if(f != 0 and (POW10[6]*(a+b+c)) % f == 0)
                {
                    int64_t d = (POW10[6]*(a+b+c)) / f;
                    if(d>=c and a+b+c+d <= SUMLIM and POW10[6]*(a+b+c+d) == a*b*c*d)
                        RESULT(a, b, c, d);
                }
            }
        }
    }
}
