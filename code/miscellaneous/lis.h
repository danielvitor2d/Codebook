#include <vector>
int lis(std::vector<int> &aux) {
	std::vector<int> d;
	for (int &x : aux) {
		auto it = std::lower_bound(d.begin(), d.end(), x);
		if (it == d.end()) d.push_back(x);
		else *it = x;
	}
	return (int)d.size();
}