#include <bits/stdc++.h>
#include "extended_euclidean.h"
using namespace std;

const int64_t MOD = 1e9+7;

inline int64_t modSum(int64_t a, int64_t b, int64_t mod = MOD) {
    return (a+b >= mod ? a+b-mod : a+b);
}
inline int64_t modSub(int64_t a, int64_t b, int64_t mod = MOD) {
    return (a-b < 0 ? a-b+mod : a-b);
}
inline int64_t modMul(int64_t a, int64_t b, int64_t mod = MOD) {
    return (a*b)%mod;
}
int64_t inv_mod(int64_t a, int64_t m = MOD) {
    int64_t x, y;
  extended_gcd(a, m, x, y);
    return (x%m + m)%m;
}
int64_t modDiv(int64_t a, int64_t b, int64_t mod = MOD) {
    return modMul(a, inv_mod(b, mod), mod);
}
//O(log(a))
int64_t bigModMul(int64_t a, int64_t b, int64_t mod = MOD) {
	int64_t ans = 0LL;
	b %= mod;
	while (a > 0) {
		if (a & 1) ans = modSum(ans, b);
		b = modMul(b, 2LL);
		a >>= 1;
	}
	return ans;
}
uint64_t bigModMul_2(uint64_t a, uint64_t b, int64_t mod = MOD) {
	long double x;
	uint64_t c;
	int64_t r;
	if (a >= mod) a %= mod;
	if (b >= mod) b %= mod;
	x = a;
	c = (x * b) / mod;
	r = (int64_t) (a * b - c * mod) % (int64_t)mod;
	return (r < 0 ? r+mod : r);
}
