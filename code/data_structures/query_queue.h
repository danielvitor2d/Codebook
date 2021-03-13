#include <stack>
template<class T>
class QueryQueue {
	std::stack<std::pair<T, T>> s1, s2;
	inline T cmp(T a, T b) {
		return std::min(a, b);
	}
	void normalize() {
		if (s2.empty()) {
			while (!s1.empty()) {
				T e = s1.top().first; s1.pop();
				T new_e = s2.empty() ? e : cmp(e, s2.top().second);
				s2.push({e, new_e});
			}
		}
	}
public:
	inline void push(T e) {
		T new_e = s1.empty() ? e : cmp(e, s1.top().second);
		s1.push({e, new_e});
	}
	inline T front() {
		normalize();
		return s2.top().first;
	}
	inline T query() {
		if (s1.empty() or s2.empty())
			return (s1.empty() ? s2.top().second : s1.top().second);
		else
			return cmp(s1.top().second, s2.top().second);
	}
	T pop() {
		T e = front();
		s2.pop();
		return e;
	}
	inline int size() {
		return s1.size()+s2.size();
	}
};