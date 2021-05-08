#include <bits/stdc++.h>

using namespace std;

vector<bool> has_dom(const vector<pair<int, int>>& A)
{
    const size_t n = A.size();

    vector<size_t> I(n);
    iota(I.begin(), I.end(), 0);
    sort(I.begin(), I.end(), [&](size_t i, size_t j) {
        return A[i] < A[j];
    });
    vector<bool> out(n);
    int y_min = INT_MAX;
    for(auto i : I)
    {
        auto y = A[i].second;
        out[i] = y_min <= y;
        y_min = min(y_min, y);
    }
    return out;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<pair<int, int>> A(n);
    for(auto& [x, y] : A)
        cin >> x >> y;

    for(auto& [x, y] : A)
        x = -x;
    for(auto b : has_dom(A))
        cout << b << ' ';
    cout << endl;
    for(auto& [x, y] : A)
        x = -x, y = -y;
    for(auto b : has_dom(A))
        cout << b << ' ';
    cout << endl;
}
