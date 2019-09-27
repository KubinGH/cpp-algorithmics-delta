#include <bits/stdc++.h>
#include <ktl/util/extio.cpp>

using namespace std;

namespace brute
{
    typedef intmax_t I;
    const I inf = 1e18;
    typedef pair<I, I> II;
    bool solve(I n, vector<I> v)
    {
        vector<vector<I>> w = {v};

        map<vector<I>, vector<I>> pre;
        pre[v];

        for (;;) {
          I m = w.size();

          for (I i = 0; i < (I)m; ++i) {
            for (I x = 0; x + 2 < (I)n; ++x) {
              w.push_back(w[i]);

              auto &c = w.back();
              I o = 3 * x;

              swap(c[o + 0], c[o + 8]);
              swap(c[o + 1], c[o + 7]);
              swap(c[o + 2], c[o + 6]);
              swap(c[o + 3], c[o + 5]);

              // cout << w[i] << " -> " << c << "\n";
              if (pre.find(c) == pre.end()) pre[c] = w[i];
            }
          }

          sort(w.begin(), w.end());
          w.erase(unique(w.begin(), w.end()), w.end());

          if ((I)w.size() == m) break;
        }

        // cout << w << "\n";
        // for (auto i : w) cout << i << "\n";

        vector<I> needed(3 * n);
        iota(needed.begin(), needed.end(), 1);

        /*
        auto h = needed;
        while (pre.find(h) != pre.end()) {
          cout << pre[h] << "\n";
          h = pre[h];
        }
        */

        // bool ok = binary_search(w.begin(), w.end(), needed);
        bool ok = w[0] == needed;

        return ok;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    srand(time(0));

    set<pair<vector<size_t>, vector<bool>>> unsolvable, solvable;

    while(true)
    {
        vector<size_t> A(n);
        vector<bool> Z(n);
        iota(A.begin(), A.end(), 0);
        random_shuffle(A.begin(), A.end());

        vector<long> B1(3*n);
        vector<size_t> B(3*n);

        for(size_t i = 0; i < n; i++)
        {
            bool z = false;
            //bool z = rand() % 2;
            Z[i] = z;
            if(z) B[3*i] = 3*A[i]+2, B[3*i+1] = 3*A[i]+1, B[3*i+2] = 3*A[i];
            else B[3*i] = 3*A[i], B[3*i+1] = 3*A[i]+1, B[3*i+2] = 3*A[i]+2;
        }
        for(size_t i = 0; i < 3*n; i++)
            B1[i] = B[i]+1;

        auto R = brute::solve(n, B1);

        bool r = true;

        #define TRUE_OR_FAIL(_condition_) if(not (_condition_)) { r = false; }

        for(size_t i = 0; i < 3*n; i += 3)
        {
            TRUE_OR_FAIL(((B[i+1] == B[i]+1 and B[i+2] == B[i]+2)
                       or (B[i+1] == B[i]-1 and B[i+2] == B[i]-2)))
            TRUE_OR_FAIL((i/3)%2 == (B[i]/3)%2)
        }

        if(R and not solvable.count({A, Z}))
        {
            solvable.emplace(A, Z);
            for(size_t i = 0; i < n; i++)
            {
                cout << A[i];
                if(Z[i]) cout << '^';
                else cout << ' ';
                cout << " ";
            }
            cout << "?" << r << " !" << R << endl;
        }
        /*
        if(R != r and not unsolvable.count({A, Z}))
        {
            for(size_t i = 0; i < n; i++)
            {
                cout << A[i];
                if(Z[i]) cout << '^';
                else cout << ' ';
                cout << " ";
            }
            cout << " ?" << r << " !" << R << " #" << unsolvable.size()+1 << endl;
            //cout << B1 << endl;
            assert(r and not R);
            unsolvable.emplace(A, Z);
        }
        */
        //assert(R == r);
    }

    for(auto p : unsolvable)
    {
        auto A = p.first; auto Z = p.second;
        for(size_t i = 0; i < n; i++)
        {
            cout << A[i];
            if(Z[i]) cout << '^';
            else cout << ' ';
            cout << " ";
        }
        cout << endl;
    }

}
