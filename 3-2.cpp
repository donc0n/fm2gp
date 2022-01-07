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


int main(void) {
	int limit = 100000;
	bool t1(0); uint8_t t2(0); uint16_t t3(0); uint32_t t4(0); uint64_t t5(0);
	sift_test(t1, limit);
	sift_test(t2, limit);
	sift_test(t3, limit);
	sift_test(t4, limit);
	sift_test(t5, limit);
}