#include <utility>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

pair<bool, vector<bool>> solve(const vector<uint32_t>& A)
{
    uint32_t n = A.size();
    vector<bool> R(n);
    stack<uint32_t> X, Y;
    X.push(n+1); Y.push(n+2);
    uint32_t lo = 1;
    bool ok = true;
    for(uint32_t i = 0; i < n; i++)
    {
        if(X.top() < A[i] and Y.top() < A[i])
        {
            ok = false;
            break;
        }
        if(A[i] < X.top() and (X.top() < Y.top() or Y.top() < A[i]))
            X.push(A[i]), R[i] = 0, cout << "push X " << A[i] << endl;
        else
            Y.push(A[i]), R[i] = 1, cout << "push Y " << A[i] << endl;
        while(lo <= n and (X.top() == lo or Y.top() == lo))
        {
            if(X.top() == lo) X.pop();
            if(Y.top() == lo) Y.pop();
            lo++;
        }
    }
    return {ok, R};
}

bool check_solution(const vector<uint32_t>& A, const vector<bool>& R)
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
        if(check_solution(A, R))
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
    for(uint32_t i = 0; i < n; i++) cin >> A[i];
    auto r = solve(A);
    if(r.first)
    {
        cout << "TAK\n";
        for(uint32_t b : r.second)
            cout << uint32_t(b)+1 << " ";
    }
    else
        cout << "NIE";
}
