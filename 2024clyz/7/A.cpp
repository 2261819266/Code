#include <iostream>
#include <vector>
#define int long long
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

using std::cin;
using std::cout;
using std::vector;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define updata return a[k] = a[ls] + a[rs];
#define num (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)

    vector<int> a, b;
    void assign(int N) {
        a.assign(N << 2, 0);
        b.assign(N << 2, 0);
    }

    SegTree(int N = 1e5 + 8) {
        assign(N);
    }

    void push_down(int k, int l, int r) {
        a[ls] += b[k] * lm;
        a[rs] += b[k] * rm;
        b[ls] += b[k];
        b[rs] += b[k];
        b[k] = 0;
    }

    int add(int k, int l, int r, int L, int R, int x = 1) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k] += x * num, b[k] += x;
        push_down(k, l, r);
        add(Ls, L, R, x);
        add(Rs, L, R, x);
        updata
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        push_down(k, l, r);
        return query(Ls, L, R) + query(Rs, L, R);
    }
};

signed main() {
#ifndef LOCAL
    fo(measure)
#endif
    int n, m, s;
    cin >> n >> m;
    SegTree a(n);
    while (m--) {
        int x, y;
        cin >> x >> y;
        a.add(1, 1, n, x, y);
    }
    s = a.query(1, 1, n, 1, n) / 2;
    for (int i = 1; i <= n; i++) {
        cout << a.query(1, 1, n, i, i) << " ";
    }
    cout << "\n" << s;
}