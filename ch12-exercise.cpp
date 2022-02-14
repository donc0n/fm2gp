#include <iostream>
#include <cmath>
#include <time.h>
#include <random>
#include "ch12.h"

using namespace std;

int counter = 0;

long long int rand_digit(int digit) {
	long long int ret(0);
	while (digit >= 15) {
		srand((unsigned)time(NULL)+counter);
		ret = ret << 15 | rand();
		digit -= 15;
		counter += 1;
	}
	ret = (ret << digit) | int((rand() % (2 << digit)));
	return ret;
}


void gcd_test(int digit) {
	clock_t start, end;
	clock_t timer1(0), timer2(0);

	for (int i = 0; i < 300000; i++) {
		long long int a = rand_digit(digit);
		long long int b = rand_digit(digit);
		start = clock();
		stein_gcd(a, b);
		end = clock();
		timer1 += (end - start);
		start = clock();
		gcd(a, b);
		end = clock();
		timer2 += (end - start);
	}
	cout << "stein_gcd: " << timer1 << "ms ";
	cout << "euclidian_gcd: " << timer2 << "ms";
	cout << "  [0, " << pow(2, digit) << ")\n";
}


template <BinaryInteger N>
std::pair<N, N> extended_stein_gcd(N p, N q) {
	if (p < N(0)) p = -p;
	if (q < N(0)) q = -q;
	if (p == N(0)) return { q, 1 };
	if (q == N(0)) return { p, 1 };

	// p > 0 && q > 0
	int shift = 0;
	while (even(p) && even(q)) { p >>= 1; q >>= 1; ++shift; }

	N p0 = p, q0 = q;
	N sp = 1, sq = 0; // sp * p_0 + sq * q_0 = p
	N tp = 0, tq = 1; // tp * p_0 + tq * q_0 = q

	while (even(p)) {
		if (!(even(sp) && even(sq))) {
			sp -= q0;
			sq += p0;
		}
		p >>= 1;
		sp >>= 1;
		sq >>= 1;
	}

	// odd(p)
	while (q != N(0)) {
		while (even(q)) {
			if (!(even(tp) && even(tq))) {
				tp -= q0;
				tq += p0;
			}
			q >>= 1;
			tp >>= 1;
			tq >>= 1;
		}
		if (p > q) {
			std::swap(q, p);
			std::swap(tp, sp);
			std::swap(tq, sq);
		}
		q -= p;
		tp -= sp;
		tq -= sq;
	}

	// p == q
	return { sp, p << shift }; // sp*(p_0*k) + sq*(q_0*k) = r' * k
}


template <BinaryInteger N>
void extended_stein_gcd_test(N p, N q) {
	auto x = extended_gcd(p, q);
	auto y = (x.second - p * x.first) / q;
	cout << "extended_gcd: " << p << " * (" << x.first << ") + " << q << " * (" << y << ") = " << x.first * p + y * q << endl;
	x = extended_stein_gcd(p, q);
	y = (x.second - p * x.first) / q;
	cout << "extended_stein_gcd: " << p << " * (" << x.first << ") + " << q << " * (" << y << ") = " << x.first * p + y * q << endl;
	cout << endl;
}


int main() {
	// exercise 12.1
	cout << "TEST START ...\n";
	gcd_test(15); // 2^15
	gcd_test(31); // 2^31
	gcd_test(63); // 2^63
	cout << endl;

	// exercise 12.7
	extended_stein_gcd_test(121, 66);
	extended_stein_gcd_test(196, 42);
	extended_stein_gcd_test(253, 161);
}
