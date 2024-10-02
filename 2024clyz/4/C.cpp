#include <iostream>
#include <vector>
#define int long long
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

using std::cin;
using std::cout;
using std::vector;
const int M = 998244353;

vector<int> a;

signed main() {
#ifndef LOCAL
    fo(rsrs)
#endif
    int n, m;
    cin >> n >> m;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while (m--) {
        int k, l, r;
        cin >> k >> l >> r;
        if (k == 1) {
            for (int i = l; i <= r; i++) {
                (a[i] *= a[i]) %= M;
            }
        } else {
            int ans = 0;
            for (int i = l; i <= r; i++) {
                (ans += a[i]) %= M;
            }
            cout << ans << "\n";
        }
    }
}