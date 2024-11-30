// 2024.11.30 21:27 回忆代码

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

inline void init() {
    return;
}

   static const int inf = 0x3fffffffffffffff;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update return a[k] = max(a[ls], a[rs]), b[k] = min(b[ls], b[rs]);
    int n;
    vector<int> a, b;
    SegTree(int N) : n(N), a(n << 2), b(n << 2, inf) {}
    SegTree(const vector<int> &data) : n(data.size() - 1), a(n << 2), b(n << 2, inf) { build(1, 1, n, data); }

    int build(int k, int l, int r, const vector<int> &data) {
        if (l == r) return a[k] = b[k] = data[l];
        build(Ls, data), build(Rs, data);
        update
    }

    int modify(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] = b[k] = x;
        i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
        update
    }

    int querymax(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        return max(querymax(Ls, L, R), querymax(Rs, L, R));
    }

    int querymin(int k, int l, int r, int L, int R) {
        if (l > R || L > r || L > R) return inf;
        if (l >= L && r <= R) return b[k];
        return min(querymin(Ls, L, R), querymin(Rs, L, R));
    }
};

const int maxldep = 30;
int n, q, mxdep;
vector<vector<int>> e, F;
vector<int> vis, dep, fa;


void dfs(int u = 1) {
    vis[u] = 1;
    mxdep = max(mxdep, dep[u]);
    for (int v : e[u]) {
        if (vis[v]) continue;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs(v);
    }
}

void LCAinit() {
    fa[1] = 1;
    dep[1] = 1;
    dfs();
    for (int i = 1; i <= n; i++) F[i].push_back(fa[i]);
    for (int j = 1; j <= maxldep; j++) {
        for (int i = 1; i <= n; i++) {
            F[i].push_back(F[F[i][j - 1]][j - 1]);
        }
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    if (dep[u] != dep[v]) {
        for (int i = maxldep; i >= 0; i--) {
            if (dep[F[u][i]] >= dep[v]) u = F[u][i];
        }
    }
    if (u == v) return u;
    for (int i = maxldep; i >= 0; i--) {
        if (F[u][i] != F[v][i]) u = F[u][i], v = F[v][i];
    }
    return fa[u];
}

void solvesmall() {
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int l = 1; l <= n; l++) {
        a[l][l] = l;
        for (int r = l + 1; r <= n; r++) {
            a[l][r] = LCA(a[l][r - 1], r);
        }
    }

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int ans = 0;
        for (int i = l; i + k - 1 <= r; i++) {
            ans = max(ans, dep[a[i][i + k - 1]]);
        }
        cout << ans << endl;
    }
}

void solveB() {
    SegTree a(n), b(dep);
    for (int i = 1; i < n; i++) a.modify(1, 1, n, i, dep[LCA(i, i + 1)]);
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int ans = a.querymin(1, 1, n, l, r - 1);
        if (k == 1) {
            cout << b.querymax(1, 1, n, l, r) << endl;
            continue;
        }
        for (int i = l; i + k - 1 <= r; i++) {
            ans = max(ans, a.querymin(1, 1, n, i, i + k - 2));
        }
        cout << ans << endl;
    }
}

void solve() {
    cin >> n;
    assign(n + 1, e, F, vis, dep, fa);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    cin >> q;
    LCAinit();
    // if (n <= 6e3) return solvesmall();
    // if (n == mxdep) return solveB();
    solveB();
}

signed main() {
    fo(query)
    cin.tie()->sync_with_stdio(0);
    init();

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}