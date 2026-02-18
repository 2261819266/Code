#include <bits/stdc++.h>
#include <vector>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem T532927
#define fop fo(T532927)

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

template<typename T> vector<T> operator+(const vector<T> &A, const vector<T> &B) {
    int n = A.size(), m = B.size(), k = max(m, n);
    vector<T> C(k, 0);
    for (int i = 0; i < k; i++) {
        if (i < n) C[i] += A[i];
        if (i < m) C[i] += B[i];
    }
    return C;
}

template<typename T> vector<T> operator+=(vector<T> &A, const vector<T> &B) { return A = A + B; }

int sqr(int x) { return x * x; }

int solve(int n, vector<int> &a) {
	int t = 1;
	while (t++) {
        int tt = t * t;
        if (tt > n) break;
		for (int i = 0; i + tt < n; i++) {
			unordered_map<int, int> mp;
			for (int j = 0; j < tt; j++) {
				mp[a[i + j]]++;
			}
			if ((int)mp.size() <= t) {
				int k = n;
				for (int j = i + tt; j < n; j++) {
					mp[a[j]]++;
					if ((int)mp.size() > t) {
						k = j;
						break;
					}
				}
                vector<int> b;
                for (int j = 0; j < i; j++) b.push_back(a[j]);
                for (int j = k; j < n; j++) b.push_back(a[j]);
                return solve(b.size(), b) + sqr(mp.size() - ((int)(mp.size() > t)));
			}
		}
	}
    return n;
}
void main() { 
	int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    if (n > 1e5) cout << n;
	else cout << solve(n, a);
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}