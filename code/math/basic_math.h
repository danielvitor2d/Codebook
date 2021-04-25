#include <string>
uint64_t modMul(uint64_t a, uint64_t b, uint64_t MOD) {
	return (__uint128_t)a*b%MOD;
}
uint64_t binpow(uint64_t base, uint64_t exp, uint64_t MOD) {
	base %= MOD;
	uint64_t res = 1;
	while (exp > 0) {
		if (exp & 1) res = modMul(res, base, MOD);
		base = modMul(base, base, MOD);
		exp >>= 1;
	}
	return res;
}
uint64_t bigExp(uint64_t base, std::string exp, uint64_t MOD) {
	base %= MOD;
	uint64_t ans = 1LL;
	for (char c : exp) {
		ans = binpow(ans, 10LL, MOD);
		ans = modMul(ans, binpow(base, c-'0', MOD), MOD);
	}
	return ans;
}
uint64_t gcd(uint64_t a, uint64_t b) { return (b == 0 ? a : gcd(b, a%b)); }
uint64_t lcm(uint64_t a, uint64_t b) { return a / gcd(a, b) * b; }
uint64_t binary_gcd(uint64_t a, uint64_t b) {
	if (a == 0 or b == 0)
		return a ^ b;
	int shift = __builtin_ctzll(a | b);
	a >>= __builtin_ctzll(a);
	do {
		b >>= __builtin_ctzll(b);
		if (a > b) 
			std::swap(a, b);
		b -= a;
	} while (b);
	return a << shift;
}
namespace ModHash{
  const uint64_t MOD = (1ll<<61) - 1;
  uint64_t modmul(uint64_t a, uint64_t b){
    uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
    uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    uint64_t ret = (l&MOD) + (l>>61) + (h << 3) + (m >> 29) + ((m << 35) >> 3) + 1;
    ret = (ret & MOD) + (ret>>61);
    ret = (ret & MOD) + (ret>>61);
    return ret-1;
  }
};