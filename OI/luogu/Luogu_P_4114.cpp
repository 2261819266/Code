#include <bits/stdc++.h>
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem problem
#define int long long
#define endl "\n"

using namespace std;

namespace Problem {
template<typename T>
void assign(int n, vector<T> &x) {
	x.assign(n, T());
}

template<typename T, typename ...Arg>
void assign(int n, vector<T> &x, vector<Arg> &...y) {
	assign(n, x);
	assign(n, y...);
}

void init() {

}

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update a[k] = a[ls] + a[rs];
	int n;
	vector<int> a;
	SegTree() = default;
	SegTree(int N) : n(N), a(n << 2) {}
	
	int modify(int k, int l, int r, int i, int x) {
		if (l == r) return a[k] = x;
		i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
		update
	}
	
	int query(int k, int l, int r, int L, int R) {
		if (l > R || L > r) return 0;
		if (l >= L && r <= R) return a[k];
		return query(Ls, L, R) + query(Rs, L, R);
	}
	
	void modify(int i, int x) { modify(1, 1, n, i, x); }
	int query(int l, int r) { return query(1, 1, n, l, r); }
} a;

using PII = pair<int, int>;
vector<PII> es;
vector<vector<PII>> e;
vector<int> vis, fa, dep, siz, son;
vector<int> top, dfn, rnk, w;
int cnt;

void dfs1(int u = 1, int depth = 1) {
	vis[u] = true;
	dep[u] = depth;
	siz[u] = 1;
	son[u] = 0;
	int ms = 0;
	for (PII p : e[u]) {
		int v = p.first, W = p.second;
		if (vis[v]) continue;
		fa[v] = u;
		w[v] = W;
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
	for (PII p : e[u]) {
		int v = p.first;
		if (v != son[u] && fa[v] == u) dfs2(v, v);
	}
}

void change(int i, int x) { 
	int u = es[i].first, v = es[i].second;
	a.modify(dep[u] > dep[v] ? u : v, x);
}

int query(int u, int v) {
	int ans = 0;
	while (top[u] != top[v]) {
		int &x = dep[top[u]] > dep[top[v]] ? u : v;
		ans += a.query(dfn[top[x]], x);
		x = fa[top[x]];
	}
	if (dep[u] < dep[v]) ans += a.query(u, v);
	else ans += a.query(v, u);
	return ans;
}

void solve() {
	int n;
	cin >> n;
	assign(n + 1, e, vis, fa, dep, siz, son, top, dfn, rnk, es, w);
//	a = SegTree(n);
//	fa[1] = 1;
//	for (int i = 1; i < n; i++) {
//		int u, v, w;
//		es[i] = {u, v};
//		e[u].push_back({v, w});
//		e[v].push_back({u, w});
//	}
//	dfs1();
//	dfs2();
//	for (int i = 2; i <= n; i++) {
//		a.modify(dfn[i], w[i]);
//	}
//	string op;
//	while (op != "DONE") {
//		int x, y;
//		cin >> op >> x >> y;
//		if (op == "CHANGE") change(x, y);
//		else cout << query(x, y) << endl;
//		cin >> op;
//	}
}

void main() {
	init();
	int T = 1;
//	cin >> T;
	while (T--) {
		solve();
	}
	return;
}
}

signed main() {
	fo()
	cin.tie()->sync_with_stdio(0);
	Problem::main();
	return 0;
}
