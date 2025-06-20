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
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<int> nxt(m);
    for (int i = 1, j = 0; i < m; i++) {
        while (t[i] != t[j] && j > 0) j = nxt[j - 1];
        if (t[i] == t[j]) {
            j++;
        }
        nxt[i] = j;
    }

    for (int i = 0, j = 0; i < n; i++) {
        while (s[i] != t[j] && j > 0) 
            j = nxt[j - 1];
        if (s[i] == t[j]) {
            j++;
        }
        if (j == m) cout << i - j + 2 << endl, j = nxt[j - 1];
    }

    for (int i : nxt) cout << i << " ";
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