#include <bits/stdc++.h>
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

vector<int> vis, fa, dep, siz, son;
vector<int> top, dfn, rnk;
int cnt = 0, s, n, m;
vector<vector<int>> e;

void dfs1(int u = s, int depth = 1) {
    vis[u] = true;
    dep[u] = depth;
    siz[u] = 1;
    int ms = 0;
    for (int v : e[u]) {
        if (vis[v]) continue;
        fa[v] = u;
        dfs1(v, depth + 1);
        siz[u] += siz[v];
        if (siz[v] > ms) son[u] = v, ms = siz[v];
    }
}

void dfs2(int u = s, int TOP = s) {
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    top[u] = TOP;
    if (!son[u]) return;
    dfs2(son[u], TOP);
    for (int v : e[u]) {
        if (v != son[u] && v != fa[u]) dfs2(v, v);
    }
}

int getLCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    if (u == v) return u;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) v = fa[top[v]];
        else u = fa[top[u]];
    }
    return dep[u] > dep[v] ? v : u;
}

void solve() {
    cin >> n >> m >> s;
    assign(n + 1, vis, fa, dep, siz, son, top, dfn, rnk, e);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    fa[s] = s;
    dfs1();
    dfs2();
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << getLCA(u, v) << endl;
    }
}

signed main() {
    cin.tie()->sync_with_stdio(0);
    init();

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}