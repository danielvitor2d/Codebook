#include <bits/stdc++.h>
#include "basic_math.h"

using namespace std;

bool check_composite(uint64_t n, uint64_t a, uint64_t d, int s) {
	uint64_t x = binpow(a, d, n);
	if (x == 1 or x == n - 1)
		return false;
	for (int r = 1; r < s; ++r) {
		x = modMul(x, x, n);
		if (x == n - 1)
			return false;
	}
	return true;
}

bool MillerRabin(uint64_t n) {
	if (n < 4) 
		return (n == 2 or n == 3);

	uint64_t d = n - 1;
	int s = __builtin_ctzll(d);
	d >>= s;

	for (uint64_t a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
		// int a = 2 + rand() % (n - 3);  // nondeterministic version
		if (n == a)
			return true;
		if (check_composite(n, a, d, s)) 
			return false;
	}
	return true;
}

uint64_t pollard(uint64_t n) {
	auto f = [n](uint64_t x) { return (modMul(x, x, n) + 1) % n; };
	uint64_t x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 or binary_gcd(prd, n) == 1) {
		if (x == y)
			x = ++i, y = f(x);
		if ((q = modMul(prd, max(x, y) - min(x, y), n)))
			prd = q;
		x = f(x), y = f(f(y));
	}
	return binary_gcd(prd, n);
}

vector<uint64_t> factor(uint64_t n) {
	if (n == 1)
		return {};
	if (MillerRabin(n))
		return {n};
	uint64_t x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}