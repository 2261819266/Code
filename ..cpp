#include <bits/stdc++.h>
#include <vector>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem problem
#define fop fo(problem)

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

int M;

struct Matrix {
    vector<vector<int>> a;

    Matrix() : a({{1, 1}, {1, 0}}) {}

    Matrix operator*(const Matrix &b) const {
        Matrix x;
        int n = a.size();
        x.a.assign(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    (x.a[i][j] += a[i][k] * b.a[k][j]) %= M;
                }
            }
        }
        return x;
    }

} one, f;

Matrix pow(const Matrix &x, int n) {
    if (!n) return one;
    Matrix y = pow(x, n / 2);
    y = y * y;
    if (n % 2) y = y * x;
    return y;
}

// int X[] = {1, 1, 2, 4, 6}

int solve() {
    int n;
    one.a = {{1, 0}, {0, 1}};
    cin >> n >> M;
    if (n == 1) return 1;
    Matrix y = (pow(f, n));
    return ((int)(y.a[1][0] + y.a[1][1] * 2 - (n % 2 == 0)) + M) % M;
}

void main() {
    int T;
    cin >> T;
    while(T--) {
        cout << solve() << endl;
    }
}
}

signed main() {
    // fo(math)
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}