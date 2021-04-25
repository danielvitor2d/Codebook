#include <vector>
#include <algorithm>

template<typename T>
struct Matrix {
	T MOD = 1e9+7;
	std::vector<std::vector<T>> mat;
	Matrix(int n, int m, bool id = false) {
		mat.resize(n, std::vector<T>(m, 0));
		if (id) for (int i = 0; i < n; ++i)
			mat[i][i] = 1;
	}
	Matrix(std::vector<std::vector<int>> oth) : mat(oth) {}
	Matrix<T> operator +(Matrix<T> oth) {
		int n = (int)mat.size();
		int m = (int)mat[0].size();
		Matrix<T> c(n, m, false);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)
				c[i][j] = mat[i][j]+oth.mat[i][j];
		}
		return c;
	}
	Matrix<T> operator*(Matrix<T> oth) {
		int n = (int)mat.size();
		int m = (int)mat[0].size();
		int p = (int)oth.mat[0].size();
		Matrix<T> c(n, p, false);
		std::vector<T> col(m);
		for (int j = 0; j < p; ++j) {
			for (int k = 0; k < m; ++k)
				col[k] = oth.mat[k][j];
			for (int i = 0; i < n; ++i) {
				T sum = 0;
				for (int k = 0; k < m; ++k)
					sum += mat[i][k] * col[k];
				c.mat[i][j] = sum;
			}
		}
		return c;
	}
	Matrix<T> operator*(T k) {
		int n = (int)mat.size();
		int m = (int)mat[0].size();
		Matrix<T> a(mat);
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
			a[i][j] *= k;
		return a;
	}
	Matrix<T> operator-(Matrix<T> oth) {
		Matrix<T> a = mat;
		return a + ((-1) * oth);
	}
	Matrix<T> operator^(T exp) {
		int n = (int)mat.size();
		Matrix<T> res(n, n, true), base(mat);
		while (exp > 0) {
			if (exp & 1) 
				res = res * base;
			base = base * base;
			exp >>= 1;
		}
		return res;
	}
};