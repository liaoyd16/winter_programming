
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define N 1000000

int get_primes(bool *bitmap, int n) {
	memset(bitmap, false, n);
	bitmap[0] = bitmap[1] = true;

	int seeds = sqrt(n);

	// for(int i = 2; i < n; i += 2) {
	// 	bitmap[i] = true;
	// }

	for(int s = 3; s <= seeds; s ++) {
		for(int run = s*s; run < n; run += s) {
			bitmap[run] = true;
		}
	}

	// report
	// for (int i = 0; i < n; ++i) {
	// 	if(1-bitmap[i])
	// 		printf("%d %d\n", i, 1-bitmap[i]);
	// }
	int cnt = 0;
	for (int i = 1; i < n; i+=2)
		cnt += 1-bitmap[i];
	return cnt;
}

int main() {
	bool *primes = new bool[N];
	printf("%d", get_primes(primes, N));

	return 0;
}
