#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
const int N = 8;
// sz : 第i个节点现在的位置
int t, n, m, sz[N], cnt;
char pre[N], ept, nw[N];
bool vis[N];
struct edge {
	int to, tp;
};
// edge
vector<edge> v[N];
// 第i个点拆成的点
vector<int> id[N];
void clear() {
	for (int i = 1; i <= cnt; i++) {
		pre[i] = nw[i] = ept, vis[i] = false;
		v[i].clear();
	}
	for (int i = 1; i <= n; i++) {
		id[i].clear();
	}
	cnt = 0;
}
char chg(char c, int tp) {
	if (tp == 1)
		return c;
	if (c == 'T')
		return 'F';
	if (c == 'F')
		return 'T';
	return 'U';
}
int bf(int x, char c) {
	if (pre[x] != ept && pre[x] != c)
		return -1;
	nw[x] = c;
	int num = 0;
	if (x <= n)
		num += (nw[x] != 'U');
	queue<int> q;
	q.push(x);
	vis[x] = true;
	while (!q.empty()) {
		int s = q.front();
		q.pop();
		for (edge E : v[s]) {
			int to = E.to;
			char c_to = chg(nw[s], E.tp);
			if (pre[to] != ept && pre[to] != c_to) {
				return -1;
			}
			if (nw[to] != ept && nw[to] != c_to) {
				return -1;
			}
			nw[to] = c_to;
			if (!vis[to]) {
				vis[to] = true;
				q.push(to);
				if (to <= n)
					num += (nw[to] != 'U');
			}
		}
	}
	return num;
}
void rbf(int x) {
	queue<int> q;
	q.push(x);
	nw[x] = ept;
	vis[x] = false;
	while (!q.empty()) {
		int s = q.front();
		q.pop();
		for (edge E : v[s]) {
			int to = E.to;
			if (nw[to] != ept) {
				nw[to] = ept;
				vis[to] = false;
				q.push(to);
			}
		}
	}
}
void tag(int x) {
	queue<int> q;
	q.push(x);
	vis[x] = true;
	while (!q.empty()) {
		int s = q.front();
		q.pop();
		for (edge E : v[s]) {
			int to = E.to;
			if (!vis[to]) {
				vis[to] = true;
				q.push(to);
			}
		}
	}
}
int lst(int x) {
	return id[x][sz[x] - 1];
}
void mian() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) {
		sz[i] = 1;
		id[i].push_back(++cnt);
	}
	for (int i = 1; i <= m; i++) {
		char c;
		cin >> c;
		if (c == 'T' || c == 'U' || c == 'F') {
			int x = read();
			sz[x]++, pre[++cnt] = c;
			id[x].push_back(cnt);
		} else if (c == '+' || c == '-') {
			int x = read(), y = read();
			if (x == y) {
				int fk = lst(x);
				sz[x]++, id[x].push_back(++cnt);
				v[fk].push_back({lst(x), (c == '+')});
				v[lst(x)].push_back({fk, (c == '+')});
				continue;
			}
			sz[x]++, id[x].push_back(++cnt);
			v[lst(x)].push_back({lst(y), (c == '+')});
			v[lst(y)].push_back({lst(x), (c == '+')});
		}
	}
	for (int i = 1; i <= n; i++) {
		if (i != lst(i)) {
			v[i].push_back({lst(i), 1});
			v[lst(i)].push_back({i, 1});
		}
	}
	int ans = 0;
	for (int i = 1; i <= cnt; i++) {
		int mx = 0;
		if (!vis[i]) {
			mx = max(mx, bf(i, 'T'));
			rbf(i);
			// mx = max(mx, bf(i, 'F'));
			// rbf(i);
			mx = max(mx, bf(i, 'U'));
			rbf(i);
			tag(i);
		}
		ans += mx;
	}
	cout << n - ans << '\n';
	clear();
}
int main() {
	read();
	t = read();
	while (t--)
		mian();
	return 0;
}