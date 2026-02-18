#include <bits/stdc++.h>
#include <type_traits>
#include <vector>

using namespace std;

#define int long long
#define Problem CF558E

namespace Problem {
#define endl "\n"
#define space " "

template<typename t = int>
ostream &operator<<(ostream &out, const vector<t> &a) {
//	cout << 1;
	for (t i : a) {
		out << i << space;
	}
	return out;
}

vector<int> operator+(const vector<int> &a, const vector<int> &b) {
	
//		cout << 1;
	int n = a.size();
	if (b.size() < n) n = b.size();
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = a[i] + b[i];
	}
//		cout << 2;
	return ans;
}

vector<int> operator+=(vector<int> &a, const vector<int> b) {
	return a = a + b;
}

vector<int> operator-(const vector<int> &a, const vector<int> &b) {
//	cout << 1;
	int n = a.size();
	if (b.size() < n) n = b.size();
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = a[i] - b[i];
	}
//	cout << 2;
	return ans;
}

vector<int> operator-=(vector<int> &a, const vector<int> b) {
	return a = a - b;
}

vector<int> operator-(const vector<int> &a, int x) {
//	cout << 1;
	int n = a.size();
	vector<int> ans(n);
	int i = 0;
	// cout << a << x << endl;
	if (x && i < n)  {
        while (x && i < n) {
	    	if (x <= a[i]) {
	    		ans[i] = a[i] - x;
	    		break;
	    	}
	    	else x -= a[i];
	    	i++;
//	    	cout << x;
	    }
	    i++;
    }
	for (; i < n; i++) {
		ans[i] = a[i];
	}
		// cout << ans << x << endl;
//	cout << 2;
	return ans;
}

vector<int> operator-=(vector<int> &a, int x) {
	return a = a - x;
}
	
struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define updata return (a[k] = a[ls] + a[rs]).size();
#define num (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)
#define pushdown do {\
		if (b[k] == -1) break;\
		bool _K = b[k];\
		a[_K ? rs : ls] = a[k] - (_K ? lm : rm);\
		a[_K ? ls : rs] = a[k] - a[_K ? rs : ls];\
		b[ls] = b[rs] = b[k];\
		b[k] = -1;\
	} while(0);
	vector<vector<int>> a;
	vector<int> b;
	int build(int k, int l, int r, const string &s) {
		if (l == r) return a[k][s[l - 1] - 'a'] = 1;
		build(Ls, s), build(Rs, s);
		updata
	}
	
//	void pushdown(int k, int l, int r) {
//		if (b[k] == -1) return;
//		bool K = b[k];
//		a[K ? rs : ls] = a[k] - (K ? ls : rs);
//		a[K ? ls : rs] = a[k] - a[K ? rs : ls];
//		b[k] = -1;
//	}
	
// 	int Sort(int k, int l, int r, int L, int R, int K) {
// 		if (l > R || L > r) return 0;
// 		if (l >= L && r <= R) return b[k] = K;
// 		pushdown
// 		Sort(Ls, L, R, K); Sort(Rs, L, R, K);
// //		cout << 1;
// 		updata
// 	}

    int Sort(int k, int l, int r, int L, int R, int K, const vector<int> &s) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return b[k] = K, (a[k] = s)[0];
        pushdown
        vector<int> p = s - (K == 1 ? max(0ll, mid - max(L, l) + 1) : max(0ll, min(R, r) - mid)), q = s - p;
        if (K) {
            Sort(Rs, L, R, K, p);
            Sort(Ls, L, R, K, q);
        } else {
            Sort(Ls, L, R, K, p);
            Sort(Rs, L, R, K, q);
        }
        // Sort(K == 1 ? Rs : Ls, L, R, K, p);
        // Sort(K == 1 ? Ls : Rs, L, R, K, q);
        updata
    }

    vector<int> query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return vector<int>(26, 0);
        if (l >= L && r <= R) return a[k];
        pushdown
        return query(Ls, L, R) + query(Rs, L, R);
    }
	
	void query(int k, int l, int r, string &s) {
		if (l == r) {
			for (int j = 0; j < M; j++) {
				if (a[k][j]) s += j + 'a';
			}
			return;
		}
		pushdown
		query(Ls, s); query(Rs, s);
	}
	
	int n;
	const int M = 26;
public:

	
	SegTree(int N) : n(N) {
		a.assign(n << 2, vector<int>(M, 0));
		b.assign(n << 2, -1);
	}
	
	void build(const string &s) {
		build(1, 1, n, s);
	}
	
	void Sort(int L, int R, int K) {
        vector<int> sum = query(1, 1, n, L, R);
        Sort(1, 1, n, L, R, K, sum);
	}
	
	string query() {
		string s;
		s.clear();
		query(1, 1, n, s);
		return s;
	}
};

signed main() {
	int n, m;
	cin >> n >> m;
	string s;
	cin >> s;
	SegTree a(n);
	a.build(s);
	// cout << a.query() << endl;
	// cout << a.a << endl;
	while (m--) {
		int l, r, x;
		cin >> l >> r >> x;
//		cout << m;
		a.Sort(l, r, x);
		// cout << a.query() << endl;
		// cout << a.a << endl << a.b << endl;
	}
//	cout << 1;
	cout << a.query() << endl;
	return 0;
}
}


signed main() {
	// freopen("in.in", "r", stdin);
	// freopen("out.out", "w", stdout);
	Problem::main();
	return 0;
}