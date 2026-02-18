#include <bits/stdc++.h>
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define int long long
#define endl "\n"
#define space " "

#define Problem detect

using namespace std;

namespace Problem {
template<typename t>
ostream &operator<<(ostream &out, const vector<t> &a) {
	for (const t &i : a) out << i << space;
	return out;
}

template<typename t>
istream &operator>>(istream &in, vector<t> &a) {
	for (t &i : a) in >> i;
	return in;
}
	
struct Car {
	int d, v, a;
	friend istream &operator>>(istream &in, Car &car) {
		return in >> car.d >> car.v >> car.a;
	}
	
	operator int() { return a; }

};

struct Block {
	int l, r;
//	operator int() { return r - l + 1; }
	bool operator>(int x) { return x >= l && x <= r; }
	bool operator<(const Block &b) const { return l < b.l; }
};

int n, m, L, V, ans;
vector<Car> a;
vector<int> b;
vector<Block> bs;

void solve0() {
//	priority_queue<Block> q;
	for (Block i : bs) {
		cout << i.l << space << i.r << endl;
	}
	sort(bs.begin(), bs.end());
	int r = bs.size();
	vector<int> ans(1, 0ll), vis(m, 0);
	int cnt = 0;
	for (Block j : bs) {
		if (j > 0) cnt++;
//		cout << cnt << space << j.l << space << j.r << endl;
	}
//	cout << cnt << endl;
	for (int i = 1; i < m && cnt < m; i++) {
		int u = ans.back();
		bool k = u + 1 == i;
		int c = 0;
//		cout << bs.size();
//		cout << "i" << (u == i - 1) << space << i << endl;
		for (int J = 0; J < r; J++) {
			Block j = bs[J];
			if (j > i && !(j > u)) c++;
//			cout << "b" << (j > i && !(j > u));
			
			if (!vis[J] && j > u && !(j > i)) k = false;
			
		}
		if (k) {
			ans.pop_back();
		} 
		if (c || k) ans.push_back(i);
		cnt += c;
//		cout << "k" << k << space << c << space << cnt << endl;
//		cout << ans << endl;
//		for (int j = 0; j < r; j++) {
//			if (bs[j].l <= u) vis[j] = true;
//		}
	}
	cout << m - ans.size();
//	cout << endl << ans;
}

void solveA() {
	cout << m - (ans > 0);
}

void solveB() {
	solveA();
}

void solveC() {
	solve0();
}

int sqr(int x) { return x * x; }

int get_ceil(int x, int y) { return x / y + (bool)(x % y); }

int get_floor(int x, int y) { return x / y; }

void solve() { 
	bs.clear();
	cin >> n >> m >> L >> V;
	a.assign(n, {});
	b.assign(m, 0);
	cin >> a >> b;
	int symbol = a[0] == 0 ? 1 : a[0] > 0 ? 2 : 3;
	for (int i = 1; i < n; i++) {
		if (symbol != (a[i] == 0 ? 1 : a[i] > 0 ? 2 : 3)) {
			symbol = 0;
			break;
		}
	}
	
	
	
	ans = 0;
	for(const Car &i : a) {
		if (b.back() < i.d) continue;
		int next = lower_bound(b.begin(), b.end(), i.d) - b.begin();
		if (i.a == 0 && i.v > V) {
			ans++;
			bs.push_back({next, m - 1});
		}
		if (i.a < 0) {
			int s = get_ceil(sqr(V) - sqr(i.v), 2 * i.a);
			int Ek = sqr(i.v) + 2 * i.a * (b[next] - i.d);
			if (Ek > sqr(V)) {
				ans++;
//				cout << s + i.d << endl;
				int r = lower_bound(b.begin(), b.end(), s + i.d) - b.begin() - 1;
				bs.push_back({next, r});
			}
		}
		if (i.a > 0) {
			int s = get_floor(sqr(V) - sqr(i.v), 2 * i.a);
			int Ek = sqr(i.v) + 2 * i.a * (b.back() - i.d);
			if (Ek > sqr(V)) {
				ans++;
				int l = upper_bound(b.begin(), b.end(), s + i.d) - b.begin();
//				cout << s + i.d << endl;
				bs.push_back({l, m - 1});
			}
		}
	}
	cout << ans << space;
	auto f = symbol == 0 ? solve0 : symbol == 1 ? solveA : symbol == 2 ? solveB : solveC;
	f();
	cout << endl;
}
	
void main() {
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	Problem::main();
	return 0;
}
