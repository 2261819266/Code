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

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update return a[k] = (a[ls] + a[rs]) % M;
#define num (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)
#define pushdown (a[ls] += b[k] * lm) %= M, (a[rs] += b[k] * rm) %= M, (b[ls] += b[k]) %= M, (b[rs] += b[k]) %= M, b[k] = 0;
    int n, M;
    vector<int> a, b;
    SegTree() = default;
    SegTree(int m, const vector<int> &A, const vector<int> &rnk) : n(A.size() - 1), M(m), a(n << 2), b(n << 2) { build(1, 1, n, A, rnk); }

private:
    int build(int k, int l, int r, const vector<int> &A, const vector<int> &rnk) {
        if (l == r) return a[k] = A[rnk[l]];
        build(Ls, A, rnk), build(Rs, A, rnk);
        update
    }

    int add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return (a[k] += x * num) %= M, (b[k] += x) %= M;
        pushdown
        add(Ls, L, R, x), add(Rs, L, R, x);
        update
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k] % M;
        pushdown
        return (query(Ls, L, R) + query(Rs, L, R)) % M;
    }
public:
    void add(int l, int r, int x) { if (l > r) swap(l, r); add(1, 1, n, l, r, x); }
    int query(int l, int r) { if (l > r) swap(l, r); return query(1, 1, n, l, r); }
    void print() {
        for (int i = 1; i <= n; i++) cerr << query(i, i) << " ";
        cerr << "\n";
    }
};

int n, m, s, M;
vector<int> w;
vector<vector<int>> e;
vector<int> vis, fa, dep, siz, son;
vector<int> top, dfn, rnk, bottom;
int cnt;
SegTree a;

void dfs1(int u = s, int depth = 1) {
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
        if (siz[v] > ms) ms = siz[v], son[u] = v;
    }
}

void dfs2(int u = s, int TOP = s) {
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    top[u] = TOP;
    bottom[u] = u;
    if (!son[u]) return;
    dfs2(son[u], TOP);
    for (int v : e[u]) if (v != son[u] && v != fa[u]) dfs2(v, v);
    bottom[u] = rnk[cnt];
}

void add(int u, int v, int W) {
    while (top[u] != top[v]) {
        int &x = dep[top[u]] > dep[top[v]] ? u : v;
        a.add(dfn[top[x]], dfn[x], W);
        x = fa[top[x]];
    }
    a.add(dfn[u], dfn[v], W);
}

void add(int u, int W) { a.add(dfn[u], dfn[bottom[u]], W); }

int query(int u, int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        int &x = dep[top[u]] > dep[top[v]] ? u : v;
        ans += a.query(dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    return (ans += a.query(dfn[u], dfn[v])) %= M;
}

int query(int u) { return a.query(dfn[u], dfn[bottom[u]]) % M; }

void solve() {
    cin >> n >> m >> s >> M;
    assign(n + 1, w, e, vis, fa, dep, siz, son, top, dfn, rnk, bottom);
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1();
    dfs2();
    a = SegTree(M, w, rnk);
    while (m--) {
        // a.print();
        int op, x, y, z;
        cin >> op;
        switch (op) {
            case 1: cin >> x >> y >> z, add(x, y, z); break;
            case 2: cin >> x >> y, cout << query(x, y) << endl; break;
            case 3: cin >> x >> y, add(x, y); break;
            case 4: cin >> x, cout << query(x) << endl; break;
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