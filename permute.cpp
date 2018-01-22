#include <iostream>
// #include <algorithm>
using namespace std;

template <typename T>
void swapp (T& a, T& b){
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
void reverse(T* lo, T* hi) {
	T *l = lo, *r = hi;
	while(l++ < r--) {
		swapp<T>(*l, *r);
	}
}

template <typename T>
bool next_permutation(T* lo, T* hi) {
	//[lo, hi)
	if(lo + 1 >= hi) 
		 return false;
	if(hi - lo == 2) {
		if(*(hi-1) > *lo) {
			swapp<T>(*lo, *(hi-1));
			return true;
		}
		else {
			return false;
		}
	}
	//find x < y1
	T* x = hi;
	while(x!=lo) {
		if(*(x-1) < *x) {
			break;
		}
		x --;
	}
	if(x==lo) return false;
	x--;
	//find yi > x
	T* y = x+1;
	for(; y<hi && *x<*y; y ++) ;
	swapp(*(y-1), *x);

	reverse(x+1, hi-1);

	return true;
}

int main()
{
	int num[4]={1,3,2};

    // int cnt = 0;
    do
    {
    	// if(10 == cnt++) return 1;
    	// next_permutation<int>(num, num+3);
        cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<endl;
    } while(next_permutation<int>(num,num+3));

    return 0;
}