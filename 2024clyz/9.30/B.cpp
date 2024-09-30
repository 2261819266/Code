#include <iostream>
#include <vector>
#define int long long

const int M = 998244353;
using std::cin;
using std::cout;
using std::vector;

int pow(int x, int n) {
    if (n == 0) return 1;
    int y = pow(x, n / 2);
    y *= y;
    if (n % 2) y = y % M * x;
    return y % M;
}

int solve(int n) {
    vector<vector<int>> f(n + 1, vector<int>(n + 1, 0));
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i][i] = (f[i - 1][i - 1] + f[i - 1][i]) % M;
        for (int j = i + 1; j <= n; j++) {
            if (i == 1) f[i][j] = 1;
            else {
                f[i][j] = (f[i - 1][j] + f[i][j - 1]) % M;
            }
        }
    }
    // for (auto i : f) {
    //     for (int j : i) cout << j << " ";
    //     cout << "\n";
    // }
    return f[n][n] % M;
}

signed main() {
    int n;
    cin >> n;
    cout <<solve(n) << "\n";
}