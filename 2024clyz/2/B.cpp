#include <iostream>
#include <vector>
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

using std::cin;
using std::cout;
using std::vector;
#define int long long

vector<int> a, b, fs(501, 0);
vector<vector<int>> f(501, vector<int>(501, 0));
const int M = 1e9 + 7;
int n, k;

void init() {
    for (int i = 1; i <= 500; i++) {
        f[i][i] = f[i][1] = 1;
    }
    for (int i = 3; i <= 500; i++) {
        for (int j = 2; j < i; j++) {
            (f[i][j] = f[i - 1][j - 1] + j * f[i - 1][j]) %= M;
        }
    }
    for (int i = 1; i <= 500; i++) {
        for (int j = 1; j <= i; j++) {
            fs[i] += f[i][j];
        }
        // cout << fs[i] << " ";
    }
    fs[0] = 1;
}

int solveKISZERO() {
    int ans = 1;
    for (int i : b) {
        (ans *= fs[i]) %= M;
    }
    return ans;
}

int solve() {
    b.assign(500 + 1, 0);
    for (int i = 1; i <= n; i++) {
        b[a[i]]++;
    }
    if (k == 0) return solveKISZERO();
}

signed main() {
    fo(divide)
    init();
    cin >> n >> k;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cout << solve();
}