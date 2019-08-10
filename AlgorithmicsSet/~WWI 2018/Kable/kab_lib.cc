#include "kab.h"
#include <cstdio>
#include <algorithm>
using namespace std;

namespace kab {
    int *t;
    int n, plug_calls;

    void check_empty(int x)
    /* checks if t[x] == 0 and prints error if not */
    {
        if(t[x]) {
            printf("Koncowka %d zostala juz wykorzystana!\n", x);
            exit(0);
        }
    }
};
using namespace kab;


int init() {
    printf("Podaj liczbe kabli:\n");
    fflush(stdout);
    scanf("%d", &n);
    t = new int[2 * n + 1];

	for(int i=1;i<2*n+1;i++)
		t[i] = 0;

    printf("Podaj kable w postaci par koncowek (z przedzialu [1, %d])\n", 2 * n);
    fflush(stdout);
    for(int a, b, i = 0; i < n; ++i) {
        scanf("%d%d", &a, &b);
        check_empty(a);
        check_empty(b);
        t[a] = b;
        t[b] = a;
    }
    n *= 2;
    return n / 2;
}

void plug(bool B[]) {
    plug_calls++;
    for(int i = 1; i <= n; ++i)
        B[i] |= B[t[i]];
}

void answer(int ans[]) {
    int errors = 0;
    for(int i = 1; i <= n; ++i)
        errors += t[i] != ans[i] ? 1 : 0;
    if(errors)
        printf("ZLA ODPOWIEDZ\nbledow: %d\n", errors);
    else
        printf("OK\nWywolan funkcji \"plug\": %d\n", plug_calls);
    exit(0);
}
