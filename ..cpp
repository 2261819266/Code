#include <bits/stdc++.h>
#define int long long
#define endl "\n"

using namespace std;

struct Array {
#define lowbit(x) ((x) & -(x))
	int n;
	vector<int> a;

	// Array(int N) : n(N), a(n + 1, 0) {}

	void build(const vector<int> &A) {
		n = A.size() - 1;
		a.assign(n + 1, 0);
		for (int i = 1; i <= n; i++) {
			a[i] += A[i];
			if (i + lowbit(i) <= n) a[i + lowbit(i)] += a[i];
		}
	}

	int query(int r) {
		int ans = 0;
		while (r) {
			ans += a[r];
			r -= lowbit(r);
		}
		return ans;
	}

	int query(int l, int r) { return query(r) - query(l - 1); }

	void add(int i, int x) {
		while (i <= n) {
			a[i] += x;
			i += lowbit(i);
		}
	}
} a;

struct Array2 {
	int n;
	Array a, b;
	void build(const vector<int> &_A) {
		n = _A.size() - 1;
		vector<int> A(n + 1), B(n + 1);
		for (int i = 1; i <= n; i++) {
			A[i] = _A[i] - _A[i - 1];
			B[i] = i * A[i];
		}
		a.build(A);
		b.build(B);
	}

	void add(int l, int r, int x) {
		a.add(l, long long x)
	}
};

signed main() {
	int n, m;
	cin >> n >> m;
	vector<int> A(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
	}
	a.build(A);
	while (m--) {
		int k, x, y;
		cin >> k >> x >> y;
		if (k == 1) a.add(x, y);
		else cout << a.query(x, y) << endl;
	}
}