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

int check(int n, string s[2]) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += s[0][i] == s[1][i];
    }
    return ans;
}

int solve() {
    int n;
    cin >> n;
    string s[2], t[2];
    cin >> s[0] >> s[1] >> t[0] >> t[1];
    for (int i = 0, k[2] = {}; i < n; i++) {
        if (t[0][i] == '0') k[0] = i + 1;
        if (t[1][i] == '0') k[1] = i + 1;
        // if (s[0][i] == s[1][i]) continue;
        for (int j = 0; j < 2; j++) {
            if (t[j][i] == '0') continue;
            while (s[0][k[j]] == s[1][k[j]] && k[j] <= i) k[j]++;
            if (s[0][k[j]] != s[1][k[j]]) swap(s[j][i], s[j][k[j]]);
        }
    }
    return check(n, s);
}

signed main() {
    cin.tie()->sync_with_stdio(0);
    init();

    int T = 1;
    cin >> T;
    while (T--) {
        cout << solve() << endl;
    }
    return 0;
}