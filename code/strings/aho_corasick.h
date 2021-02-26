#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second

typedef pair<int, int> ii;

const int K = 26;
inline int getId(char c) {
	return c-'a';
}
namespace Aho {
	struct Vertex {
		int next[K], go[K];
		int suff_link = -1, end_link = -1;
		int leaf = -1, p = -1, sz, match = -1;
		char pch;
		Vertex(int p1 = -1, char ch = '$', int sz1 = 0) : p(p1), pch(ch), sz(sz1) {
			fill(begin(next), end(next), -1);
			fill(begin(go), end(go), -1);
		}
	};
	vector<Vertex> trie;
	inline void init() {
		trie.clear();
		trie.emplace_back();
	}
	int add_string(const string &s, int id = 1) {
		int v = 0;
		for (char ch : s) {
			int c = getId(ch);
			if (trie[v].next[c] == -1) {
				trie[v].next[c] = trie.size();
				trie.emplace_back(v, ch, trie[v].sz + 1);
			}
			v = trie[v].next[c];
		}
		trie[v].leaf = id;
		return v;
	}
	int go(int v, char ch);
	int get_suff_link(int v) {
		if (trie[v].suff_link == -1) {
			if (v == 0 or trie[v].p == 0) {
				trie[v].suff_link = 0;
			} else {
				trie[v].suff_link = go(get_suff_link(trie[v].p), trie[v].pch);
			}
		}
		return trie[v].suff_link;
	}
	int get_end_link(int v) {
		if (trie[v].end_link == -1) {
			if (v == 0 or trie[v].p == 0) {
				trie[v].end_link = 0;
			} else {
				int suff_link = get_suff_link(v);
				if (trie[suff_link].leaf != -1) {
					trie[v].end_link = suff_link;
				} else {
					trie[v].end_link = get_end_link(suff_link);
				}
			}
		}
		return trie[v].end_link;
	}
	int go(int v, char ch) {
		int c = getId(ch);
		if (trie[v].go[c] == -1) {
			if (trie[v].next[c] != -1) {
				trie[v].go[c] = trie[v].next[c];
			} else {
				trie[v].go[c] = (v == 0 ? 0 : go(get_suff_link(v), ch));
			}
		}
		return trie[v].go[c];
	}
};

/*
	Get match positions in O(|t| * sqrt(|t|))
	Answer: {i, j} -> Range of match
*/
vector<ii> getMatch(const string &t) {
	auto addMatch = [](vector<ii> &ans, int v, int i) {
		while (v != 0) {
			ans.emplace_back(i - Aho::trie[v].sz + 1, i);
			v = Aho::get_end_link(v);
		}
	};
	int v = 0;
	vector<ii> ans;
	for (int i = 0; i < (int)t.size(); ++i) {
		v = Aho::go(v, t[i]);
		if (Aho::trie[v].leaf != -1) {
			addMatch(ans, v, i);
		} else {
			addMatch(ans, Aho::get_end_link(v), i);
		}
	}
	sort(ans.begin(), ans.end());
	return ans;
}

int countMatch(int v) {
	if (Aho::trie[v].match == -1) {
		if (v == 0 or Aho::trie[v].p == 0) {
			Aho::trie[v].match = (Aho::trie[v].leaf != -1 ? 1 : 0);
		} else {
			Aho::trie[v].match = (Aho::trie[v].leaf != -1 ? 1 : 0) + 
								 countMatch(Aho::get_end_link(v));
		}
	}
	return Aho::trie[v].match;
}

/*
	Get match amount in O(|t|)
	Answer: Amount of matches
*/
int64_t matchAmount(const string &t) {
	int v = 0;
	int64_t ans = 0;
	for (char ch : t) {
		v = Aho::go(v, ch);
		ans += countMatch(v);
	}
	return ans;
}