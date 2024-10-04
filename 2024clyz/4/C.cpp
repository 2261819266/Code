#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;
#define int long long
const int MOD = 998244353;
struct SegmentTree {
#define mid ((l + r) >> 1)
    int n;
    vector<int> nodes;
    vector<int> lazy;
    void pushup(int p) { nodes[p] = (nodes[p << 1] + nodes[p << 1 | 1]) % MOD; }
    void pushdown(int p, int l, int r) {
        if (lazy[p] == 0)
            return;
        lazy[p << 1] += lazy[p];
        lazy[p << 1 | 1] += lazy[p];
        nodes[p << 1] += lazy[p] * (mid - l + 1);
        nodes[p << 1 | 1] += lazy[p] * (r - mid);
        lazy[p] = 0;
    }
    void modify(int p, int l, int r, int L, int R, int v) {
        if (p == 0)
            p++, l++, r += n, L += n, R += n;
        if (r < L || l > R) {
            return;
        }
        if (L <= l && r <= R) {
            nodes[p] += v * (r - l + 1);
            lazy[p] += v;
            return;
        }
        pushdown(p, l, r);
        modify(p << 1, l, mid, L, R, v);
        modify(p << 1 | 1, mid + 1, r, L, R, v);
        pushup(p);
    }
    void set(int p, int l, int r, int x, int v) {
        if (p == 0)
            p++, l++, r += n, x += n;
        if (l == r) {
            nodes[p] = v;
            return;
        }
        pushdown(p, l, r);
        if (x <= mid) {
            set(p << 1, l, mid, x, v);
        } else {
            set(p << 1 | 1, mid + 1, r, x, v);
        }
        pushup(p);
    }
    int query(int p, int l, int r, int L, int R) {
        if (p == 0)
            p++, l++, r += n, L += n, R += n;
        if (r < L || l > R) {
            return 0;
        }
        if (L <= l && r <= R) {
            return nodes[p];
        }
        pushdown(p, l, r);
        return (query(p << 1, l, mid, L, R) % MOD +
                query(p << 1 | 1, mid + 1, r, L, R) % MOD) %
               MOD;
    }
    SegmentTree(int n_) : n(n_) {
        nodes.resize(n << 2);
        lazy.resize(n << 2);
    }
    void build(int p, int l, int r, int a[]) {
        if (l == r) {
            nodes[p] = a[l];
            return;
        }
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        pushup(p);
    }
#undef mid
};

const int N = 5e5 + 10;

struct Query {
    int op, l, r;
} q[N];

int a[N];
int n, m;

void solve5000() {
    for (int i = 1; i <= m; ++i) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            for (int j = l; j <= r; ++j) {
                a[j] = a[j] * a[j] % MOD;
            }
        } else {
            int cnt = 0;
            for (int j = l; j <= r; ++j) {
                cnt += a[j];
                cnt %= MOD;
            }
            cout << cnt << "\n";
        }
    }
    exit(0);
}
int binpow(int a, int b) {
    int res = a;
    while (b) {
        if (b & 1)
            res = res * a % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}
int tot[N];
void solve1() {
    int t = 1;
    for (int i = 1; i <= m; ++i) {
        if (q[i].op == 2) {
            t = i;
            break;
        }
        tot[q[i].l] += 1, tot[q[i].r + 1] -= 1;
    }
    for (int i = 1; i <= n; ++i) {
        tot[i] = tot[i] + tot[i - 1];
        a[i] = binpow(a[i], tot[i]);
    }
    for (int i = 1; i <= n; ++i) {
        a[i] = a[i] + a[i - 1];
    }
    for (int i = t; i <= m; ++i) {
        cout << a[q[i].r] - a[q[i].l - 1] << "\n";
    }
    exit(0);
}

void solve3() {
    SegmentTree tree(n);
    tree.build(1, 1, n, a);
    for (int i = 1; i <= m; ++i) {
        if (q[i].op == 1) {
            int x = tree.query(1, 1, n, q[i].l, q[i].r);
            x = (x * x) % MOD;
            tree.set(1, 1, n, q[i].l, x);
        } else {
            cout << tree.query(1, 1, n, q[i].l, q[i].r) << "\n";
        }
    }
    exit(0);
}
void solve4() {
    SegmentTree tree(n);
    tree.build(1, 1, n, a);
    for (int i = 1; i <= m; ++i) {
        if (q[i].op == 1) {
            tree.modify(1, 1, n, q[i].l, q[i].r, 1);
        } else {
            cout << binpow(a[q[i].l], 1 << tree.query(1, 1, n, q[i].l, q[i].r)) << "\n";
        }
    }
    exit(0);
}

signed main() {
    freopen("rsrs.in", "r", stdin);
    freopen("rsrs.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    if (n <= 5000) {
        solve5000();
    }
    bool flag1 = 1, flag3 = 1, flag4 = 1;
    for (int i = 1; i <= m; ++i) {
        int op, l, r;
        cin >> op >> l >> r;
        q[i] = {op, l, r};
        if (q[i - 1].op == 2 && q[i].op == 1) {
            flag1 = false;
        }
        if (op == 1 && l != r) {
            flag3 = 0;
        }
        if (op == 2 && l != r) {
            flag4 = 0;
        }
    }
    if (flag1) {
        solve1();
    }
    if (flag3) {
        solve3();
    }
    if (flag4) {
        solve4();
    }
    return 0;
}