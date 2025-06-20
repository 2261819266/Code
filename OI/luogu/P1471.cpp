#include <bits/stdc++.h>
#include <iomanip>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem P1471
#define fop fo(P1471)

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

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update return a[k] = a[ls] + a[rs], b[k] = b[ls] + b[rs];
#define num (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)
    int n;
    vector<double> a, b, c;
    SegTree(const vector<double> &A) : n(A.size() - 1), a(n << 2), b(n << 2), c(n << 2) { build(1, 1, n, A); }

    double sqr(double x) { return x * x;  } 

    double build(int k, int l, int r, const vector<double> &A) {
        if (l == r) return a[k] = A[l], b[k] = sqr(A[l]);
        build(Ls, A), build(Rs, A);
        update 
    }

    void pushdown(int k, int l, int r) {
        a[ls] += c[k] * lm;
        a[rs] += c[k] * rm;
        b[ls] += 2 * a[ls] * c[k] - lm * sqr(c[k]);
        b[rs] += 2 * a[rs] * c[k] - rm * sqr(c[k]);
        c[ls] += c[k];
        c[rs] += c[k];
        c[k] = 0;
    }

    double add(int k, int l, int r, int L, int R, double x) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k] += num * x, b[k] += 2 * a[k] * x - sqr(x) * num, c[k] += x;
        pushdown(k, l, r);
        add(Ls, L, R, x), add(Rs, L, R, x);
        update
    }

    double query(int k, int l, int r, int L, int R, int K) { // 0 sum 1 sqr sum
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return K ? b[k] : a[k];
        pushdown(k, l, r);
        return query(Ls, L, R, K) + query(Rs, L, R, K);
    }

    void print(int K) {
        for (int i = 1; i <= n; i++) {
            cout << query(1, 1, n, i, i, K) << spc;
        }
        cout << endl;
    }

    void print() {
        print(0), print(1);
        cout << endl;
    }
};

void main() {
    int n, m;
    cin >> n >> m;
    vector<double> A(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    SegTree a(A);
    while (m--) {
        // a.print();
        int k, l, r;
        double x;
        cin >> k >> l >> r;
        if (k == 1) cin >> x, a.add(1, 1, n, l, r, x);
        else if (k == 2) {
            cout << fixed << setprecision(4) << a.query(1, 1, n, l, r, 0) / num << endl;
        } else {
            cout << fixed << setprecision(4) << a.query(1, 1, n, l, r, 1) / num - a.sqr(a.query(1, 1, n, l, r, 0) / num) << endl;
        }
    }
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}