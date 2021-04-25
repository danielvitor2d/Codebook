#include "basic_math.h"

int64_t extended_gcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	int64_t g = extended_gcd(b, a%b, y, x);
	y -= x*(a/b);
	return g;
}