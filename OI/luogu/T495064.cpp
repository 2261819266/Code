#include <algorithm>
#include <bits/stdc++.h>
#include <unordered_map>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem T495064

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

unordered_map<int, int> mp;

void main() {
#define ceil(x, y) ((x) / (y) + (bool)((x) % (y))) 
    int n, k;
    cin >> n >> k;
    vector<int> a(n), ans(n), b, c;
    cin >> a;
    b = a;
    sort(a.begin(), a.end());
    c.push_back(a[0]);
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) c.push_back(a[i]);
    }
    a = c;
    int t = a.back();
    int m = a.size();
    for (int i = m - 2; i >= 0; i--) {
        for (int j = m - 1; j > i; j--) {
            ans[i] = max(ans[i], (m - 1 - j) + ceil((k + 1) * (j - i) - (a[j] - a[i]), k));
        }
        // int y = ((k + 1) * (m - 1 - i) - (t - a[i]));
        // ans[i] = y / k + (bool)(y % k);
        // if (ans[i] <= ans[i + 1]) ans[i] = ans[i + 1] + 1;
    }
    ans[n - 1] = 0;
    for (int i = 0; i < n; i++) {
        cout << ans[lower_bound(a.begin(), a.end(), b[i]) - a.begin()] << spc;
    }
}
}

signed main() {
    Problem::main();
    return 0;
}