#include <bits/stdc++.h>

using namespace std;

typedef int64_t I;
const I inf = 1e18;

I n, m, k;

const I max_nm = 1e6, max_k = 1e9;
const I tree_max_w = (1 << 20);

I add_mod_k(I a, I b) {
    return (a + 42 * k + b) % k;  // `b` may be arbitrarily negative (where arbitrary = -3k).
}

template<I (*f)(I, I), I neutral> struct tree {
    I value[2 * tree_max_w], collectivize[2 * tree_max_w], w;
    tree(I n) {
        for(w = 1; w < n; w *= 2);
    }

    I aggregate(I qb, I qe, I rb, I re, I i, I x = 0) {
        if(re < qb || rb > qe) {
            return neutral;
        }
        if(qb <= rb && re <= qe) {
            collectivize[i] = add_mod_k(collectivize[i], x);
            value[i] = add_mod_k(value[i], x);
            return value[i];
        }

        collectivize[2 * i + 0] = add_mod_k(collectivize[2 * i + 0], collectivize[i]);
        value[2 * i + 0] = add_mod_k(value[2 * i + 0], collectivize[i]);
        collectivize[2 * i + 1] = add_mod_k(collectivize[2 * i + 1], collectivize[i]);
        value[2 * i + 1] = add_mod_k(value[2 * i + 1], collectivize[i]);

        collectivize[i] = 0;

        I mid = (rb + re) / 2;

        I c = f(aggregate(qb, qe, rb, mid, 2 * i + 0, x),
                aggregate(qb, qe, mid + 1, re, 2 * i + 1, x));

        value[i] = f(value[2 * i + 0], value[2 * i + 1]);

        return c;
    }
    I aggregate(I qb, I qe, I x = 0) {
        return aggregate(qb, qe, 0, w - 1, 1, x);
    }
};

I min_(I a, I b) {
    return min(a, b);
}
I max_(I a, I b) {
    return max(a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> m >> k;

    static tree<min_, inf> min_tree(n);
    static tree<max_, 0> max_tree(n);

    static I t[max_nm];
    for(I i = 0; i < n; ++i) {
        cin >> t[i];

        if(i >= 2) {
            min_tree.aggregate(i, i, add_mod_k(t[i], -t[i - 1] - t[i - 2]));
            max_tree.aggregate(i, i, add_mod_k(t[i], -t[i - 1] - t[i - 2]));
        }
    }

    for(I i = 0; i < m; ++i) {
        char o;
        cin >> o;
        if(o == '?') {
            I a, b;
            cin >> a >> b;

            cout << (min_tree.aggregate(a + 2, b) == 0 && max_tree.aggregate(a + 2, b) == 0 ? "TAK" : "NIE") << '\n';
        } else if(o == '+') {
            I a, b, x;
            cin >> a >> b >> x;

            if(a >= 2) {  // First two fields don't matter.
                min_tree.aggregate(a, a, x);
                max_tree.aggregate(a, a, x);
            }

            min_tree.aggregate(a + 2, min(n - 1, b + 2), -x);
            max_tree.aggregate(a + 2, min(n - 1, b + 2), -x);

            if(b + 1 < n) {
                min_tree.aggregate(b + 1, b + 1, -x);
                max_tree.aggregate(b + 1, b + 1, -x);
            }
        }
    }

    return 0;
}
