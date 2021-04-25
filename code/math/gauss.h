#include <iostream>
#include <algorithm>
#include "matrix.h"
typedef long double ld;
const ld EPS = 1e-9;
const int INF = 0x3f3f3f3f;

// Gaussian elimination with partial pivot (avoids propagation of rounding errors)
int gaussianElimination(Matrix<ld> a, Matrix<ld> &ans) {
	int n = (int)a.mat.size();
	int m = (int)a.mat[0].size()-1;
	std::vector<int> end(m, -1);

	for (int col = 0, row = 0; col < m and row < n; ++col) {
		int l = row;

		// Which row has largest column value
		for (int i = row; i < n; ++i)
			if (std::abs(a.mat[i][col]) > std::abs(a.mat[l][col]))
				l = i;
		if (std::abs(a.mat[l][col]) < EPS)
			continue;
		for (int i = col; i <= m; ++i)
			std::swap(a.mat[row][i], a.mat[l][i]);
		end[col] = row;

		// Elimination phase
		for (int i = 0; i < n; ++i) if (i != row) {
			ld c = a.mat[i][col] / a.mat[row][col];
			for (int j = m; j >= col; --j) {
				a.mat[i][j] -= a.mat[row][j] * c;
			}
		}
		++row;
	}

	// Substitution phase
	for (int i = 0; i < m; ++i)
		if (end[i] != -1)
			ans.mat[i][0] = a.mat[end[i]][m]/a.mat[end[i]][i];

	for (int i = 0; i < n; ++i) {
		ld sum = 0;
		for (int j = 0; j < m; ++j)
			sum += ans.mat[j][0] * a.mat[i][j];
		if (std::abs(sum - a.mat[i][m]) > EPS)
			return 0; // No solution
	}

	for (int i = 0; i < m; ++i)
		if (end[i] == -1)
			return INF; // Infinite solutions

	return 1; // One solution
}