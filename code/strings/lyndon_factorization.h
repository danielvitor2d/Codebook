#include <string>
#include <vector>
std::vector<std::string> duval(const std::string &s) {
	int n = s.size();
	std::vector<std::string> fac;
	for (int i = 0; i < n;) {
		int j = i + 1, k = i;
		while (j < n and s[k] <= s[j]) {
			if (s[k] < s[j])
				k = i;
			else
				++k;
			++j;
		}
		while (i <= k) {
			fac.push_back(s.substr(i, j-k));
			i += j-k;
		}
	}
	return fac;
}
std::string min_cyclic_string(std::string s) {
	s += s;
	int n = s.size();
	int ans = 0;
	for (int i = 0; i < n/2;) {
		ans = i;
		int j = i+1, k = i;
		while (s[k] <= s[j]) {
			if (s[k] < s[j])
				k = i;
			else
				++k;
			++j;
		}
		while (i <= k)
			i += j-k;
	}
	return s.substr(ans, n/2);
}