#include <bits/stdc++.h>
using namespace std;

namespace wxyt {
#define int __int128
struct SegmentTree {
#define mid ((l + r) >> 1)
    int n;
    int rt = 1;

    vector<int> tree;
    vector<int> lazy;
    SegmentTree(int node) : n(node) {
        tree.resize(n << 2);
        lazy.resize(n << 2);
    }

    void pushup(int p) { tree[p] = tree[p << 1] + tree[p << 1 | 1]; }

    void pushdown(int p, int l, int r) {
        if (lazy[p] == 0)
            return;
        lazy[p << 1] += lazy[p];
        lazy[p << 1 | 1] += lazy[p];
        tree[p << 1] += (mid - l + 1) * lazy[p];
        tree[p << 1 | 1] += (r - mid) * lazy[p];
        lazy[p] = 0;
    }

    void build(int p, int l, int r, vector<long long>& a) {
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        pushup(p);
    }

    void modify(int p, int l, int r, int L, int R, int v) {
        if (l > R || r < L)
            return;
        if (L <= l && r <= R) {
            lazy[p] += v;
            tree[p] += (r - l + 1) * v;
            return;
        }
        pushdown(p, l, r);
        modify(p << 1, l, mid, L, R, v);
        modify(p << 1 | 1, mid + 1, r, L, R, v);
        pushup(p);
    }

    int query(int p, int l, int r, int L, int R) {
        if (l > R || r < L)
            return 0;
        if (L <= l && r <= R)
            return tree[p];
        pushdown(p, l, r);
        return query(p << 1, l, mid, L, R) +
               query(p << 1 | 1, mid + 1, r, L, R);
    }

#undef mid
};
__int128 x0 = 1;
int sigma(int x) {
    return (x0 << x) - 1;
}
bool check(int x, int sum, int w) {
    return sigma(x) * sum < w;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    long long n, q, W;
    cin >> n >> q >> W;
    vector<long long> a(n + 1);
    SegmentTree t(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    t.build(t.rt, 1, n, a);
    while (q--) {
        long long x, y, d;
        cin >> x >> y >> d;
        t.modify(t.rt, 1, n, x, y, d);

        int sum = t.query(t.rt, 1, n, 1, n);
        int l = 1, r = 64;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (check(mid, sum, W)) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }

        int ans = (r - 1) * n, twice = r - 1;
        int less = sigma(twice + 1) * sum - W;
        // cout << less << " " << twice << endl;
        // for (int i = n; i >= 1; --i) {
        //     int s = t.query(t.rt, 1, n, i + 1, n);
        //     // cout << s * (twice + 1) << endl;
        //     if (s * (x0 << twice) > less) {
        //         cout << (long long)(ans + i) << endl;
        //         break;
        //     }
        // }
        // if (flag) {
        //     cout << ans << endl;
        // }
        l = 1, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            int s = t.query(t.rt, 1, n, mid + 1, n);
            if (s * (x0 << twice) > less) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        cout << (long long)(ans + r - 1) << endl;
    }
    return 0;
}
#undef int
};  // namespace wxyt

int main() {
    return wxyt::main();
}