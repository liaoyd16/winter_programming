
#include <assert.h>
#include <cstdio>
#include <cstring>

#define MAXD 5010
#define B 1000000
#define MAXLEN 835

#define times_10(n) (((n)<<3) + ((n)<<1))

int pow_10(int k) {
	int ans = 1;
	for(; k > 0; k --) {
		ans = times_10(ans);
	}
	return ans;
}

struct Long {
	unsigned int digits[MAXLEN];	
	int len;
	inline void clear() {
		len = 0;
	}
};

static void print6(unsigned int n) {
	int tmp;
	for (int i = 5; i >= 0; --i) {
		printf("%d", tmp = n / pow_10(i));
		n -= tmp*pow_10(i);
	}
}

static void print(const Long& ll) {
	printf("%d,", ll.digits[ll.len-1]);
	for(int i = ll.len-2; i >= 0; i --) {
		print6(ll.digits[i]);
		printf(",");
	}
	if(0 == ll.len) printf("NAN");
	printf("\n");
}

static void input(Long& ll) {
	char digits[MAXD]; int l;

	for(int i = 0; i < 6; i ++) digits[i] = '0';
	scanf("%s", digits + 5);
	l = strlen(digits + 5);

	// printf("%s\n", digits+8);
	// printf("%d\n\n", l);

	int blocks = (l-1)/6 + 1, rem = l - (blocks-1)*6;
	int read = rem-1;

	int block, power;
	for(block = blocks-1; block >= 0; block --) {
		ll.digits[block] = 0;
		for(power = 5; power >= 0; power --) {
			ll.digits[block] += pow_10(power) * (digits[read++] - '0');
		}
	}
	ll.len = blocks;
}

long long rslt[MAXLEN*2];
static void mult(const Long& l1, const Long& l2) {
	// printf("l1, l2:\n");
	// print(l1); print(l2);
	for(int d = 0; d < l1.len + l2.len; d ++) rslt[d] = 0;

	for(int dgt = 0; dgt < l1.len; dgt ++) {
		for(int l2dgt = 0; l2dgt < l2.len; l2dgt ++) {
			rslt[dgt + l2dgt] += (long long)l1.digits[dgt] * (long long)l2.digits[l2dgt];
			// printf("%d*%d = %lld ", l1.digits[dgt], l2.digits[l2dgt], (long long)l1.digits[dgt] * (long long)l2.digits[l2dgt]);
		}
		// printf("\n");
	}
	// for (int i = 0; i < l1.len+l2.len; ++i) {
	// 	printf("%lld, ", rslt[i]);
	// } printf("\n");

	long long add;
	for (int i = 0; i < l1.len+l2.len-1; ++i) {
		// rslt[i]
		add = rslt[i] / B;
		rslt[i] -= B*add;
		rslt[i+1] += add;
		// printf("rslt[i]=%lld, rslt[i+1]=%lld\n", rslt[i], rslt[i+1]);
		// assert(rslt[i+1]>=0);
	}

	int startdgt = (rslt[l1.len+l2.len-1] > 0) ? l1.len+l2.len-1 : l1.len+l2.len-2;
	printf("%lld", rslt[startdgt]);
	bool is_start_dgt = true;
	for (int dgt = startdgt-1 ; dgt >= 0 ; dgt --) {
		if(is_start_dgt) {
			if(rslt[dgt]==0) continue;
			else is_start_dgt = false;
		}
		print6(rslt[dgt]);
		// printf(",");
	} printf("\n");
}

int main() {
#ifndef _OJ_
	freopen("feed.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
#endif
	setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

	int n; scanf("%d", &n);

	for(;n > 0; n--) {
		Long l1, l2;
		// l1.clear(); l2.clear();
		input(l1); input(l2);
		mult(l1, l2);
	}

	return 0;
}