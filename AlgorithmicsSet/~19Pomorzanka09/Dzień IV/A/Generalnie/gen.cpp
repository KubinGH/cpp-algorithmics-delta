#include <bits/stdc++.h>
#include <ktl/util/extio.cpp>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const uint MOD = 1e9 + 7;

size_t other3(size_t a, size_t b)
{
         if(a != 0 and b != 0) return 0;
    else if(a != 1 and b != 1) return 1;
    else                       return 2;
}

int main()
{
    size_t n;
    cin >> n;
    //string S;
    //cin >> S;
    //const size_t n = S.size();

    vector<size_t> A(n);

    map<size_t, set<vector<size_t>>> res;
    set<vector<size_t>> done;
    for(size_t s = 0; s < power(3u, n); s++)
    {
        for(size_t i = 0, z = s; i < n; i++, z /= 3)
            A[i] = z % 3;
        /*
        vector<size_t> R = A;
        vector<size_t> I = {0, 1, 2};
        do {
            auto B = A;
            for(size_t i = 0; i < n; i++)
                B[i] = I[B[i]];
            R = min(R, B);
        } while(next_permutation(I.begin(), I.end()));
        A = R;
        */

        if(done.count(A)) continue;
        cout << A << endl;

        set<vector<size_t>> found;
        function<void(vector<size_t>)> venture = [&](vector<size_t> a) {
            if(found.count(a)) return;
            found.insert(a);

            for(size_t i = 0; i+1 < n; i++)
            {
                if(a[i] != a[i+1])
                {
                    auto b = a;
                    b[i] = b[i+1] = other3(a[i], a[i+1]);
                    venture(b);
                }
            }
        };
        venture(A);

        cout << found.size() << endl;

        long aa = 0, ab = 0, ac = 0, ba = 0, bb = 0, bc = 0, ca = 0, cb = 0, cc = 0;
        for(size_t i = 0; i+1 < n; i++)
        {
            if(A[i] == 0 and A[i+1] == 0) aa++;
            if(A[i] == 0 and A[i+1] == 1) ab++;
            if(A[i] == 0 and A[i+1] == 2) ac++;
            if(A[i] == 1 and A[i+1] == 0) ba++;
            if(A[i] == 1 and A[i+1] == 1) bb++;
            if(A[i] == 1 and A[i+1] == 2) bc++;
            if(A[i] == 2 and A[i+1] == 0) ca++;
            if(A[i] == 2 and A[i+1] == 1) cb++;
            if(A[i] == 2 and A[i+1] == 2) cc++;
        }

        res[found.size()].insert({A.front(), A.back()});
        done.insert(A);
    }

    for(auto p : res)
    {
        cout << p.first << ": " << p.second << endl;
        /*
        vector<size_t> sums(2);
        cout << p.first << ":: ";
        for(auto v : p.second)
            for(size_t i = 0; i < v.size(); i++)
                sums[i] += v[i];
        cout << sums << endl;
        */
    }


    for(auto p : res)
        for(auto q : res)
            if(p.first != q.first)
                for(auto x : p.second)
                    for(auto y : q.second)
                        if(x == y)
                            cout << "$ " << p.first << " "<< q.first << endl;
}
