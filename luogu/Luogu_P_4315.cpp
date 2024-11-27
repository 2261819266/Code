#include <bits/stdc++.h>
#include <vector>
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

vector<int> fa, dep, siz, son;
vector<int> top, dfn, rnk;
vector<int> vis1, vis2, w;
using PII = pair<int, int>;
vector<vector<PII>> e;
vector<vector<int>> Fa;
int Fa_max;
int cnt = 0, max_dep;

void dfs1(int u = 1, int depth = 1) {
    vis1[u] = true;
    dep[u] = depth;
    max_dep = max(max_dep, depth);
    siz[u] = 1;
    int ms = 0;
    son[u] = 0;
    for (auto [v, W] : e[u]) {
        if (vis1[v]) {
            w[u] = W;
            continue;
        }
        fa[v] = u;
        dfs1(v, depth + 1);
        siz[u] += siz[v];
        if (siz[v] > ms) son[u] = v;
    }
}

void dfs2(int u = 1, int TOP = 1) {
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    vis2[u] = true;
    top[u] = TOP;
    if (!son[u]) return;
    dfs2(son[u], son[u]);
    for (auto [v, w] : e[u]) {
        if (v != son[u] && !vis2[v]) dfs2(v, TOP);
    }
}

struct SegTree {
#define ls (l << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update return a[k] = max(a[ls], a[rs]);
#define num (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)
#define pushdown a[ls] += b[k], a[rs] += b[k], b[ls] += b[k], b[rs] += b[k], b[k] = 0;
    int n;
    vector<int> a, b;
    SegTree(int N) : n(N), a(n << 2), b(n << 2) {}
    SegTree(const vector<int> &A) : n(A.size() - 1), a(n << 2), b(n << 2) { build(1, 1, n, A); }

    int build(int k, int l, int r, const vector<int> &A) {
        if (l == r) return a[k] = A[l];
        build(Ls, A), build(Rs, A);
        update
    }

    int add(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] += x;
        pushdown
        i <= mid ? add(Ls, i, x) : add(Rs, i, x);
        update
    }

    int add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k] += x * num, b[k] += x;
        pushdown
        add(Ls, L, R, x), add(Rs, L, R, x);
        update
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r || L > R) return 0;
        if (l >= L && r <= R) return a[k];
        pushdown
        return max(query(Ls, L, R), query(Rs, L, R));
    }

    int modify(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] = x;
        pushdown
        i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
        update
    }

    int modify(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r || L > R) return 0;
        if (l >= L && r <= R) return a[k] = x, b[k] = x;
        pushdown
        modify(Ls, L, R, x), modify(Rs, L, R, x);
        update
    }
};

int getLCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    if (dep[u] != dep[v]) {
        for (int i = Fa_max; i >= 0; i--) {
            if (dep[Fa[u][i]] <= dep[v]) u = Fa[u][i];
        }
    }
    if (u == v) return u;
    for (int i = Fa_max; i >= 0; i--) {
        if (Fa[u][i] != Fa[v][i]) u = Fa[u][i], v = Fa[v][i];
    }
    return fa[u];
}

void solve() {
    int n;
    cin >> n;
    assign(n + 1, e, w, fa, dep, siz, son, top, dfn, rnk, vis1, vis2, Fa);
    fa[1] = 1;
    vector<PII> es(1);
    for (int i = 1; i < n; i++) {
        int u, v, W;
        cin >> u >> v >> W;
        es.push_back({u, v});
        e[u].push_back({v, W});
        e[v].push_back({u, W});
    }
    dfs1();
    dfs2();

    for (int i = 1; i <= n; i++) {
        Fa[i].push_back(fa[i]);
    }
    for (int j = 1; (1 << j) <= max_dep; j++) {
        Fa_max = j;
        for (int i = 1; i <= n; i++) {
            Fa[i].push_back(Fa[Fa[i][j - 1]][j - 1]);
        }
    }

    SegTree a(n);
    for (int i = 2; i <= n; i++) {
        a.modify(1, 1, n, i, w[rnk[i]]);
    }
    string s;
    cin >> s;
    while (s != "Stop") {
        int x, y, z;
        if (s == "Max") {
            cin >> x >> y;
            int k = getLCA(x, y);
            int ans = 0;
            while (top[x] != top[k]) {
                ans = max(ans, a.query(1, 1, n, dfn[top[x]] + 1, dfn[x]));
                x = fa[top[x]];
            }
            while (top[y] != top[k]) {
                ans = max(ans, a.query(1, 1, n, dfn[top[y]], dfn[y]));
                y = fa[top[y]];
            }
            if (dep[x] < dep[y]) swap(x, y);
            ans = max(ans, a.query(1, 1, n, dfn[y] + 1, dfn[x]));
            cout << ans << endl;
        } else if (s == "Change") {
            cin >> x >> y;
            int u = es[x].first, v = es[x].second;
            if (dep[u] < dep[v]) swap(u, v);
            a.modify(1, 1, n, dfn[u], y);
        } else if (s == "Cover") {
            
        }
        cin >> s;
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