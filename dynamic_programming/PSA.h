#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;

/*
Answer queries:
Q(L, R) = 1*A[L] + 2*A[L+1] + 3*A[L+2] + ... (R-L+1)*A[R]
*/


int n, a[maxn];
int psa[maxn], ips[maxn];
int q, l, r, ans;

void computePSA() {
	for (int i = 1; i <= n; ++i) {
		psa[i] = psa[i-1] + a[i];
		ips[i] = ips[i-1] + i * a[i];
	}
	while (q--) {
		cin >> l >> r;
		ans = ips[r] - ips[l-1] - (l - 1) * (psa[r] - psa[l-1]);
		cout << ans << '\n';
	}
}

