#include <stack>
template<class T>
class QueryStack {
	std::stack<std::pair<T, T>> st;
	inline T cmp(T a, T b) {
		return std::min(a, b);
	}
public:
	inline void push(T e) {
		T new_e = st.empty() ? e : cmp(e, st.top().second);
		st.push({e, new_e});
	}
	inline T top() {
		return st.top().first;
	}
	inline T query() {
			return st.top().second;
	}
	inline T pop() {
		T e = top();
		st.pop();
		return e;
	}
	inline int size() {
		return st.size();
	}
};