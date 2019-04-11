#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

void swap_segments(rope<uint32_t>& R, size_t a, size_t b, size_t x, size_t y)
{
    auto seg1 = R.substr(a, b - a + 1);
    auto seg2 = R.substr(x, y - x + 1);
    R.erase(x, y - x + 1);
    R.erase(a, b - a + 1);
    R.insert(R.mutable_begin() + a, seg2);
    R.insert(R.mutable_begin() + x, seg1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    vector<uint32_t> A(2*n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    copy(A.begin(), A.begin() + n, A.rbegin());

    rope<uint32_t> R(A.data(), A.data() + 2*n);

    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == 'Q')
        {
            uint32_t i;
            cin >> i; i--;
            cout << R[i] << "\n";
        }
        else if(c == 'I')
        {
            uint32_t a, b;
            cin >> a >> b; a--; b--;
            uint32_t x = 2*n - b - 1, y = 2*n - a - 1;
            swap_segments(R, a, b, x, y);
        }
    }
}
