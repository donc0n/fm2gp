#include <iostream>
#include <bitset>
#include <random>
#include <time.h>
#include "ch07.h"
#include "ch12.h"
#include "ch13.h"

using namespace std;

// exercise 13.1
template <Integer I>
bool is_carmichael(I n) {
	if (n < I(2) || is_prime(n)) return false;
	for (I i = 2; i < n; i++) {
		if (gcd(n, i) == 1) { // n과 서로소인 모든 i < n 에 대해 b^(n-1) = 1 mod n 만족해야 한다.
			I remainder(power_semigroup(i, n - I(1), modulo_multiply<I>(n)));
			if (remainder != I(1)) return false;
		}
	}
	return true;
}


// exercise 13.3
__int64 generate_big_random(unsigned int seed) { // generate BIG random value
	bitset<16> bs;
	srand((unsigned)time(NULL)+ seed);
	bs.set();
	for (int j = 1; j < 16; j++) { if (even(rand())) bs.reset(j); }
	return bs.to_ullong();
}


__int64 generate_prime(unsigned int seed) {
	
__int64 p, q, k, w;
	bool check;
	do {
		p = generate_big_random(seed);
		check = true;
		if (p == 0) p += 1;
		q = p - 1;
		k = 0;
		while (even(q)) { q >>= 1; k += 1; }
		for (int i = 0; i < 10; i++) {
			w = rand() % p;
			check &= miller_rabin_test(p, q, k, w);
			if (!check) break;
		}
	} while (!check);
	return p;
}


vector<__int64> generate_keys() {
	// generate prime numbers
	cout << "/...Key Generating.../\n";
	__int64 p1, p2, pub, prv, n, euler_n;
	p1 = generate_prime(1);
	p2 = generate_prime(10);
	n = p1 * p2;
	euler_n = (p1 - 1)*(p2 - 1);
	
	// generate pub, prv
	do {
		pub = rand() % euler_n;
	} while (gcd(pub, euler_n) != 1);
	prv = multiplicative_inverse(pub, euler_n);
	cout << "/...Completed.../\n";

	return { pub, prv, n };
}


__int64 encode_rsa(__int64 plaintext_block, __int64 pub, __int64 n) {
	return power_semigroup(plaintext_block, pub, modulo_multiply<__int64>(n));
}

__int64 decode_rsa(__int64 cyphertext_block, __int64 prv, __int64 n) {
	return power_semigroup(cyphertext_block, prv, modulo_multiply<__int64>(n));
}


int main() {
	// exercise 13.2
	int n = 0, cnt = 0;
	while (cnt < 7) {
		n += 1;
		if (is_carmichael(n)) {
			cnt += 1;
			cout << n << " ";
		}
	}
	cout << endl << endl;

	// exercise 13.4
	auto key_set = generate_keys();
	auto pub = key_set.at(0);
	auto prv = key_set.at(1);
	auto s = key_set.at(2);

	decltype(s) plain, cypher, decypher;
	plain = 123456789;
	cypher = encode_rsa(plain, pub, s);
	cout << "encoded: " << cypher << endl;
	decypher = decode_rsa(cypher, prv, s);
	cout << "decoded: " << decypher << endl;
}
