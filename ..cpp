#include <bits/stdc++.h>
#define Problem problem

using namespace std;

namespace Problem {
#define int long long
#define endl "\n"
#define space " "

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define updata return a[k] = a[ls] + a[rs];
#define num (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)
#define push_down do {\
	a[ls] += b[k] * lm;\
	a[rs] += b[k] * rm;\
	b[ls] += b[k];\
	b[rs] += b[k];\
	b[k] = 0;\
} while(0);
#define OUT if (l > R || L > r) return 0;
#define CHECK if (l >= L && r <= R)

	vector<int> a, b;
	int n;
	SegTree(int N) : n(N) {
		a.assign(n << 2, 0);
		b.assign(n << 2, 0);
	}

	int modify(int k, int l, int r, int i, int x) {
		if (l == r) return a[k] = x;
		i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
		updata
	}

	int add(int k, int l, int r, int L, int R, int x) {
		OUT
		CHECK return a[k] += x * num, b[k] += x;
		push_down
		add(Ls, L, R, x); add(Rs, L, R, x);
		updata
	}

	int query(int k, int l, int r, int L, int R) {
		OUT
		CHECK return a[k];
		push_down
		return query(Ls, L, R) + query(Rs, L, R);
	}
};

void main() {
	int n, m;
	cin >> n >> m;
	vector<int> A(n + 1);
	SegTree a(n);
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
		a.modify(1, 1, n, i, A[i]);
	}
	while (m--) {
		int k, x, y, z;
		cin >> k >> x >> y;
		if (k == 1) {
			cin >> z;
			a.add(1, 1, n, x, y, z);
		} else {
			cout << a.query(1, 1, n, x, y) << endl;
		}
	}
}
}

signed main() {
	Problem::main();
	return 0;
}