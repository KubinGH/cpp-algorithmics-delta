 #include <bits/stdc++.h>

 using namespace std;

 int main()
 {
     ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

     string S;
     cin >> S;

     const size_t n = S.size();

     vector<unsigned> A(n);
     for(size_t i = 0; i < n; i++)
        A[i] = S[i] - '0';

    vector<array<unsigned, 13>> Q(n + 1);
    for(size_t i = 1; i <= n; i++)
        Q[i][A[i-1]]++;
    for(size_t i = 1; i < n; i++)
        for(size_t r = 0; r < 13; r++)
            Q[i+1][(10*r + A[i]) % 13] += Q[i][r];

    uint64_t result = 0;
    for(size_t i = 1; i <= n; i++)
        result += Q[i][0];
    cout << result;
 }
