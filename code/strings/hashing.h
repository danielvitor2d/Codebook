#include <bits/stdc++.h>
using namespace std;

/*
Cuidado ao subtrair de unsigned
Trocar %MOD por += MOD ou -= MOD
Cuidado com caracteres como #, $, @
/*

/*
	Small Primes:
		31, 53
	Large Primes:
		(1e6+3), (1e8+7), 100003621, (1e9+7), (1e9+9), (1LL<<61)-1
*/

struct StringHashing {
	const uint64_t MOD = (1LL<<61)-1;
	const int base = 31;
	uint64_t modMul(uint64_t a, uint64_t b) {
		uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
		uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
		uint64_t ret = (l&MOD) + (l>>61) + (h << 3) + (m >> 29) + ((m << 35) >> 3) + 1;
		ret = (ret & MOD) + (ret>>61);
		ret = (ret & MOD) + (ret>>61);
		return ret-1;
	}
	inline int getInt(char c) {
		return (c-'a'+1);
	}
	/*
		hs[i] = s[0]*p^(i) + s[1]*p(i-1) + ... + s[i-1]*p + s[i]
	*/
	vector<uint64_t> hs, p;
	StringHashing (const string &s) {
		int n = s.size();
		hs.resize(n); p.resize(n);
		p[0] = 1;
		hs[0] = getInt(s[0]);
		for (int i = 1; i < n; ++i) {
			p[i] = modMul(p[i-1], base);
			hs[i] = modMul(hs[i-1], base) + getInt(s[i]);
			if (hs[i] >= MOD) hs[i] -= MOD;
		}
	}
	/*
		hs[i..j] = hs[j] - hs[i-1] * p^(j-i+1)
	*/
	uint64_t getValue(int l, int r) {
		if (l > r) return -1;
		uint64_t res = hs[r];
		if (l > 0) {
			res = res + MOD - modMul(p[r-l+1], hs[l-1]);
			if (res >= MOD) res -= MOD;
		}
		return res;
	}
};

struct StringHashingDoubleMod {
	const uint64_t MOD1 = 1e6+3;
	const uint64_t MOD2 = 1e8+7;
	const int base = 31;
	uint64_t modMul(uint64_t a, uint64_t b, const uint64_t &MOD) {
		uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
		uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
		uint64_t ret = (l&MOD) + (l>>61) + (h << 3) + (m >> 29) + ((m << 35) >> 3) + 1;
		ret = (ret & MOD) + (ret>>61);
		ret = (ret & MOD) + (ret>>61);
		return ret-1;
	}
	int getInt(char c) {
		return (c-'a'+1);
	}
	vector<uint64_t> h1, h2, p1, p2;
	StringHashingDoubleMod (const string &s) {
		int n = s.size();
		h1.resize(n); h2.resize(n); p1.resize(n); p2.resize(n);
		p1[0] = 1;
		p2[0] = 1;
		h1[0] = getInt(s[0]);
		h2[0] = getInt(s[0]);
		for (int i = 1; i < n; ++i) {
			p1[i] = modMul(p1[i-1], base, MOD1);
			p2[i] = modMul(p2[i-1], base, MOD2);
			h1[i] = modMul(h1[i-1], base, MOD1) + getInt(s[i]);
			if (h1[i] >= MOD1) h1[i] -= MOD1;
			h2[i] = modMul(h2[i-1], base, MOD2) + getInt(s[i]);
			if (h2[i] >= MOD2) h2[i] -= MOD2;
		}
	}
	pair<uint64_t, uint64_t> getValue(int l, int r) {
		if (l > r) return {-1, -1};
		pair<uint64_t, uint64_t> res;
		res.first = h1[r];
		if (l > 0) {
			res.first = res.first + MOD1 - modMul(p1[r-l+1], h1[l-1], MOD1);
			if (res.first >= MOD1) res.first -= MOD1;
		}
		res.second = h2[r];
		if (l > 0) {
			res.second = res.second + MOD2 - modMul(p2[r-l+1], h2[l-1], MOD2);
			if (res.second >= MOD2) res.second -= MOD2;
		}
		return res;
	}
};
