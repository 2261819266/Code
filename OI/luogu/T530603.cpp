#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem T530603

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

void main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1, 0);
    vector<int> b(n + 1, 0);
    scan(a, 1, n + 1);
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] + b[i - 1];
    }
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        if (k > r - l) {
            cout << -1 << endl;
            continue;
        }
        int s = b[r] - b[l - 1];
        if (k == r - l && s == r - l + 1) {
            cout << 0 << endl;
            continue;
        }
        cout << abs(k - s) << endl;
    }
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Problem::main();
    return 0;
}