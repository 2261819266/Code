#include <bits/stdc++.h>
#include <vector>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem dawn
#define fop fo(dawn)

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

template<typename T> vector<T> operator^=(vector<T> &A, const vector<T> &B);

template<typename T> vector<T> operator^(const vector<T> &A, const vector<T> &B) {
    int n = A.size(), m = B.size(), k = max(m, n);
    vector<T> C(k);
    for (int i = 0; i < k; i++) {
        if (i < n) C[i] ^= A[i];
        if (i < m) C[i] ^= B[i];
    }
    return C;
}
template<typename T> vector<T> operator^=(vector<T> &A, const vector<T> &B) { return A = A ^ B; }


template<typename T> vector<T> operator+=(vector<T> &A, const vector<T> &B) { return A = A + B; }
int n, m;
vector<vector<int>> a, v, f;

PII next(int i, int j) { return {i + (j == m), j % m + 1}; }
PII last(int i, int j) { return {i - (j == 1), j - 1 + m * (j == 1)}; }

void getnext() {
    if (!v[n][m]) v[n][m] = 1;
    else {
        PII p = {n, m};
        v[n][m] = 0;
        while ((p = last(p.first, p.second)).first && v[p.first][p.second]) {
            v[p.first][p.second] = 0;
        }
        v[p.first][p.second] = 1;
    }
};

int sum(const vector<vector<int>> &A) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans += A[i][j];
        }
    }
    return ans;
}

int getcol(const vector<vector<int>> &A) {
    int ans = m;
    for (int j = 1; j <= m; j++) {
        for (int i = 1, k = n; i < k; i++, k--) {
            if (A[i][j] != A[k][j]) {
                ans--;
                break;
            }
        }
    }
    return ans;
}

int getrow(const vector<vector<int>> &A) {
    int ans = n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1, k = m; j < k; j++, k--) {
            if (A[i][j] != A[i][k]) {
                ans--;
                break;
            }
        }
    }
    return ans;
}

void solve() {
    v.assign(n + 1, vector<int>(m + 1));
    f.assign(n + 1, vector<int>(m + 1, n * m + 100));
    size_t maxn = 1ull << (n * m);
    for (size_t T = 0; T < maxn; T++) {
        vector<vector<int>> x = v ^ a;
        int c = getcol(x), r = getrow(x), s = sum(v);
        for (int i = 0; i <= r; i++) {
            for (int j = 0; j <= c; j++) {
                f[i][j] = min(f[i][j], s);
            }
        }
        getnext();
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            cout << f[i][j] << spc;
        }
        cout << endl;
    }
}

void main() {
    cin >> n >> m;
    a.assign(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            a[i][j] = c - '0';
        }
    }
    if (n == 1) {
        int ans = 0;
        for (int i = 1, j = m; i < j; i++, j--) {
            if (a[1][i] != a[1][j]) ans++;
        }
        for (int i = 0; i <= m; i++) {
            cout << 0 << spc;
        }
        cout << endl;
        for (int i = 0; i <= m; i++) {
            cout << ans << spc;
        }
        cout << endl;
    } else {
        solve();
    }
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