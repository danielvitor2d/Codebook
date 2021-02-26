#include <bits/stdc++.h>
using namespace std;
typedef long long int i64;
typedef double ftype;

const int mod = 1e9+7;
const int D = 4;

int d = D;

struct M {
	ftype m[D][D];

	ftype* operator[](int i) {
		return m[i];
	}

	M operator-(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = m[i][j] - oth[i][j];
			}
		}
		return res;
	}

	M operator+(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = m[i][j] + oth[i][j];
			}
		}
		return res;
	}

	M operator*(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = 0;
				for (int k = 0; k < d; ++k) {
					// res[i][j] = (res[i][j] + m[i][k] * oth[k][j] % mod + mod) % mod;
					res[i][j] += m[i][k] * oth[k][j];
				}
			}
		}
		return res;
	}	

	M exp(i64 e) {
		M res;
		for (int i = 0; i < d; ++i)
			for (int j = 0; j < d; ++j)
				res[i][j] = (i==j);
		M base = *this;
		while (e > 0) {
			if (e & 1LL) res = res * base;
			base = base * base;
			e >>= 1LL;
		}
		return res;
	}
};

struct operation {
	int op, a, b, c;
	double ang;
};

void geometric_operations(int &x, int &y, int &z, vector<pair<operation, int>> &v) {
	int m = v.size();
	M bases[m];
	for (int i = 0; i < m; ++i) {
		operation op = v[i].first;
		int k = v[i].second;
		if (op.op == 1) {        //Shift operation
			M base;
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					base[j][k] = (j == k);

			base[3][0] = op.a;
			base[3][1] = op.b;
			base[3][2] = op.c;
			bases[i] = base.exp(k);
		} else if (op.op == 2) { //Scaling operation
			M base;
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					base[j][k] = 0;

			base[0][0] = op.a;
			base[1][1] = op.b;
			base[2][2] = op.c;
			base[3][3] = 1;
			bases[i] = base.exp(k);
		} else if (op.op == 3) { //Rotation operation around x
			M base;
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					base[j][k] = 0;

			base[0][0] = 1.0;
			base[1][1] = +cos(op.ang);   //cos(theta)
			base[1][2] = -sin(op.ang);   //sin(theta)
			base[2][2] = +cos(op.ang);   //cos(theta)
			base[2][1] = +sin(op.ang);   //sin(theta)
			base[3][3] = 1.0;
			bases[i] = base.exp(k);
		}
	}
	for (int i = 1; i < m; ++i) {
		bases[i] = bases[i-1] * bases[i];
	}
	M ans = bases[m-1];
	int _x = x, _y = y, _z = z;
	x = _x * ans[0][0] + _y * ans[1][0] + _z * ans[2][0] + 1 * ans[3][0];
	y = _x * ans[0][1] + _y * ans[1][1] + _z * ans[2][1] + 1 * ans[3][1];
	z = _x * ans[0][2] + _y * ans[1][2] + _z * ans[2][2] + 1 * ans[3][2];
}
