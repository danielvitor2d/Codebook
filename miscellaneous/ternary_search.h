#include <bits/stdc++.h>
using namespace std;

#define ftype long double;
#define f(x) x

const int inf = 0x3f3f3f3f;

void ternary_search_of_min(ftype top) {
	ftype lo = 0.0, hi = top;
	for (int i = 0; i < 100; ++i) {
		m1 = (lo * 2 + hi) / 3.0;
		m2 = (lo + 2 * hi) / 3.0;
		if (f(m1) > f(m2)) {
			lo = m1;
			ans = m2;
		} else {
			hi = m2;
			ans = m1;
		}
	}
	cout << f(ans) << " = " << ans << '\n';
}

void ternary_search_of_max(ftype top) {
	ftype lo = 0.0, hi = top;
	for (int i = 0; i < 100; ++i) {
		m1 = (lo * 2 + hi) / 3.0;
		m2 = (lo + 2 * hi) / 3.0;
		if (f(m1) < f(m2)) {
			lo = m1;
			ans = m2;
		} else {
			hi = m2;
			ans = m1;
		}
	}
	cout << f(ans) << " = " << ans << '\n';
}

void ternary_seach_of_min_on_integers(int top) {
	int lo = 0, hi = top, ans = inf;
	while (hi - lo > 4) {
		int m1 = (lo + hi) / 2;
		int m2 = m1 + 1;
		if (f(m1) > f(m2)) {
			lo = m1;
		} else {
			hi = m2;
		}
	}
	for (int i = lo; i <= hi; ++i) {
		ans = min(ans, f(i));
	}
}

void ternary_seach_of_max_on_integers(int top) {
	int lo = 0, hi = top, ans = -inf;
	while (hi - lo > 4) {
		int m1 = (lo + hi) / 2;
		int m2 = m1 + 1;
		if (f(m1) < f(m2)) {
			lo = m1;
		} else {
			hi = m2;
		}
	}
	for (int i = lo; i <= hi; ++i) {
		ans = max(ans, f(i));
	}
}