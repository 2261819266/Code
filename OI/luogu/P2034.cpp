#include <bits/stdc++.h>
#include <vector>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem P2034
#define fop fo(P2034)

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

void main() {
    const int inf = 0x3fffffffffffffff;
    int n, k, sum = 0;
    cin >> n >> k;
    vector<int> a(n + 2, 0), f(n + 2, inf);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    f[0] = 0;
    deque<PII> q;
    q.push_back({0, 0});
    for (int i = 1; i <= n + 1; i++) {
        while (!q.empty() && i - k - 1 >= 0 && i - k - 1 > q.front().first) q.pop_front(); 
        f[i] = q.front().second + a[i];
        while (!q.empty() && q.back().second > f[i] && i <= n) q.pop_back();
        q.push_back({i, f[i]});
        // for (int j = 1; j <= k + 1 && i - j >= 0; j++) {
        //     f[i] = min(f[i], f[i - j] + a[i]);

        // }
    }
    cout << sum - f[n + 1] << endl;
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}