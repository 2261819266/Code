#include <iostream>
#define int long long
#define endl "\n"

using namespace std;

inline void init() {
    return;
}

const int maxn = 1e5 + 8;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update return a[k] = a[ls] + a[rs];
#define num (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)
#define pushdown a[ls] += b[k] * lm, a[rs] += b[k] * rm, b[ls] += b[k], b[rs] += b[k], b[k] = 0;
    int a[maxn << 2], b[maxn << 2];
    int build(int k, int l, int r, int *A) {
        if (l == r) return a[k] = A[l];
        build(Ls, A), build(Rs, A);
        update
    }

    int add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k] += x * num, b[k] += x;
        pushdown
        add(Ls, L, R, x), add(Rs, L, R, x);
        update
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        pushdown
        return query(Ls, L, R) + query(Rs, L, R);
    }
} a;

int A[maxn];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    a.build(1, 1, n, A);
    while (m--) {
        int k, l, r, x;
        cin >> k >> l >> r;
        if (k == 1) cin >> x, a.add(1, 1, n, l, r, x);
        else cout << a.query(1, 1, n, l, r) << endl;
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