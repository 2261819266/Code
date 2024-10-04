#include <iostream>
#include <vector>
#include <cmath>
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define int long long

using std::cin;
using std::cout;
using std::vector;

int solve() {
    int n, k, m;
    cin >> n >> k;
    m = sqrt(k);
    if (m % 2) {
        return n % 2;
    } else return n;
}

signed main() {
#ifndef LOCAL
    fo(math)
#endif
    int T;
    cin >> T;
    while (T--) {
        cout << solve() << "\n";
    }
}