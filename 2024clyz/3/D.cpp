#include <iostream>
#include <vector>
#define int long long
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define int long long

using std::cin;
using std::cout;
using std::vector;

const int M = 998244353;

int pow(int x, int n) {
    if (n == 0) return 1;
    int y = pow(x, n / 2);
    y *= y;
    if (n % 2) y = y % M * x;
    return y % M;
}

int exgcd(int a, int b, int &x, int &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int get(int a) {
    int x, y, d;
    d = exgcd(a, M, x, y);
    return (x % M + M) % M;
}

int C(int n, int k) {
    if (k == 0) return 1;
    return (C(n, k - 1) * (n - k + 1) * get(k)) % M;
}

int qmi(int a, int b, int mod) {
    int res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

vector<int> a;

int dfs(int n, int m, int s = 0, int i = 0) {
    if (i == n) {
        return (s % m) > 0;
    }
    int ans = 0;
    for (int j = 1; j < m; j++) {
        (ans += dfs(n, m, s + j, i + 1)) %= M;
    }
    return ans;
}

signed main() {
#ifndef LOCAL
    fo(paper)
#endif
    int n, m;
    cin >> n >> m;
    if (m == 3) {
        int i, ans = 0, s = 1;
        for (i = 0; (n - i * 2) % 3; i++);
        for (; i <= n; i += 3) {
            (ans += C(n, i)) %= M;
        }
        cout << ((pow(2, n) - ans) % M + M) % M << "\n";
        // cout << dfs(n, m) << "\n";
    } else {
        a.assign(n, 0);
        cout << dfs(n, m) << "\n";
    }
}