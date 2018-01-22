
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

#define MAXN 100
#define MAXM 100

#define C1(n) (n)
#define C2(n) (n*(n-1)/2)
#define C3(n) (n*(n-1)*(n-2)/6)
#define C4(n) (n*(n-1)*(n-2)*(n-3)/24)

long long fact(long long n) {
	if(n<=1) return 1;
	long long ans = 1;
	for (; n >= 2; n--) {
		ans *= n;
	}
	return ans;
}

struct P_N_M {
private:
	double solution_space[MAXM][MAXN];
	int _m;
public:
	P_N_M(int m);
	double p_n(int n);
	void print() {
		for (int j = 0; j <= 100 ; ++j) {
			for (int i = 0; i <= _m; ++i) {
				printf("%f\t", solution_space[i][j]);
			}
			printf("\n");
		}
	}
};

P_N_M::P_N_M(int m) : _m(m) {
	//初始化
	for (int i = 0; i <= m; ++i) {
		memset(solution_space[i], 0, MAXN);
	}
}

double P_N_M::p_n(int n) {
	//0 - 边界：l1: m = 0; l2: n = 4m
	//l1:
	for (int ni = 0; ni <= n; ++ni) {
		solution_space[0][ni] = 0;
	}
	//l2:
	for (int mi = 0; mi < _m; ++mi) {
		printf("%f %f\n", (double)fact(4*mi), pow(24, mi));
		solution_space[mi][4*mi] = (double)fact(4*mi)/pow(24, mi);
	}

	//m-递推
	for (int i = 1; i < _m; ++i) {
		for (int j = 4*i+1; j <= n; ++j) {
			solution_space[i][j] = 
			solution_space[i-1][j] + 
			solution_space[i-1][j-1] * C1(n) + 
			solution_space[i-1][j-2] * C2(n) +
			solution_space[i-1][j-3] * C3(n) +
			solution_space[i-1][j-4] * C4(n);
		}
	}

	return solution_space[_m][n];
}

int main() {

	P_N_M p_machine(10);

	printf("%f\n", p_machine.p_n(6));
	p_machine.print();

	return 0;
}