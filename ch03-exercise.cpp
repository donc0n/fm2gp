#include <iostream>
#include <vector>
#include <time.h>
#include "ch03.h"

template <typename T, Integer N>
void sift_test(T t, N limit) {
	std::vector<T> v(limit);
	clock_t start, end;
	start = clock();
	sift(begin(v), limit);
	end = clock();
	std::cout << "\nduration(ms): " << (end - start) << "\n";
}


template <RandomAccessIterator I, Integer N>
N pi(I first, N n) {
	N i{ 0 };
	N cnt{ 1 };
	if (n <= 1) return 0;
	if (n == 2) return 1;
	while (i <= (n-3)/2) {
		if (*first) {
			cnt++; // 2 * i + 3;
		}
		++first;
		++i;
	}
	return cnt;
}


int main(void) {
	// exercies 3.2
	int limit = 100000;
	bool t1(0); uint8_t t2(0); uint16_t t3(0); uint32_t t4(0); uint64_t t5(0);
	sift_test(t1, limit);
	sift_test(t2, limit);
	sift_test(t3, limit);
	sift_test(t4, limit);
	sift_test(t5, limit);
	
	// exercies 3.3
	std::vector<int> v(500);
	sift(begin(v), 500);
	int tmp;
	for (int i = 0; i < 108; i++) {
		tmp = pi(begin(v), i);
		for (int j = 0; j < tmp; j++) {
			std::cout << " ";
		}
		std::cout << "*" << std::endl;
	}
}
