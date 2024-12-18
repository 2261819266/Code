#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem T436524
#define fop fo(T436524)

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

const int M = 998244353;

int f(int x) {
    vector<int> f(x + 1, 0);
    f[1] = f[0] = 1;
    for (int i = 2; i <= x; i++) {
        f[i] = f[i - 1] + (i - 1) * f[i - 2];
        f[i] %= M;
    }
    return f.back();
}

void main() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i]) b[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] && b[i] && a[i] != b[i]) {
            cout << 0 << endl;
            return ;
        }
        if (a[i]) b[i] = a[i];
        if (b[i]) a[i] = b[i];
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!a[i]) cnt++;
    }
    int ans = 1;
    cout << f(cnt) << endl;
    // for (int i = 1; i <= n; i++) {
    //     cout << f(i) << endl;
    // }
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}