#include <bits/stdc++.h>
#include "extended_euclidean.h"
using namespace std;

const int64_t MOD = 1e9+7;

inline int64_t modSum(int64_t a, int64_t b) {
    return (a+b >= MOD ? a+b-MOD : a+b);
}
inline int64_t modSub(int64_t a, int64_t b) {
    return (a-b < 0 ? a-b+MOD : a-b);
}
inline int64_t modMul(int64_t a, int64_t b) {
    return (a*b)%MOD;
}
int64_t inv_mod(int64_t a, int64_t m = MOD) {
	int64_t x, y;
  extended_gcd(a, m, x, y);
	return (x%m + m)%m;
}
int64_t modDiv(int64_t a, int64_t b) {
    return modMul(a, inv_mod(b, MOD));
}
//O(log(a))
int64_t bigModMul(int64_t a, int64_t b) {
	int64_t ans = 0LL;
	b %= MOD;
	while (a > 0) {
		if (a & 1) ans = modSum(ans, b);
		b = modMul(b, 2LL);
		a >>= 1;
	}
	return ans;
}
uint64_t bigModMul_2(uint64_t a, uint64_t b) {
	long double x;
	uint64_t c;
	int64_t r;
	if (a >= MOD) a %= MOD;
	if (b >= MOD) b %= MOD;
	x = a;
	c = (x * b) / MOD;
	r = (int64_t) (a * b - c * MOD) % (int64_t)MOD;
	return (r < 0 ? r+MOD : r);
}
