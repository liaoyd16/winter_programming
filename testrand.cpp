#include <iostream>
#include <ctime>
using namespace std;

int randint(int lo, int hi) {
	srand((unsigned)clock());
	return lo + rand()%(hi-lo);
}

double randdoub(double lo, double hi) {
	srand((unsigned)clock());
	return lo + (hi - lo) * (double)(rand()%100) / 100.;
}

int main() {
	// cout << randdoub(1, 3) << endl;
	srand((unsigned)clock());
	cout << rand() << endl;

	// for (int i = 0; i < 10; i ++) {
	// 	srand((unsigned)clock());
	// 	cout << rand()%100 << endl;
	// }
	// cout<<"Ten random numbers from "<<MIN<<
	// 	  " to "<<MAX<<" :/n"<<endl;   
	// for(i=0; i<10; i++)          //产生随机数
	// {
	// 	cout << MIN + int(MAX * rand() / (RAND_MAX + 1)) << "\t"; 
	// }
	// cout<<endl;
	return   0;   
} 