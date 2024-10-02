#include <algorithm>
#include <iostream>
#include <vector>
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define int long long

using std::cin;
using std::cout;
using std::vector;

int pow(int x, int n) {
    if (n == 0) return 1;
    int y = pow(x, n / 2);
    y *= y;
    if (n % 2) y = y * x;
    return y;
}

int dfs(const vector<int> &a, vector<int> &b, int s, int i = 0) {
    if (i == a.size()) {
        return 1;
    }
    int ans = 0;
    for (int I = 1, j = a[i]; j <= s; I++, j *= a[i]) {
        b[i] = I;
        ans += dfs(a, b, s - j, i + 1);
    }
    return ans;
}

int solveKISZERO(int a, int n, int s) {
    if (n * a > s) return 0;
    int ans = 0;
}

signed main() {
#ifndef LOCAL
    fo(problem)
#endif
    int n, s;
    cin >> n >> s;
    bool K = 1;
    vector<int> a(n), b(n, 0);
    for (int &i : a) cin >> i, K &= i == a.front();
    
    // cout << solveKISZERO(a.front(), n, s) << "\n";
    // cout << dfs(a, b, s) << "\n";

    cout << (K ? solveKISZERO(a.front(), n, s) : dfs(a, b, s));
}