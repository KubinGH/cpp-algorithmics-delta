#include <iostream>
#include <string>

using namespace std;

const int oo = 1 << 28;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t T;
    cin >> T;

    while(T --> 0)
    {
        string A, B; int k;
        cin >> A >> B >> k;

        const size_t n = A.size();

        int f = k;
        for(size_t i = 0; i < n; i++)
            f -= (A[i] != B[i]);
        string C = B, R;

        for(size_t p = n; p --> 0; )
        {
            C[p] = A[p];
            f += (A[p] != B[p]);

            int l = f;

            auto sure_finish = [&](string D, int r) {
                for(size_t i = p+1; i < n; i++)
                    if(r and A[i] != '9')
                        D[i] = '9', r--;
                for(size_t i = n; i --> p+1; )
                    if(r and A[i] == '9')
                        D[i] = '8', r--;
                if(r == 0)
                    R = max(R, D);
            };
            auto finish = [&](string& D, int r) {
                if(0 <= r and r <= int(n - (p+1)))
                    sure_finish(D, r);
            };

            char cp = C[p];

            if(A[p] < B[p])
                finish(C, l);

            if(A[p] == B[p] - 1)
            {
                if(B[p] >= '1')
                    C[p] = B[p] - 1, finish(C, l);
                if(B[p] >= '2')
                    C[p] = B[p] - 2, finish(C, l - 1);
            }
            else
            {
                if(B[p] >= '1')
                    C[p] = B[p] - 1, finish(C, l - 1);
            }

            C[p] = cp;

            if(not R.empty())
                break;
        }

        cout << (R.empty() ? "-1" : R) << endl;
    }
}
