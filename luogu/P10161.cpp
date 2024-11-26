#include <algorithm>
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem P7914
#define fop fo(P7914)

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

int f(int x) { return x * (x + 1) / 2; }

template<typename f_type, typename value_type>
value_type lower_bound(f_type F, value_type x) {
    value_type l, r;
    while (l < r - 1) {
        int mid = ((l + r) >> 1);
        if (F(mid) > x) r = mid;
        else l = mid;
    }
    return l;
}

string solve(int n, int k) {
    if (n % 2) return solve(n - 1, k);
    int y = lower_bound(f, k) - 1;
    if (f(y + 1) <= k) y++;

}

void solve() {
    int n, k;
    cin >> n >> k;
    int m = n / 2;
    int mx = m * (m + 1) / 2;
    if (k > mx || (k > f(m - 1) && k != f(m - 1) + 1 && k != f(m))) {
        cout << -1 << endl;
        return ;
    }
    // cout << solve(n, k) << endl;
    return ;
}

void main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}