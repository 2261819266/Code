#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using ll = long long;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update a[k] = a[ls] + a[rs];
#define lm (mid - l + 1)
#define rm (r - mid)
#define num (r - l + 1)
#define pushdown                                                    \
	do {                                                            \
		a[ls] += b[k] * lm, a[rs] += b[k] * rm, b[ls] += b[k], b[rs] += b[k]; \
		b[k] = 0;                                                   \
	} while (false)

	vector<ll> a, b;
    SegTree(int n) {
        a.assign(n << 2, 0);
        b.assign(n << 2, 0);
    }

    ll build(int k, int l, int r, const vector<ll> &data) {
        if (l == r) return a[k] = data[l];
        return a[k] = build(Ls, data) + build(Rs, data);
    }

    ll add(int k, int l, int r, int L, int R, ll x) {
        if (l > R || L > r) return a[k];
        if (l >= L && r <= R) return b[k] += x, a[k] += x * num;
        pushdown;
        return a[k] = add(Ls, L, R, x) + add(Rs, L, R, x);
    }

    ll query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        pushdown;
        return query(Ls, L, R) + query(Rs, L, R);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<ll> data(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> data[i];
    }
    SegTree a(n);
    a.build(1, 1, n, data);
    while (m--) {
        int op, l, r;
        ll x;
        cin >> op >> l >> r;
        op == 1 ? cin >> x, a.add(1, 1, n, l, r, x) : 
            (cout << a.query(1, 1, n, l, r) << "\n", 0ll);
    }
    return 0;
}