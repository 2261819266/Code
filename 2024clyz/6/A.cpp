#include <algorithm>
#include <iostream>
#include <vector>
#define int long long
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

using std::cin;
using std::cout;
using std::vector;
using std::cerr;
using std::sort;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    sort(a.begin(), a.end());
    int ans = 0;
    for (int i = 0; i < n - k; i++) {
        ans += a[i];
    }
    if (a.back() > ans) ans = a.back();
    cout << ans << "\n";
}

signed main() {    
#ifndef LOCAL
    fo(coin)
#endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    cerr << clock();
}