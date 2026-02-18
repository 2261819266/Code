#include <bits/stdc++.h>
#include <vector>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem T472989
#define fop fo(T472989)

using namespace std;

namespace Problem {
using PII = pair<int, int>;

istream &operator>>(istream &in, PII &a) {
    return in >> a.first >> a.second;
}

ostream &operator<<(ostream &out, const PII &a) {
    return out << a.first << spc << a.second << spc;
}

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


int gcd(int x, int y) { return __gcd(x, y); }

void print(const vector<PII> &a, int k, int ans) {
    if (ans < k) cout << "No\n";
    else {
        cout << "Yes\n";
        for (PII p : a) {
            if (p.first % ans) cout << (p.first / ans + 1) * ans << spc;
            else cout << p.first << spc;
        }
        cout << endl;
    }
}

struct Data {
    int l, r, i;
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<Data> a(n);
    int up = 1e9;
    for (int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r;
        a[i].i = i;
        if (a[i].r < up) up = a[i].r;
    }
    sort(a.begin(), a.end(), [](const Data &p, const Data &q) { return p.r - p.l < q.r - q.l; });
    for (int i = k; i <= up; i++) {
        int K = true;
        for (const Data &j : a) {
            int l = j.l, r = j.r;
            int L = l % i ? l / i * i + i : l;
            if (L > r) {
                K = false;
                break;
            }
        }
        if (K) {
            vector<int> ans(n);
            for (const Data &j : a) {
                int l = j.l;
                int L = l % i ? l / i * i + i : l;
                ans[j.i] = L;
            }
            cout << "Yes\n" << ans << endl;
            return;
        }
    }
    cout << "No\n";
}

void main() {
    srand(time(0));
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