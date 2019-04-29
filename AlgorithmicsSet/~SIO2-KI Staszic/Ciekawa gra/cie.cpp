#include <bits/stdc++.h>

using namespace std;

const char *nameA = "Jas", *nameB = "Malgosia";


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    uint32_t A, B;
    cin >> n >> A >> B;
    uint32_t C_lo, C_hi;
    tie(C_lo, C_hi) = minmax(A, B);

    vector<uint32_t> H_lo, H_hi;
    H_lo.reserve(n); H_hi.reserve(n);
    for(size_t i = 0; i < n; i++)
    {
        uint32_t h;
        cin >> h;
        h %= A + B;
        if(h >= C_hi)
            H_hi.push_back(h);
        else if(h >= C_lo)
            H_lo.push_back(h);
    }
    sort(H_hi.begin(), H_hi.end());

    size_t i;
    uint32_t C = A;
    for(i = 0; true; i++, C = (i % 2 ? B : A))
    {
        if(C == C_lo)
        {
            if(not H_hi.empty())
            {
                auto h = H_hi.back();
                H_hi.pop_back();
                if(h >= 2*C_lo)
                    H_lo.push_back(h - C_lo);
            }
            else if(not H_lo.empty())
            {
                if(H_lo.back() >= 2*C_lo)
                    H_lo.back() -= C_lo;
                else
                    H_lo.pop_back();
            }
            else
                break;
        }
        else
        {
            if(not H_hi.empty())
                H_hi.pop_back();
            else
                break;
        }
    }
    cout << (i % 2 ? nameA : nameB);
}