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

const int M = 998244353;

int solve() {

    int n, ans = 1;
    vector<int> a, b, f, c, d;
    cin >> n;
    assign(n + 1, a, b, f);
    f[0] = 0, f[1] = 1;
    for (int i = 2; i <= n; i++) f[i] = f[i - 1] * 3 % M;
    for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i] == (i & 1);
    if (!b[1] && !b[n]) return 0;
    int t = 0, s = 1;
    for (int i = 1, j; i <= n; i++) {
        if (i < n && b[i] == 0 && b[i + 1] == 0) return 0;
        if (!b[i]) t++, j = a[i];
        else {
            if ((i >= n - 1 || b[i + 1]) && t) {
                c.push_back(t);
                d.push_back(j);
                ans = ans * f[t] % M, t = 0;
            }
        }
    }
    for (int i = 0, t = 0; i < c.size(); i++) {
        if (i && d[i] == d[i - 1]) (ans *= 3) %= M;
        else t++;
    }
    // return f[t];
    // return 0;
    return ans * t * (t + 1);
}

signed main() {
    cin.tie()->sync_with_stdio(0);
    init();

    int T = 1;
    // cin >> T;
    while (T--) {
        cout << solve() << endl;
    }
    return 0;
}