#include <bits/stdc++.h>

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

        string R(n, 0), default_result = R;

        auto candidate = [&](string C) {
            cerr << "candidate: " << C << endl;
            bool ok = true;
            for(char x : C)
                ok &= isdigit(x);
            assert(C < B);
            if(ok)
                R = max(R, C);
        };

        for(size_t p = n; p --> 0; )
        {
            cerr << "trying p = " << p << endl;
            if(B[p] == '0')
            {
                cerr << "nah, 0" << endl;
                continue;
            }
            int l = k;

            string C = A;

            cerr << "1* " << C << endl;

            for(size_t i = 0; i < p; i++)
            {
                C[i] = B[i];
                if(A[i] != B[i])
                    l--;
            }

            cerr << "2* " << C << endl;

            auto finish = [&](string D, int r) {
                for(size_t i = p+1; i < n; i++)
                    if(r and A[i] != '9')
                        D[i] = '9', r--;
                for(size_t i = n; i --> p+1; )
                    if(r and A[i] == '9')
                        D[i] = '8', r--;
                return r == 0 ? D : default_result;
            };

            if(A[p] < B[p])
                candidate(finish(C, l));

            if(A[p] == B[p] - 1)
            {
                C[p] = B[p] - 1;
                candidate(finish(C, l));
                C[p] = B[p] - 2;
                candidate(finish(C, l - 1));
            }
            else
            {
                C[p] = B[p] - 1;
                candidate(finish(C, l - 1));
            }

            if(R != default_result)
                break;
        }

        if(R == default_result)
            cout << "-1\n";
        else
            cout << R << endl;
    }
}
