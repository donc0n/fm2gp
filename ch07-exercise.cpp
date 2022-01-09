#include <iostream>
#include <tuple>
#include "ch07.h"

using namespace std;

struct fib_op {
	tuple<int, int, int> operator()(const tuple<int, int, int>& x, const tuple<int, int, int>& y) const {
		int f0 = get<0>(x) * get<0>(y) + get<1>(x) * get<1>(y);
		int f1 = get<1>(x) * get<0>(y) + get<2>(x) * get<1>(y);
		int f2 = get<1>(x) * get<1>(y) + get<2>(x) * get<2>(y);
		return { f0, f1, f2 }; // fib(n+1) fib(n) fib(n-1)
	}
};


tuple<int, int, int> identity_element(fib_op) {
	return { 1, 0, 1 };
}


template <Integer N>
N fibonacci_power(N n) {
	tuple<int, int, int> fib = { 1, 1, 0 };
	fib_op op;
	fib = power_monoid(fib, n, op);
	return get<1>(fib);
}


int main(void) {
	// exercise 7.2
	int n;
	cout << "Input number: ";
	cin >> n;
	cout << "Fibonacci numbers = " << fibonacci_power(n) << endl;
}
