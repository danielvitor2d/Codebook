#include <numeric>
#include <vector>
#include <string>
typedef std::pair<int, int> ii;
class SuffixArray {
	std::vector<int> RA, SA, tempRA, tempSA, c;
	std::vector<int> LCP, Phi, PLCP;
	std::string S;
	int N;
	void countingSort(int k) {
		int sum = 0, maxi = std::max(256, N);
		c.assign(maxi, 0);
		for (int i = 0; i < N; ++i)
			c[RA[(i+k)%N]]++;
		for (int i = 1; i < maxi; ++i)
			c[i] += c[i-1];
		for (int i = N-1; i >= 0; --i)
			tempSA[--c[RA[(SA[i]+k)%N]]] = SA[i];
		SA = tempSA;
	}
	void constructSA() {
		iota(SA.begin(), SA.end(), 0);
		for (int i = 0; i < N; ++i) RA[i] = S[i];
		for (int k = 1; k < N; k <<= 1) {
			countingSort(k);
			countingSort(0);
			int r = 0;
			tempRA[SA[0]] = 0;
			for (int i = 1; i < N; ++i) {
				tempRA[SA[i]] = 
					(ii(RA[SA[i]], RA[(SA[i]+k)%N]) == ii(RA[SA[i-1]], RA[(SA[i-1]+k)%N]) ? r : ++r);
			}
			RA = tempRA;
			if (RA[SA[N-1]] == N-1) break;
		}
	}
	void constructLCP() {
		Phi[SA[0]] = -1;
		for (int i = 1; i < N; ++i) {
			Phi[SA[i]] = SA[i-1];
		}
		for (int i = 0, k = 0; i < N; ++i) {
			if (Phi[i] == -1) { PLCP[i] = 0; continue; }
			while (S[i+k] == S[Phi[i]+k]) ++k;
			PLCP[i] = k;
			k = std::max(k-1, 0);
		}
		for (int i = 0; i < N; ++i)
			LCP[i] = PLCP[SA[i]];
	}
	ii stringMatching(const std::string &s) {
		int m = s.size();
		int lo = 0, hi = N-2, mid;
		while (lo < hi) { /*Find the lower bound*/
			mid = lo+(hi-lo)/2;
			if (S.substr(SA[mid], m) >= s) hi = mid;
			else lo = mid + 1;
		}
		if (S.substr(SA[lo], m) != s) return {-1, -1};
		ii ans = {lo, lo};
		lo = 0, hi = N-2;
		while (lo < hi) { /*Find the upper bound*/
			mid = lo+(hi-lo)/2;
			if (S.substr(SA[mid], m) > s) hi = mid;
			else lo = mid + 1;
		}
		if (S.substr(SA[lo], m) != s) --hi;
		ans.second = hi;
		return ans;
	}
public:
	SuffixArray (const std::string &s) : S(s) {
		S += '$';
		N = S.size();
		RA.assign(N, 0);
		SA.assign(N, 0);
		tempSA.assign(N, 0);
		tempRA.assign(N, 0);
		LCP.assign(N, 0);
		PLCP.assign(N, 0);
		Phi.assign(N, 0);
		constructSA();
		constructLCP();
		SA.erase(SA.begin());
		LCP.erase(LCP.begin());
	}
	std::vector<int> getSA() {
		return SA;
	}
	std::vector<int> getLCP() {
		return LCP;
	}
	ii getStringMatching(const std::string &s) {
		return stringMatching(s);
	}
	/*
		Number of different substrings:
		(n^2+n)/2 - sum_{i=0 to n-2} lcp[i]
	*/
};