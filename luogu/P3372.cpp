#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

template<typename t = long long>
struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update return a[k] = a[ls] + a[rs];
#define num (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)
	vector<t> a, b;
	int n;
	SegTree(const int N = 1) {
		assign(N);
	}

	void assign(const int N) {
		n = N;
		a.assign(n << 2, 0);
		b.assign(n << 2, 0);
	}

	t modify(int k, int l, int r, int i, t x) {
		if (l == r) return a[k] = x;
		i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
		update
	}

	void pushdown(int k, int l, int r) {
		b[ls] += b[k];
		b[rs] += b[k];
		a[ls] += b[k] * lm;
		a[rs] += b[k] * rm;
		b[k] = 0;
	}

	t add(int k, int l, int r, int L, int R, t x) {
		if (l > R || L > r) return 0;
		if (l >= L && r <= R) return a[k] += x * num, b[k] += x;
		pushdown(k, l, r);
		add(Ls, L, R, x);
		add(Rs, L, R, x);
		update;
	}

	t query(int k, int l, int r, int L, int R) {
		if (l > R || L > r) return 0;
		if (l >= L && r <= R) return a[k];
		pushdown(k, l, r);
		return query(Ls, L, R) + query(Rs, L, R);
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	SegTree<> a(n);
	using t = long long;
	for (int i = 1; i <= n; i++) {
		t x;
		cin >> x;
		a.modify(1, 1, n, i, x);
	}
	while (m--) {
		int k, l, r;
		t x;
		cin >> k >> l >> r;
		if (k == 1) {
			cin >> x;
			a.add(1, 1, n, l, r, x);
		} else {
			cout << a.query(1, 1, n, l, r) << "\n";
		}
	}
}