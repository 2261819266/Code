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

const int inf = 0x3fffffffffffffff;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update return a[k] = a[ls] + a[rs], b[k] = max(b[ls], b[rs]);
    int n;
    vector<int> a, b;
    SegTree(int N) : n(N), a(n << 2), b(n << 2, -inf) {}
    SegTree(const vector<int> &A) : n(A.size() - 1), a(n << 2), b(n << 2, -inf) { build(1, 1, n, A); }

    int build(int k, int l, int r, const vector<int> &A) {
        if (l == r) return a[k] = b[k] = A[l];
        build(Ls, A), build(Rs, A);
        update
    }

    int modify(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] = b[k] = x;
        i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
        update
    }

    int query(int k, int l, int r, int L, int R, int K) {
        if (l > R || L > r) return K ? -inf : 0;
        if (l >= L && r <= R) return K ? b[k] : a[k];
        int lc = query(Ls, L, R, K), rc = query(Rs, L, R, K);
        return K ? max(lc, rc) : (lc + rc);
    }

    void modify(int i, int x) { modify(1, 1, n, i, x); }
    int query(int l, int r, int K) { return query(1, 1, n, l, r, K); }
    int qsum(int l, int r) { return query(1, 1, n, l, r, 0); }
    int qmax(int l, int r) { return query(1, 1, n, l, r, 1); }
};

vector<int> fa, dep, siz, son, vis, w;
vector<int> top, dfn, rnk;
int cnt = 0, LCA_max = 22;
vector<vector<int>> e, Fa;

void dfs1(int u = 1, int depth = 1) {
    vis[u] = true;
    dep[u] = depth;
    siz[u] = 1;
    son[u] = 0;
    int ms = 0;
    for (int v : e[u]) {
        if (vis[v]) continue;
        fa[v] = u;
        dfs1(v, depth + 1);
        siz[u] += siz[v];
        if (siz[v] > ms) son[u] = v, ms = siz[v];
    }
}

void dfs2(int u = 1, int TOP = 1) {
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    top[u] = TOP;
    if (!son[u]) return;
    dfs2(son[u], TOP);
    for (int v : e[u]) {
        if (fa[v] == u && v != son[u]) dfs2(v, v);
    }
}

void LCA_init(int n) {
    assign(n + 1, Fa);
    for (int i = 1; i <= n; i++) {
        Fa[i].push_back(fa[i]);
    }
    for (int j = 1; j <= LCA_max; j++) {
        for (int i = 1; i <= n; i++) {
            Fa[i].push_back(Fa[Fa[i][j - 1]][j - 1]);
        }
    }
}

int getLCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    if (dep[u] != dep[v]) for (int i = LCA_max; i >= 0; i--) if (dep[Fa[u][i]] >= dep[v]) u = Fa[u][i];
    if (u == v) return u;
    for (int i = LCA_max; i >= 0; i--) if (Fa[u][i] != Fa[v][i]) u = Fa[u][i], v = Fa[v][i];
    return fa[u];
}

void solve() {
    int n;
    cin >> n;
    assign(n + 1, fa, dep, siz, son, w, top, dfn, rnk, vis, e);
    for (int i = 1; i < n; i++) {
        int u, v;;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    fa[1] = 1;
    dfs1();
    dfs2();

    // for (int i : top) cout << i << " ";
    

    for (int i = 1; i <= n; i++) cin >> w[dfn[i]];
    SegTree a(w);

    LCA_init(n);

    auto Update = [](int &x, int y, int k) {
        if (k) return x = max(x, y);
        else return x += y;
    };

    int m;
    cin >> m;
    while (m--) {
        string s;
        int x, y;
        cin >> s >> x >> y;
        if (s == "CHANGE") a.modify(dfn[x], y);
        else {
            int z = getLCA(x, y), K = s == "QMAX";
            int ans = K ? -inf : 0;
            while (top[x] != top[z]) Update(ans, a.query(dfn[top[x]], dfn[x], K), K), x = fa[top[x]];
            while (top[y] != top[z]) Update(ans, a.query(dfn[top[y]], dfn[y], K), K), y = fa[top[y]];
            if (dep[x] > dep[y]) swap(x, y);
            Update(ans, a.query(x, y, K), K);
            cout << ans << endl;
        }
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
