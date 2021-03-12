#include <vector>
int mergeSort(std::vector<int> &a) {
	int n = a.size();
	if (n <= 1) return 0;
	int mid = n/2;
	std::vector<int> b, c;
	for (int i = 0; i < mid; ++i)
		b.push_back(a[i]);
	for (int i = mid; i < n; ++i)
		c.push_back(a[i]);
	int inv = 0;
	inv += mergeSort(b);
	inv += mergeSort(c);
	int i = 0, j = 0;
	for (int k = 0; k < n; ++k) {
		if (i == mid) {
			a[k] = c[j++];
		} else if (j == n-mid) {
			a[k] = b[i++];
		} else if (b[i] <= c[j]) {
			a[k] = b[i++];
		} else {
			a[k] = c[j++];
			inv += mid-i;
		}
	}
	return inv;
}