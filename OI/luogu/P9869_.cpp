#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <ostream>

using std::cin;
using std::cout;
using std::vector;
using std::ostream;

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

struct Data {
	int x;
	Data operator=(char c) {
		x = c == 'T' ? 1 : (c == 'F' ? 0 : -1);
		return *this;
	}
	
	Data operator=(int c) {
		x = c;
		return *this;
	}
	
//	operator int() {
//		return x;
//	}
	
//	Data(char c) {
//		*this = c;
//	}
	
//	Data(int c = -2) {
//		*this = c;
//	}
	Data operator!() const {
		Data y;
		y.x = x < 0 ? x : !x;
		return y;
	}
	
	bool operator==(const Data &b) const {
		return x == b.x;
	}
};

struct WAY {
	int w, u, v;
	WAY() { u = v = w = 0; }
	WAY(char _c, int _u, int _v) {
		w = _c == 'T' ? 1 : (_c == 'F' ? 0 : (_c == 'U' ? -1 : (_c == '+' ? 2 : 3)));
		u = _u;
		v = _v;
	}
};

const int inf = 0x7fffffff;
int ans = inf;

void check(vector<Data>a, vector<WAY> w) {
	vector<Data> b = a;
	for (WAY i : w) {
		int u = i.u, v = i.v, k = i.w;
		if (k == 2) {
			b[u].x = b[v].x;
		} else if (k == 3) {
			b[u] = !b[v];
		} else {
			b[u].x = k;
		}
	}
	for (unsigned i = 1; i < a.size(); i++) {
		if (a[i].x != b[i].x) return;
	}
	int _ans = 0;
	for (unsigned i = 1; i < a.size(); i++) {
		_ans += (a[i].x == -1);
	}
	if (_ans < ans) ans = _ans;
//	if (_ans == 0) {
//		for (Data i : a) cout << i.x << " ";
//		cout << "\n";
//	}
}

void dfs(int n, vector<Data> a, vector<WAY> w) {
	if (!n) {
		return check(a, w);
	}
	for (int i = -1; i <= 1; i++) {
		a[n].x = i;
		dfs(n - 1, a, w);
	}
}

void tribool() {
	int c, t;
	cin >> c >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		vector<Data> a(n + 1);
		if (c == 3 || c == 4) {
			for (int i = 1; i <= m; i++) {
				char c;
				int x;
				cin >> c >> x;
				a[x] = c;
			}
			int ans = 0;
			for (int i = 1; i <= n; i++) {
				if (a[i].x == -1) ans++;
			}
			cout << ans << "\n";
			continue;
		}
//		if (c == 1 || c == 2) {
		else {
			ans = inf;
			vector<WAY> w;
			for (int i = 0; i < m; i++) {
				int U, V = 0;
				char W;
				cin >> W >> U;
				if (!(W >= 'A' && W <= 'Z')) cin >> V;
				w.push_back({W, U, V});
			}
			vector<Data> a(n + 1);
			dfs(n, a, w);
			
//			for (auto i : w) {
//				cout << i.w << i.u << i.v << "\n";
//			}
			cout << ans << "\n";
		}
	}
}

int main() {
	// fo(tribool)
	
	tribool();
	return 0;
}
