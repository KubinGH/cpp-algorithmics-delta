#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());

    cout << A.size() << endl;
}
