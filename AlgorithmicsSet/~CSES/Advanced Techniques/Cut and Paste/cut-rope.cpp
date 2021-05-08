#include <bits/stdc++.h>
#include <experimental/random>
#include <ext/rope>

using __gnu_cxx::rope;
using std::experimental::fundamentals_v2::randint;
using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    string init;
    // cin >> init;
     for(size_t i = 0; i < n; i++) init.push_back('A' + (i%26));

    rope<char> R(init.c_str());

    while(m --> 0)
    {
        size_t a, b;
        // cin >> a >> b; a--;
        a = randint<size_t>(0, n - 1);
        b = randint<size_t>(a + 1, n);

        R.append(R.substr(a, b - a));
        R.erase(a, b - a);
    }

    cout << string(R.begin(), R.end()) << endl;
}
