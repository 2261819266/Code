#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::min;
using std::set;

static const int inf = 0x3fffffff;

template<typename t = long long>
struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update return a[k] = min(a[ls], a[rs]);
#define num (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)
	vector<t> a, b;
	int n;
	SegTree(const int N = 1) {
		assign(N);
	}

	void assign(const int N) {
		n = N;
		a.assign(n << 2, inf);
		b.assign(n << 2, inf);
	}

	t modify(int k, int l, int r, int i, t x) {
		if (l == r) return a[k] = x;
		i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
		update
	}

    t del(int i) {
        return modify(1, 1, n, i, inf);
    }

    t modify(int i, t x) {
        return modify(1, 1, n, i, abs(x));
    }

    t query() {
        return query(1, 1, n, 1, n);
    }

	t query(int k, int l, int r, int L, int R) {
		if (l > R || L > r) return 0;
		if (l >= L && r <= R) return a[k];
		return min(query(Ls, L, R),  query(Rs, L, R));
	}
#undef ls
#undef rs
#undef mid
#undef Ls
#undef Rs 
#undef update
#undef num
#undef lm
#undef rm
};

int ans = 0x7fffffff;
set<int> st1, st2;

void update(int x) {
    if (!st1.empty()) {
        auto P = st1.lower_bound(x);
        auto Q = st2.lower_bound(-x);
        if (P == st1.end()) P--;
        if (Q == st2.end()) Q--;
        int p = *P;
        int q = *Q;
        ans = min(ans, abs(p - x));
        ans = min(ans, abs(q + x));
    }
    st1.insert(x); 
    st2.insert(-x);
}

int main() {
    int n, m;
    cin >> n >> m;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    vector<vector<int>> a(n), b(n, vector<int>(1));
    for (vector<int> &i : a) {
        int x;
        cin >> x;
        i.push_back(x);
        update(x);
    }
    SegTree<int> delta(n + m);
    int cnt = n;
    b[0][0] = 1;
    for (int i = 1; i < n; i++) {
        delta.modify(i, a[i][0] - a[i - 1][0]);
        b[i][0] = i + 1;
    }
    const string s1 = "INSERT", s2 = "MIN_GAP", s3 = "MIN_SORT_GAP";
    while (m--) {
        string s;
        cin >> s;
        if (s == s1) {
            int x, y;
            cin >> x >> y;
            delta.modify(b[x][0], y - a[x][0]);
            x--;
            b[x].push_back(++cnt);
            delta.modify(cnt, y - a[x].back());
            update(y);
            a[x].push_back(y);
        } 
        if (s == s2) {
            cout << delta.query() << "\n";
        }
        if (s == s3) {
            cout << ans << "\n";
        }
    }
}