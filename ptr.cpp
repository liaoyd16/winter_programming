
//指针

#include <iostream>


using namespace std;

template <typename T>
void test() {
	T x[2];
	T* run = x, *y = run + 1;
	cout << (void*)run << " " << (void*)y << endl;
	cout << sizeof(T) << endl;
}

class Test0 {
	char _datab;
	char _dataa;
	char _data;
	char _data0;
	char _dataaa;
	int* _ptr;
	int* _ptr0;
};

class Test1 {
	Test0 t;
	// char _data;
	// int* _ptr;
};

int main() {
	// cout << "bool:\t"; test<bool>();
	// cout << "int:\t"; test<int>();
	// cout << "short:\t"; test<short>();
	// cout << "char:\t";test<char>();
	// cout << "int*:\t"; test<int*>();
	// cout << "long:\t"; test<long>();
	// cout << "long long:\t"; test<long long>();

	// cout << "Test*:\t"; test<Test*>();
	cout << "Test0:\t"; test<Test0>();
	// cout << "Test1:\t"; test<Test1>();
}