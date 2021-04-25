#include "modular.h"
const int MAXV = 1e6+5;

int64_t fat[MAXV], ifat[MAXV];
void init() {
	fat[0] = 1LL;
	for (int64_t i = 1; i < MAXV; ++i) {
		fat[i] = (fat[i-1] * i) % MOD;
	}
	ifat[MAXV-1] = inv_mod(fat[MAXV-1], MOD);
	for (int64_t i = MAXV-1; i >= 1; --i) {
		ifat[i-1] = (ifat[i] * i) % MOD;
	}
}