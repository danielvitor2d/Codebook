#include <vector>
#include <math.h>

template <class T>
struct SqrtDecomposition {
	int block_size;
	std::vector<T> a, b;
	template <class MyIterator>
	SqrtDecomposition(MyIterator ini, MyIterator end) {
		int n = end-ini;
		block_size = int(sqrt(n + .0) + 1);
		a.resize(n);
		b.resize(block_size + 5);
		for (int i = 0; i < n; ++i, ++ini) {
			a[i] = (*ini);
			b[i / block_size] += a[i];
		}
	}
	void update(int idx, T new_value) {
		T delta = new_value - a[idx];
		a[idx] += delta;
		b[idx / block_size] += delta;
	}
	T query(int l, int r) {
		T sum = 0;
		int c_l = l / block_size, c_r = r / block_size;
		if (c_l == c_r) {
			for (int i = l; i <= r; ++i)
				sum += a[i];
		} else {
			for (int i = l, aux = (c_l+1)*block_size; i < aux; ++i)
				sum += a[i];
			for (int i = c_l+1; i < c_r; ++i)
				sum += b[i];
			for (int i = c_r*block_size; i <= r; ++i)
				sum += a[i];
		}
		return sum;
	}
};
