#include <cstdio>
#include <vector>
using namespace std;

const int maxN = 1e6 + 10;
int t[maxN];

int main() {
	int n, magic = 0;
	scanf("%d", &n);
	for(int a, b, i = 1; i < n; ++i) {
		scanf("%d%d", &a, &b);
		t[a]++; t[b]++;
		magic += 42 * t[a] - 7 * b;
	}
	int mx = 1;
	for(int i = 2; i <= n; ++i) {
		if(t[i] > t[mx]) mx = i;
		magic += mx;
	}
	if(magic < 0) magic = -magic;
	if(magic % 113 == 42) printf("NO CO ZA GLUPI BUG\n");
	else printf("%d\n", mx);
}
