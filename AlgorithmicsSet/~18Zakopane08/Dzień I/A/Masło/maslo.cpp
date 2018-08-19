#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

template<typename T>
ostream& operator<< (ostream& out, stack<T>& A)
{
    stack<T> B;
    while(not A.empty()) B.push(A.top()), A.pop();
    out << "< ";
    while(not B.empty())
    {
        out << B.top() << " ";
        A.push(B.top()); B.pop();
    }
    out << ">";
    return out;
}

void keep_merged(stack<uint32_t>& S)
{
    while(S.size() >= 2)
    {
        uint32_t a = S.top(); S.pop(); uint32_t b = S.top();
        if(a == b)
            S.pop(), S.push(a + 1);
        else
            { S.push(a); break; }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    stack<uint32_t> S;
    vector<uint32_t> R;
    uint32_t late = -1u;
    for(uint32_t i = 0; i < n or late != -1u; i++)
    {
        uint32_t a;
        if(late == -1u) cin >> a;
        else a = late, late = -1u;
        if(S.empty() or S.top() >= a)
        {
            S.push(a);
            R.push_back(a);
        }
        else
        {
            S.push(S.top());
            R.push_back(S.top()+32);
            k--;
            late = a;
            n++;
        }
        keep_merged(S);
    }
    while(S.top() < 30)
    {
        S.push(S.top());
        R.push_back(S.top()+32); k--;
        keep_merged(S);
    }
    while(not S.empty()) S.pop();
    for(uint32_t a : R)
    {
        if(a < 32)
            cout << a << " ";
        else
        {
            S.push(a-32);
            while(k and not S.empty())
            {
                uint32_t x = S.top(); S.pop();
                if(x == 0)
                    cout << "0 ";
                else
                    S.push(x-1), S.push(x-1), k--;
            }
            while(not S.empty())
                cout << S.top() << " ", S.pop();
        }
    }
}
