#include <bits/stdc++.h>
using namespace std;
const int K = 26;
inline int getId(char c) {
	return c-'a'; 
}
namespace Trie {
	struct Vertex {
		int next[K];
		int leaf, count;
		Vertex () {
			fill(begin(next), end(next), -1);
			leaf = count = 0;
		}
	};
	vector<Vertex> trie;
	void init() {
		trie.clear();
		trie.emplace_back();
	}
	/*
		Insert a string in O(|s|)
	*/
	void add(const string &s) {
		int v = 0;
		++trie[v].count;
		for (char ch : s) {
			int c = getId(ch);
			if (trie[v].next[c] == -1) {
				trie[v].next[c] = trie.size();
				trie.emplace_back();
			}
			v = trie[v].next[c];
			++trie[v].count;
		}
		++trie[v].leaf;
	}
	/*
		Get amount of occurrences of s in O(|s|)
	*/
	int countStr(const string &s) {
		int v = 0;
		for (char ch : s) {
			int c = getId(ch);
			if (trie[v].next[c] == -1) return 0;
			v = trie[v].next[c]; 
		}
		return trie[v].leaf;
	}
	/*
		Get amount of occurrences of prefix s in O(|s|)
	*/
	int countPre(const string &s) {
		int v = 0;
		for (char ch : s) {
			int c = getId(ch);
			if (trie[v].next[c] == -1) return 0;
			v = trie[v].next[c];
		}
		return trie[v].count;
	}
	/*
		Remove a string s in O(|s|) and returns true if it's removed
	*/
	bool remove(const string &s) {
		vector<int> rm;
		int v = 0;
		rm.push_back(v);
		for (char ch : s) {
			int c = getId(ch);
			if (trie[v].next[c] == -1) return false;
			v = trie[v].next[c];
			rm.push_back(v); 
		}
		if (trie[v].leaf > 0) {
			--trie[v].leaf;
			for (int x : rm) --trie[x].count;
			return true;
		}
		return false;
	}
};