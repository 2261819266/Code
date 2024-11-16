#include <algorithm>
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem learn
#define fop fo(learn)

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

int f(int x) {
	return 2 * x * x - 2 * x + 1;
}

const int maxn = 2e9 + 5;

template<typename P = int, typename Q = int>
P lower_bound(Q (*F)(P), Q X, P l = 0, P r = maxn, P e = 1) {
	while (r - l > e) {
		P mid = (l + r) / 2;
		Q M = F(mid);
		if (M <= X) l = mid;
		else r = mid;
	}
	return l;
}

PII solve(int x) {
	int layer = lower_bound(f, x);
	int s = x - f(layer);
	if (s == 0) return {layer, 0};
	if (s < 2 * layer) {
		int k = s % 2 ? 1 : -1;
		int t = (s + 1) / 2;
		return {layer - t, t * k};
	}
	int t = s % layer + 1;
	if (s < 3 * layer) {
		return {- t, layer - t};
	}
	return {t - layer, -t};
}

int solve(const PII &p) {
	if (p == (PII){0, 0}) return 0;
	int x = p.first, y = p.second;
	int layer = abs(x) + abs(y);
	if (x == layer && !y) return f(layer);
	if (x == 0 && y == -layer) return f(layer + 1) - 1;
	if (x >= 0) {
		return f(layer) + abs(y) * 2 + (y < 0) - 1;
	}
	if (y >= 0) {
		return f(layer) - 1 + 2 * layer - x;
	}
	return f(layer + 1) - 1 + x;
}

void main() {
	int n, m;
	cin >> n >> m;
	while (n--) {
		PII x;
		cin >> x;
		cout << solve(x) << endl;
	}
	while (m--) {
		int x;
		cin >> x;
		cout << solve(x) << endl;
	}
	// for (int i = 3; i >= -3; i--) {
	// 	for (int j = -3; j <= 3; j++) {
	// 		cout << solve({i, j}) << "\t";
	// 	}
	// 	cout << endl;
	// }
}
}

signed main() {
#ifndef LOCAL
	fop
#endif
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	Problem::main();
	return 0;
}