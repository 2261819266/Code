#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem AT_abc034_d

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

struct Water {
    double a, b;
    Water operator()(int w, int p) {
        a = w, b = 0.01 * w * p;
        return *this;
    }

    Water operator+(const Water &T) const {
        return {a + T.a, b + T.b};
    }

    operator double() const {
        if (a == 0) return 0;
        return b / a;
    }

    bool operator<(const Water &T) const { return (double)(*this) < (double)(T); }
    bool operator>(const Water &T) const { return (double)(*this) > (double)(T); }

    Water operator+=(const Water &T) { return *this = *this + T; }
};

void main() {
    int n, k;
    cin >> n >> k;
    vector<Water> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int w, p;
        cin >> w >> p;
        a[i](w, p);
    }
    sort(a.begin() + 1, a.end(), [](const Water &p, const Water &q) { return p < q; });
    vector<vector<Water>> f(n + 1, vector<Water>(k + 1, {0, 0}));
    f[1][1] = a[1];
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i && j <= k; j++) {
            f[i][j] = max({f[i - 1][j], f[i - 1][j - 1] + a[i]});
        }
    }
    cout << f[n][k] * 100;
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}