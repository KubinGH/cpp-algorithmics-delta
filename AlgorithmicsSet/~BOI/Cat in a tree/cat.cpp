#include <bits/stdc++.h>

using namespace std;

size_t get(const deque<size_t>& A, size_t i)
{
    return i < A.size() ? A[i] : 0;
}
void fix(deque<size_t>& A, size_t d)
{
    while(A.size() > d+1)
        A.rbegin()[1] = max(A.rbegin()[0], A.rbegin()[1]), A.pop_back();
}
void solve(size_t d, size_t u, deque<size_t>& state, const vector<vector<size_t>>& children)
{
    state.push_back(1);
    for(auto v : children[u])
    {
        deque<size_t> substate;
        solve(d, v, substate, children);
        substate.push_front(0);
        fix(substate, d);
        if(state.size() < substate.size())
            swap(state, substate);

        auto conv = state;
        for(size_t r = 0; r < substate.size(); r++)
            conv[r] = max(conv[r], substate[r]);
        for(size_t r1 = 0; r1 < state.size(); r1++)
            conv[r1] = max(conv[r1], state[r1] + get(substate, max(r1, d - r1)));
        for(size_t r2 = 0; r2 < substate.size(); r2++)
            conv[r2] = max(conv[r2], get(state, max(r2, d - r2)) + substate[r2]);
        state = conv;
    }
    fix(state, d);
    for(size_t i = state.size() - 1; i --> 0; )
        state[i] = max(state[i], state[i + 1]);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, d;
    cin >> n >> d;

    vector<vector<size_t>> children(n);
    for(size_t i = 1; i < n; i++)
    {
        size_t j;
        cin >> j;
        children[j].push_back(i);
    }

    deque<size_t> state;
    solve(d, 0, state, children);

    cout << *max_element(state.begin(), state.end()) << endl;
}
