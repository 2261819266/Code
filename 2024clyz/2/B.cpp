#include <iostream>
#include <vector>
#include <algorithm>
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

using std::cin;
using std::cout;
using std::sort;
using std::vector;

const int M = 1e9 + 7;

int main() {
#ifndef LOCAL
    fo(divide)
#endif
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 2);
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(n + 2 , vector<int>(m + 1000, 0)));
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end() - 1);
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        auto &f = dp[i % 2], &g = dp[(i + 1) % 2];
        for (int j = 0; j < i; j++) {
            for (int k = 0; k <= m; k++) {
                int d = k + a[i + 1] - a[i];
                (f[j][d] += g[j][k] * (j + 1)) %= M;
                if (j != n) (f[j + 1][d] += g[j][k]) %= M;
                if (j) (f[j - 1][d] += g[j][k] * j) %= M;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        (ans += dp[n % 2][0][i]) %= M;
    }
    cout << ans << "\n";
}