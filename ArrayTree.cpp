#include <bits/stdc++.h>
#include <vector>
#define Problem TreeArray
#define int long long
#define endl "\n"
#define space " "

using namespace std;

namespace Problem {
#define max(x, y) (x < y ? y : x)
#define min(x, y) (x < y ? x : y)
	
struct ArrayTree {
#define lowbit(x) (x & (-x))
	vector<int> a;
	int n;
	ArrayTree(int N = 0) : n(N) {
		a.assign(n + 1, 0);
	}

	void assign(int N) {
		n = N;
		a.assign(n + 1, 0);
	}

	void clear() {
		a.clear();
		n = 0;
	}
	
	void build(const vector<int> &A) {
		n = A.size() - 1;
		a.resize(n + 1, 0);
		for (int i = 1; i <= n; i++) {
			a[i] += A[i];
			if (i + lowbit(i) <= n) a[i + lowbit(i)] += a[i];
		}
	}
	
	int query(int R) const {
		int ans = 0;
		while (R) {
			ans += a[R];
			R -= lowbit(R);
		}
		return ans;
	}

	int query(int L, int R) const {
		return query(R) - query(L - 1);
	}

	void add(int I, int X) {
		while (I <= n) {
			a[I] += X;
			I += lowbit(I);
		}
	}

	ArrayTree operator=(const vector<int> &A) {
		build(A);
		return *this;
	}
};

struct ArrayTree2 {
	ArrayTree a, b;
	int n;
	ArrayTree2(int N = 0) : n(N) {
		a.assign(N);
		b.assign(N);
	}

	void assign(int N) {
		n = N;
		a.assign(N);
		b.assign(N);
	}

	void build(const vector<int> &A) {
		assign(A.size() - 1);
		vector<int> _A(n + 1, 0), _B(n + 1, 0);
		for (int i = 1; i <= n; i++) {
			_A[i] = A[i] - A[i - 1];
			_B[i] = i * _A[i];
		}
		a = _A;
		b = _B;
	}

	void add(int L, int R, int X) {
		a.add(L, X);
		b.add(L, X * L);
		if (R == n) return;
		a.add(R + 1, -X);
		b.add(R + 1, -X * (R + 1));
	}

	int find(int X) {
		return a.query(X);
	}

	int query(int R) const {
		return (R + 1) * a.query(1, R) - b.query(1, R);
	}

	int query(int L, int R) {
		return query(R) - query(L - 1);
	}
};
	
// void main() {
// 	int n, m;
// 	cin >> n >> m;
// 	ArrayTree a(n);
// 	vector<int> A(n + 1);
// 	for (int i = 1; i <= n; i++) {
// 		cin >> A[i];
// 	}
// 	a.build(A);
// 	// for (int i = 1; i <= n; i++) {
// 	// 	cout << a.query(i, i) << space;
// 	// }
// 	while (m--) {
// 		int k, x, y;
// 		cin >> k >> x >> y;
// 		if (k == 1) {
// 			a.add(x, y);
// 		} else {
// 			cout << a.query(x, y) << endl;
// 		}
// 	}
// }

void main() {
	int n, m;
	cin >> n >> m;
	vector<int> A(n + 1);
	ArrayTree2 a;
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
	}
	a.build(A);
	while (m--) {
		int k, x, y, z;
		cin >> k >> x >> y;
		if (k == 1) {
			cin >> z;
			a.add(x, y, z);
		} else {
			cout << a.query(x, y) << endl;
		}
	}
}
}

signed main() {
	// freopen("in.in", "r", stdin);
	Problem::main();
	return 0;
}

