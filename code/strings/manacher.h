#include <vector>
#include <string>
struct Palindrome {
	std::vector<int> d1, d2;
	int N;
	void manacher(const std::string &s) {
		int l, r = -1;
		N = s.size();
		d1.resize(N), d2.resize(N);
		for (int i = 0; i < N; ++i) {
			int k = i > r ? 1 : std::min(d1[l+(r-i)], r-i+1);
			while (k <= i and i + k < N and s[i-k] == s[i+k])
				++k;
			d1[i] = k--;
			if (i+k>r) l = i-k, r=i+k;
		}
		l = 0, r = -1;
		for (int i = 0; i < N; ++i) {
			int k = i > r ? 0 : std::min(d2[l+(r-i)+1], r-i+1);
			while (k+1 <= i and i + k < N and s[i-k-1] == s[i+k])
				++k;
			d2[i] = k--;
			if (i+k>r) l = i-k-1, r=i+k;
		}
	}
	Palindrome (const std::string &s) {
		manacher(s);
	}
	bool isPalindrome(int i, int j) {
		int sz = j-i+1;
		return (sz & 1 ? d1[i+sz/2] >= sz : d2[i+sz/2+1] >= sz);
	}
};