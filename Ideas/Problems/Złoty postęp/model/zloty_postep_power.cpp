#include <bits/stdc++.h>

using namespace std;

typedef int32_t I;

I n, m, k;

const I max_nm = 1e6, max_k = 1e9;

I t[max_nm];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> m >> k;

    for(I i = 0; i < n; ++i) {
        cin >> t[i];
    }

    for(I i = 0; i < m; ++i) {
        char o;
        cin >> o;
        if(o == '?') {
            I a, b;
            cin >> a >> b;

            bool ok = true;
            for(I j = a + 2; j <= b; ++j) {
                if(t[j] != (t[j - 1] + t[j - 2]) % k) {
                    ok = false;
                    break;
                }
            }
            cout << (ok ? "TAK" : "NIE") << '\n';
        } else if(o == '+') {
            I a, b, x;
            cin >> a >> b >> x;

            for(I j = a; j <= b; ++j) {
                t[j] += x;
                t[j] %= k;
            }
        }
    }

    return 0;
}
