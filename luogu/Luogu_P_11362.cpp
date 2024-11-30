// 2024.11.30 20:52 回忆代码

#include <bits/stdc++.h>
#include <unordered_map>
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

const int M = 1e9 + 7;

int quickpow(int x, int y) {
    x %= M;
    if (y == 0) return x != 0;
    int z = quickpow(x, y / 2);
    z = z * z % M;
    if (y & 1) z *= x;
    return z % M;
}

int n, m, v;
vector<int> c, d;
unordered_map<int, int> a;

int f(int x) {
    return (x * x - x + 1) % M;
}

int solvemisone() {
    return quickpow(v * v, n - 1);
}

int solveA() {
    return quickpow(f(v), n - 1);
}

int solve() {
    cin >> n >> m >> v;
    assign(0, c, d);
    bool iszero = false;
    for (int i = 0; i < m; i++) {
        int C, D;
        cin >> C >> D;
        c.push_back(C);
        d.push_back(D);
        if (a[C]) {
            if (a[C] == D) c.pop_back(), d.pop_back();
            else iszero = true;
        }
    }
    if (iszero) return 0;
    m = c.size();
    if (m == 1) return solvemisone();
    if (n == m) return solveA();
    return 0;
}

signed main() {
    cin.tie()->sync_with_stdio(0);
    init();

    int T = 1;
    cin >> T;
    while (T--) {
        cout << solve() << endl;
    }
    return 0;
}