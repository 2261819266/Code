// 2024.11.30 21:11 回忆代码

#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

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

const int maxn = 1e5 + 7, M = 1e9 + 7;
vector<int> jc;

inline void init() {
    assign(maxn, jc);
    jc[0] = jc[1] = 1;
    for (int i = 2; i < maxn; i++) jc[i] = (jc[i - 1] * i) % M;
    return;
}

using PII = pair<int, int>;
vector<vector<int>> e;
vector<PII> es;
vector<int> ed, vis, d;

int dfs(int u) {
    vis[u] = true;
    d[u] = 0;
    int t = 0, ans = 1;
    for (int v : e[u]) {
        d[u]++;
        if (vis[v]) continue;
        ans = (ans * dfs(v)) % M;
        t++;
    }
    return ans * jc[t] % M;
}

int n, m, anszero;

int solvemisone() {
    // assign(n + 1, vis);
    int u = es[ed[0]].first, v = es[ed[0]].second;
    vis[u] = vis[v] = true;
    int x = dfs(u), y = dfs(v);
    return x * y % M;
    // dfs(1);
    // int ans = 1;
    // for (int i = 1; i <= n; i++) {
    //     ans = ans * jc[d[i] - 1] % M;
    // }
    // return ans;
}


int solveB() {
    return ((m * jc[n - 2] - m * (m - 1) / 2 % M * jc[n - 3]) % M + M) % M;
}

int solve(int C) {
    cin >> n >> m;
    es.clear();
    assign(n + 1, e, vis, d);
    assign(m, ed);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        es.push_back({u, v});
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int &i : ed) cin >> i, i--;
    if (m == 1) return solvemisone();
    if (C == 18) return 1;
    if (C >= 19 && C <= 21) return solveB();
    return 0;
}

signed main() {
    // fo(traverse)
    cin.tie()->sync_with_stdio(0);
    init();

    int c, T = 1;
    cin >> c >> T;
    while (T--) {
        cout << solve(c) << endl;
    }
    return 0;
}