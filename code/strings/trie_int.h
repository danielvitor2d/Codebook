#include <bits/stdc++.h>
using namespace std;
const int K = 2;
const int SZ = 32;
namespace Trie {
	struct Vertex {
		int next[K];
		int val, pre;
		Vertex () {
			fill(begin(next), end(next), -1);
			pre = val = 0;
		}
	};
	vector<Vertex> trie;
	void build() {
		trie.clear();
		trie.emplace_back();
	}
	void add(int val) {
		int v = 0;
		++trie[v].pre;
		for (int i = SZ-1; i >= 0; --i) {
			bool b = val & (1 << i);
			if (trie[v].next[b] == -1) {
				trie[v].next[b] = trie.size();
				trie.emplace_back();
			}
			v = trie[v].next[b];
			++trie[v].pre;
		}
		trie[v].val = val;
	}
	int min_xor(int val) {
		int v = 0;
		for (int i = SZ-1; i >= 0; --i) {
			bool b = val & (1 << i);
			if (trie[v].next[b] != -1) {
				v = trie[v].next[b];
			} else {
				v = trie[v].next[b^1];
			}
		}
		return val ^ trie[v].val;
	}
	int max_xor(int val) {
		int v = 0;
		for (int i = SZ-1; i >= 0; --i) {
			bool b = val & (1 << i);
			if (trie[v].next[b^1] != -1) {
				v = trie[v].next[b^1];
			} else {
				v = trie[v].next[b];
			}
		}
		return val ^ trie[v].val;
	}
};
