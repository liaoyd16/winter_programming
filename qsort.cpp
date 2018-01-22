
#include <assert.h>
#include <random>
#include <cstdlib>
#include <cstdio>

#define N 100

template <typename T>
void swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

int randint(int size, int start = 0) {
	//start + [0, size - 1]
	srand((unsigned)clock());
	return start + rand()%size;
}

int scnt = 0;

template <typename T>
void qsort(T* list, int n) {
	if(n <= 1) return;

	//pick pivot
	swap<T>(list[0], list[randint(n)]);
	T pivot = list[0];

	//LUG
	int lo = 0, hi = n-1;
	while(lo < hi) {
		while(list[hi]>=pivot && hi > lo) hi --;
		if(hi == lo) break;
		list[lo] = list[hi];
		scnt ++; ////
		while(list[lo]<=pivot && lo < hi) lo ++;
		if(hi == lo) break;
		list[hi] = list[lo];
		scnt ++; ////
	}
	list[lo] = pivot;

	// printf("pivot = %d\n", pivot);
	// for (int i = 0; i < n; ++i) {
	// 	printf("%d ", list[i]);
	// } printf("\n");

	qsort(list, lo);
	qsort(list+lo+1, n - lo - 1);
}

int* shuffled(int size) {
	int *ans = new int[size];
	for (int i = 0; i < size; ++i)
		ans[i] = i;
	//shuffle
	for (int i = size - 1; i > 1; --i) {
		swap<int>(ans[i], ans[randint(i+1)]);
	}

	return ans;
}

int main() {
	// printf("%d\n", randint(10));

	int n = 100;
	int *list = shuffled(n);

	qsort<int>(list, n);

	for (int i = 0; i < n; ++i) {
		printf("%d ", list[i]);
	} printf("\n");

	return 0;
}