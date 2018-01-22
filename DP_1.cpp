
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define M 100
#define W 100

typedef int quant;
#define quant0 0

#define __min(a, b) (((a)<(b))?(a):(b))
#define __max(a, b) (((a)>(b))?(a):(b))

int get_min(int list[], int num) {
	int ans = list[0];
	for (int i = 1; i < num; ++i)
		ans = __min(list[i], ans);

	return ans;
}

void solve(quant mines[], int worker[], int num, int workers, quant solution_space[M][W]) {
	if(workers < get_min(worker, num)) return;
	if(num==0) return;

	solve(mines, worker, num - 1, workers, solution_space);
	solve(mines, worker, num - 1, workers - worker[num], solution_space);

	solution_space[num][workers] = __max(
		solution_space[num-1][workers-worker[num]] + mines[num], solution_space[num-1][workers]);

	return;
}

quant solve_mine_problem(quant mines[], int worker[], int num, int workers) {
	quant solution_space[M][W];
	for (int i = 0; i <= num; ++i) {
		memset(solution_space[i], quant0, workers+1);
		// for (int j = 0; j <= workers; ++j)
		// 	printf("%d", solution_space[i][j]);
		// printf("\n");
	}

	solve(mines, worker, num, workers, solution_space);

	for (int i = num; i >= 0; --i) {
		for (int j = 0; j <= workers; ++j)
			printf("%d\t", solution_space[i][j]);
		printf("\n");
	}

	return solution_space[num][workers];
}

int main() {
	freopen("input.txt", "r", stdin);

	quant mines[M+1]; int worker[M+1];
	int num;
	scanf("%d", &num);
	for(int i = 0; i < num; i ++) scanf("%d %d", &mines[i+1], &worker[i+1]);
	
	int workers; scanf("%d", &workers);

	printf("%d\n", solve_mine_problem(mines, worker, num, workers));

	return 0;
}