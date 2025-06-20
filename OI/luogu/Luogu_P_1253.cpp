#include <bits/stdc++.h>
#define int long long
#define endl "\n"

using namespace std;

const int inf = 0x3fffffffffffffff;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update return a[k] = max(a[ls], a[rs]);
#define pushdown do { if (c[k]) a[ls] = a[rs] = a[k], b[ls] = b[rs] = b[k] = 0, c[ls] = c[rs] =!(c[k] = 0); else a[ls] += b[k], a[rs] += b[k], b[ls] += b[k], b[rs] += b[k], b[k] = 0; } while (0);
    int n;
    vector<int> a, b, c;
    SegTree(int N) : n(N), a(n << 2, -inf), b(n << 2), c(n << 2) {}
    SegTree(const vector<int> &A) : n(A.size() - 1), a(n << 2), b(n << 2), c(n << 2) { build(1, 1, n, A); }

    int build(int k, int l, int r, const vector<int> &A) {
        if (l == r) return a[k] = A[l];
        build(Ls, A), build(Rs, A);
        update
    }

    int add(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] += x;
        pushdown
        i <= mid ? add(Ls, i, x) : add(Rs, i, x);
        update
    }

    int add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k] += x, b[k] += x;
        pushdown
        add(Ls, L, R, x), add(Rs, L, R, x);
        update
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r || L > R) return -inf;
        if (l >= L && r <= R) return a[k];
		pushdown
		return max(query(Ls, L, R), query(Rs, L, R));
    }

    int query(int k, int l, int r, int i) {
        if (l == r) return a[k];
        pushdown
        return i <= mid ? query(Ls, i) : query(Rs, i);
    }

    int modify(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] = x;
        pushdown
        i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
        update
    }

    int modify(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r || L > R) return 0;
        if (l >= L && r <= R) return a[k] = x, c[k] = 1, b[k] = 0;
        pushdown
        modify(Ls, L, R, x), modify(Rs, L, R, x);
        update
    }
};

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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) cin >> A[i];
    SegTree a(A);
    while (m--) {
        // for (int i = 1; i <= n; i++) {
        //     cerr << a.query(1, 1, n, i) << " ";
        // }
        // cerr << "\n";
        int op, l, r, x;
        cin >> op >> l >> r;
        if (op == 3) cout << a.query(1, 1, n, l, r) << endl;
        else {
            cin >> x;
            if (op == 1) a.modify(1, 1, n, l, r, x);
            else a.add(1, 1, n, l, r, x);
        }
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