#include <bits/stdc++.h>
#define main __main
#include "kolej.cpp"
#undef main

using namespace std;

bool check_solutionbr(const vector<uint32_t>& A, const vector<bool>& R)
{
    uint32_t n = A.size(), lo = 1;
    stack<uint32_t> X, Y;
    X.push(n+1); Y.push(n+2);
    for(uint32_t i = 0; i < n; i++)
    {
        if(R[i] == 0)
            X.push(A[i]);
        else
            Y.push(A[i]);
        while(lo <= n and (X.top() == lo or Y.top() == lo))
        {
            if(X.top() == lo) X.pop();
            if(Y.top() == lo) Y.pop();
            lo++;
        }
    }
    return X.size() == 1 and Y.size() == 1;
}

pair<bool, vector<bool>> solve_brute(const vector<uint32_t>& A)
{
    uint32_t n = A.size();
    for(uint32_t m = 0; m < (1u << n); m++)
    {
        vector<bool> R(n);
        for(uint32_t i = 0; i < n; i++)
            R[i] = (m & (1u << i)) != 0;
        if(check_solutionbr(A, R))
            return {true, R};
    }
    return {false, vector<bool>()};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n);
    iota(A.begin(), A.end(), 1);
    do {
        auto p = solve(A), q = solve_brute(A);
        if(p.first != q.first)
        {
            for(uint32_t x : A) cout << x << " "; cout << endl;
            cout << p.first << " / " << q.first << endl;
        }
        assert(p.first == q.first);
        if(p.first and not check_solution(A, p.second))
        {
            for(uint32_t x : A) cout << x << " "; cout << endl;
            for(uint32_t x : p.second) cout << x << " "; cout << endl;
            cout << "( ";
            for(uint32_t x : q.second) cout << x << " ";
            cout << ")" << endl;
        }
        assert(not p.first or check_solution(A, p.second));
    } while(next_permutation(A.begin(), A.end()));
}
