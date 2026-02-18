#include <bits/stdc++.h>
#define int long long
#define endl "\n"

using namespace std;

template<typename T>
void assign(int n, vector<T> &x) {
    x.assign(n, T());
}

template<typename T, typename ...Args>
void assign(int n, vector<T> &x, vector<Args> &...y) {
    assign(n, x);
    assign(n, y...);
}

inline void init() {
    return;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    int mn = 0x7fffffff, mx = 0;
    for (int &i : a) cin >> i, mx = max(mx, i), mn = min(mn, i), i = mn;
    vector<int> t(2e5 + 1, 0);
    for (int i = 0, j = n; i <= 2e5; i++) {
        while (i >= a[j - 1] && j) j--;
        t[i] = j;
        // cerr << t[i] << endl;
    }
    while (m--) {
        int x; 
        cin >> x;
        // int y = lower_bound(a.begin(), a.end(), x, [](int x, int y) { return x > y; }) - a.begin() + 1;
        int y = t[x] + 1;
        cout << (y > n ? -1 : y) << endl;
    }
}

signed main() {
    cin.tie()->sync_with_stdio(0);
    init();

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}