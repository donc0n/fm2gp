#include <iostream>

typedef unsigned line_segment;
typedef unsigned integer;

std::pair<integer, line_segment> quotient_remainder_fibonacci(line_segment a, line_segment b) {
    // 전제조건 b > 0
    if (a < b) return {integer(0), a};
    line_segment c = b;
    integer n(1);
    integer n_next(1);
    integer q(0);
	do {
        line_segment tmp = c; c = b + c; b = tmp;
        integer n_tmp(n_next); n_next = n + n_next; n = n_tmp;
	} while (a >= c);
    do {
        if (a >= b) { 
			a = a - b;
			q = n + q;
		}
		line_segment tmp = c - b; c = b; b = tmp;
        integer n_tmp(n_next - n); n_next = n; n = n_tmp;
    } while (b < c);
    return {q, a}; // 몫, 나머지
}


int main(void) {
	// excercise 4.7
	int a, b;
	std::cout << "input a, b: ";
	std::cin >> a;
	std::cin >> b;
	std::pair<integer, line_segment> p = quotient_remainder_fibonacci(a, b);
	std::cout << "quotient = " << p.first << ", remainder = " << p.second << std::endl;
}
