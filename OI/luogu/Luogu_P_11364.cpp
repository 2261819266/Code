#include <bits/stdc++.h>
using namespace std;

namespace Leiy {
	void main_init() {
// #ifndef LOCAL
// 		freopen("query.in", "r", stdin);
// 		freopen("query.out", "w", stdout);
// #else
// 		freopen("query.in", "r", stdin);
// 		freopen("query.out", "w", stdout);
// #endif
	}


	const int N = 5e5 + 10;
	vector<int> e[N];
	int dep[N], rnk[N];
	bool vis[N];
	int fa[N][32];
	int n;
	void dfs(int u, int step) {
		dep[u] = step;
		rnk[step] = u;
		vis[u] = 1;
		for (int j = 1; j <= 31; ++j) {
			fa[u][j] = fa[fa[u][j - 1]][j - 1];
		}
		for (auto v : e[u]) {
			if (vis[v]) continue;
			fa[v][0] = u;
			dfs(v, step + 1);
		}
	}
	
	int get(int u, int v) {
		if (dep[u] < dep[v]) swap(u, v);
		for (int j = 31; j >= 0; --j) {
			if (dep[fa[u][j]] >= dep[v]) u = fa[u][j];
		}
		if (u == v) return u;
		for (int j = 31; j >= 0; --j) {
			if (fa[u][j] != fa[v][j])
				u = fa[u][j];
		}
		return fa[u][0];
	}


	struct SegTree {
		vector<int> lc;
		void pushup(int p) {
			lc[p] = get(lc[p << 1], lc[p << 1 | 1] );
		}
		void build(int p, int l, int r) {
			if (l == r) {
				lc[p] = rnk[l];
				return;
			}
			int mid = (l + r) >> 1;
			build(p << 1, l, mid);
			build(p << 1 + 1, mid + 1, r);
			pushup(p);
		}
		SegTree(int n) : lc(n << 2) {}
		int query(int p, int l, int r, int L, int R) {
			if (l > R || r < L) return 0;
			if (L <= l && r <= R) return lc[p];
			int mid = (l + r) >> 1;
			int ll = query(p << 1, l, mid, L, R);
			int lr = query(p << 1 | 1, mid + 1, r, L, R);
			if (!ll) return lr;
			if (!lr) return ll;
			return get(ll, lr);
		}
	};


	void solve() {
		cin >> n;
		vector<int> in(n + 1);
		bool flagA = true;
		for (int i = 1; i < n; ++i) {
			int u, v;
			cin >> u >> v;
			in[v]++;
			if (in[v] > 1) flagA = false;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		fa[1][0] = 1;
		dfs(1, 1);
		if (n <= 10000) {
			int q;
			cin >> q;
			while (q--) {
				int l, r, k;
				cin >> l >> r >> k;
				int mdep = 0;
				for (int len = k; len <= k; ++len) {
					for (int i = l; i + len - 1 <= r; ++i) {
						int j = i + len - 1;
						int lca = i;
						for (int h = i + 1; h <= j; ++h) {
							lca = get(lca, h);
						}
//					if (q == 0) cerr << lca << endl;
						mdep = max(mdep, dep[lca]);
					}
				}
				cout << mdep << endl;
			}
		} else {
			SegTree sgt(n);
			sgt.build(1, 1, n);
			int q;
			cin >> q;
			while (q--) {
				int l, r, k;
				cin >> l >> r >> k;
//				int mdep = 0;
				cout << dep[sgt.query(1, 1, n, l, r)] << endl;
			}
		}
	}
}

signed main() {
	Leiy::main_init();
	int c, t = 1;
//	cin >> c >> t;
	while (t--) {
		Leiy::solve();
	}
}

