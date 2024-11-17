#include <bits/stdc++.h>

using namespace std;
#define int long long
const int inf = 0x3f3f3f3f3f3f3f3f;
struct File {
    int s, t, id;
    bool operator<(const File &b) const { return t < b.t; }
};
struct Printer {
    int wt = inf, id = inf;
    inline void shake() { wt = max(wt, 0ll); }
    bool operator<(const Printer &b) const {
        return wt == b.wt ? id < b.id : wt < b.wt;
    }
    void operator+=(int p) { wt += p; }
};
inline Printer &min(Printer &a, Printer &b) { return a < b ? a : b; }
class SegmentTree {
#define mid ((l + r) >> 1)
#define ls p << 1
#define rs p << 1 | 1
    int n;
    vector<Printer> tree;
    vector<int> lazy;
    inline void pushup(int p) {
        tree[ls].shake(), tree[rs].shake();
        tree[p] = min(tree[ls], tree[rs]);
        tree[p].shake();
    }
    inline void pushdown(int p, int l, int r) {
        tree[ls] += lazy[p];
        tree[rs] += lazy[p];
        tree[ls].shake(), tree[rs].shake();
        lazy[ls] += lazy[p], lazy[rs] += lazy[p];
        lazy[p] = 0;
    }
    void modify(int p, int l, int r, int L, int R, int v) {
        if (l > R || r < L) return;
        if (L <= l && r <= R) {
            lazy[p] += v;
            tree[p] += v;
            tree[p].shake();
            return;
        }
        pushdown(p, l, r);
        modify(ls, l, mid, L, R, v);
        modify(rs, mid + 1, r, L, R, v);
        pushup(p);
    }
    Printer query(int p, int l, int r, int L, int R, bool flag = 0) {
        if (l > R || r < L) {
            return Printer();
        }
        if (flag == 1 && L <= l && r <= R) {
            tree[p].shake();
            return tree[p];
        }
        if (l == r) {
            tree[p].shake();
            return tree[p];
        }
        pushdown(p, l, r);
        auto res = tree[ls].wt;
        return min(query(ls, l, mid, L, R, res > 0), query(rs, mid + 1, r, L, R, res <= 0));
    }

    void build(int p, int l, int r) {
        if (l == r) {
            tree[p].wt = 0;
            tree[p].id = l;
            return;
        }
        build(ls, l, mid), build(rs, mid + 1, r);
        pushup(p);
    }

  public:
    SegmentTree(int n_) : n(n_) {
        tree.resize(n << 2);
        lazy.resize(n << 2);
        build(1, 1, n);
    }
    inline void modify(int x, int v) { modify(1, 1, n, x, x, v); }
    inline void modify(int l, int r, int v) { modify(1, 1, n, l, r, v); }
    inline Printer query(int l, int r) { return query(1, 1, n, l, r); }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<File> file(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> file[i].s >> file[i].t;
        file[i].id = i;
    }
    sort(file.begin() + 1, file.end());
    SegmentTree sgt(m);
    vector<vector<int>> out(m + 1);
    for (int i = 1; i <= n; ++i) {
        sgt.modify(1, m, -(file[i].t - file[i - 1].t));
        auto [wt, id] = sgt.query(1, m);
        out[id].push_back(file[i].id);
        sgt.modify(id, file[i].s);
    }
    for (int i = 1; i <= m; ++i) {
        cout << out[i].size() << " ";
        sort(out[i].begin(), out[i].end());
        for (auto v : out[i]) {
            cout << v << " ";
        }
        cout << "\n";
    }
    cerr << clock();
    return 0;
}