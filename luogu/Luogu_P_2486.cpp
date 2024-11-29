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
#define update return a[k] = a[ls] + a[rs], 0;
#define pushdown do { if (b[k]) a[ls] = a[rs] = a[k], b[ls] = b[rs] = !(b[k] = 0); } while (0);
    struct Node {
        int sum = 0, lc = 0, rc = 0;
        int operator*() const { return sum; }
        friend bool operator&(const Node &p, const Node &q) { return p.rc == q.lc; }
        friend Node operator+(const Node &p, const Node &q) { return {*p + *q - ((p & q) && *p && *q), *p ? p.lc : q.lc, *q ? q.rc : p.rc}; }
        Node() = default;
        Node(int x) : sum(1), lc(x), rc(x) { }
        Node(int x, int y, int z) : sum(x), lc(y), rc(z) {} 
        Node &operator=(int x) { return *this = Node(x); }
        Node &operator+=(const Node &x) { return *this = *this + x; }
	};

	int n;
    vector<Node> a;
    vector<int> b;
    SegTree() = default;
    SegTree(const vector<int> &data, const vector<int> &rnk) : n(data.size() - 1), a(n << 2), b(n << 2) { build(1, 1, n, data, rnk); }

    int build(int k, int l, int r, const vector<int> &data, const vector<int> &rnk) {
        if (l == r) return a[k] = data[rnk[l]], 0;
        build(Ls, data, rnk), build(Rs, data, rnk);
        update
    }

    int modify(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k] = x, b[k] = 1, 0;
        pushdown
        modify(Ls, L, R, x), modify(Rs, L, R, x);
        update
    }

    Node query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return {0, 0, 0};
        if (l >= L && r <= R) return a[k];
		pushdown
			// int x = query(Ls, L, R), y = query(Rs, L, R), ans = x + y;
			// if (x && y && (a[ls] & a[rs])) ans--;
			Node placeholder = query(Ls, L, R) + query(Rs, L, R);
		return placeholder;
	}

    void modify(int l, int r, int x) { modify(1, 1, n, l, r, x); }
    Node query(int l, int r) { return query(1, 1, n, l, r); }
} a;

vector<vector<int>> e;
vector<int> wt;
vector<int> vis, fa, dep, siz, son;
vector<int> top, dfn, rnk;
int cnt;

void dfs1(int u = 1, int depth = 1) {
    vis[u] = 1;
    dep[u] = depth;
    son[u] = 0;
    siz[u] = 1;
    int ms = 0;
    for (int v : e[u]) {
        if (vis[v]) continue;
        fa[v] = u;
        dfs1(v, depth + 1);
        siz[u] += siz[v];
        if (siz[v] > ms) ms = siz[v], son[u] = v;
    }
}

void dfs2(int u = 1, int TOP = 1) {
    top[u] = TOP;
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    if (!son[u]) return;
    dfs2(son[u], TOP);
    for (int v : e[u]) {
        if (v != son[u] && fa[v] == u) dfs2(v, v);
    }
}

void change(int u, int v, int w) {
    while (top[u] != top[v]) {
        int &x = dep[top[u]] > dep[top[v]] ? u : v;
        a.modify(dfn[top[x]], dfn[x], w);
        x = fa[top[x]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    a.modify(dfn[u], dfn[v], w);
}

int query(int u, int v) {
    if (u == v) return 1;
    SegTree::Node l, r;
    while (top[u] != top[v]) {
        int &x = dep[top[u]] > dep[top[v]] ? u : v;
        SegTree::Node &y = dep[top[u]] > dep[top[v]] ? l : r;
        y = a.query(dfn[top[x]], dfn[x]) + y;
        x = fa[top[x]];
    }
    if (dep[u] > dep[v]) l = a.query(dfn[v], dfn[u]) + l;
    else r = a.query(dfn[u], dfn[v]) + r;
    return *l + *r - (*l && *r && l.lc == r.lc);
}

void solve() {
    int n, m;
    cin >> n >> m;
    // if (n > 100) return;
    assign(n + 1, e, wt, vis, fa, dep, siz, son, top, dfn, rnk);
    fa[1] = 1;
    for (int i = 1; i <= n; i++) cin >> wt[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1();
    dfs2();
    a = SegTree(wt, rnk);
    while (m--) {
        char op;
        int x, y, z;
        cin >> op >> x >> y;
        if (op == 'Q') cout << query(x, y) << endl;
        else cin >> z, change(x, y, z);
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