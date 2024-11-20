#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem P3372
#define fop fo(P3372)

using namespace std;

namespace Problem {
template <typename t>
ostream &operator<<(ostream &out, const vector<t> &A) {
	for (const t &i : A) out << i << spc;
	return out;
}

template <typename t>
void print(const t &x, int l = 0, int r = 0) {
	cout << x << spc;
}

template <typename t>
void print(const vector<t> &A, int l = 0, int r = 0) {
	for (int i = l; i < r; i++) {
	print(A[i], l, r);
	}
	cout << endl;
}

template <typename t>
istream &operator>>(istream &in, vector<t> &A) {
	for (t &i : A) in >> i;
	return in;
}

template<typename t>
void scan(t &x, int l = 0, int r = 0) {
	cin >> x;
}

template<typename t>
void scan(vector<t> &A, int l = 0, int r = 0) {
	for (int i = l; i < r; i++) {
	scan(A[i], l, r);
	}
}

template<typename it>
void assign(vector<int> &a, it p) {
	a.assign(*p, 0);
}

template<typename T, typename it>
void assign(vector<T> &a, it p) {
	T t;
	assign(t, p + 1);
	a.assign(*p, t);
}

template<typename T>
void assign(vector<T> &a, const vector<int> &p) {
	assign(a, p.begin());
}

using PII = pair<int, int>;

istream &operator>>(istream &in, PII &a) {
	return in >> a.first >> a.second;
}

ostream &operator<<(ostream &out, const PII &a) {
	return out << a.first << spc << a.second << spc;
}

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
#define pushdown do { a[ls] += b[k] * lm, a[rs] += b[k] * rm; b[ls] += b[k], b[rs] += b[k]; b[k] = 0; } while (0);
	
	int n;
	vector<int> a, b;

	SegTree(int N) : n(N), a(N << 2, 0), b(N << 2, 0) {}

	int build(int k, int l, int r, const vector<int> &A) {
		if (l == r) return a[k] = A[l];
		build(Ls, A), build(Rs, A);
		update;
	}

	int add(int k, int l, int r, int L, int R, int x) {
		if (l > R || L > r) return 0;
		if (l >= L && r <= R) return a[k] += x * num, b[k] += x;
		pushdown
		add(Ls, L, R, x), add(Rs, L, R, x);
		update
	}

	int query(int k, int l, int r, int L, int R) {
		if (l > R || L > r) return 0;
		if (l >= L && r <= R) return a[k];
		pushdown
		return query(Ls, L, R) + query(Rs, L, R);
	}
};

void main() {
	int n, m;
	cin >> n >> m;
	SegTree a(n);
	vector<int> A(n + 1);
	for (int i = 1; i <= n; i++) cin >> A[i];
	a.build(1, 1, n, A);
	while (m--) {
		int k, l, r, x;
		cin >> k >> l >> r;
		if (k == 1) cin >> x, a.add(1, 1, n, l, r, x);
		else cout << a.query(1, 1, n, l, r) << endl;
	}
}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	Problem::main();
	return 0;
}