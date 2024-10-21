#include <iostream>
#include <vector>
#include <cmath>
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define int long long

using std::cin;
using std::cout;
using std::vector;

double getsmall(double x) {
    if (x < 0) return getsmall(-x);
    return x - (int)x;
}

bool isgood(double x, double e = 1e-9) {
    double y = getsmall(x);
    return y < e || y > 1 - e;
}

int solve() {
    int n, k, m;
    cin >> n >> k;
    m = sqrt(k);
    // if (m % 2) {
    //     return n % 2;
    // } else return n;
    double x = sqrt(k);
    for (int i = 2; i <= 1e9; i++) {
        int y = sqrt(i*i*2);
        if (isgood(i * x)) 
            cout << i << " " << i * x << "\n";
    }
    cout << "\n";
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