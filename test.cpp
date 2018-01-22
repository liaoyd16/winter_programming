
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define N 1000

#define max(a, b) (((a)>(b)?(a):(b)))

int main() {
	freopen("feed.txt", "r", stdin);

	int *vals = new int[N];
	int n; scanf("%d", &n);

	for (int i = 0; i < n; i ++) {
		scanf("%d", &vals[i]);
	}

	int maxn = 0;
	for (int i = 0; i < n-1; i ++) {
		maxn = max ( abs(vals[i] - vals[i + 1]), maxn );
	}

	printf("%d\n", maxn);

	return 0;
}