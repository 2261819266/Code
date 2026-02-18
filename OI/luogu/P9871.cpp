#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
using PII = pair<int, int>;
const int inf = 0x7ffffffffffff;

struct SegmentTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define updata a[k] = max(a[ls], a[rs]);

    SegmentTree(int l, int r) {
        E = 1 - l;
        n = r - l + 1;
        
        a.resize(n << 2);
        b.resize(n << 2);
    }

  private:
    int n;

    int E;
    vector<int> a, b;

    int modify(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] = x;
        i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
        return updata
    }

    void pushdown(int k, int l, int r) {
        a[ls] += b[k];
        a[rs] += b[k];
        b[ls] += b[k];
        b[rs] += b[k];
        b[k] = 0;
    }

    int add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k] += x, b[k] += x;
        pushdown(k, l, r);
        add(Ls, L, R, x);
        add(Rs, L, R, x);
        return updata
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return -inf;
        if (l >= L && r <= R) return a[k];
        pushdown(k, l, r);
        return max(query(Ls, L, R), query(Rs, L, R));
    }
  public:
    void modify(int i, int x) {
        modify(1, 1, n, i + E, x);
    }

    void add(int L, int R, int x) {
        add(1, 1, n, L + E, R + E, x);
    }

    int query(int L, int R) {
        return query(1, 1, n, L + E, R + E);
    }

    int query(int L) {
        return query(L, L);
    }
#undef mid
};
void solve() {
    int n, m, k, d;
    cin >> n >> m >> k >> d;
    vector<vector<PII>> c(n + 1);
    // vector<vector<int>> f(2, vector<int>(k + 1));
    // vector<SegmentTree> f(n + 1, SegmentTree(-n - 1, k));
    for (int i = 1; i <= m; ++i) {
        int x, y, v;
        cin >> x >> y >> v;
        c[x].push_back({y, v});
    }
    // for (int i = 1; i <= n; ++i) {
        
    //     f[i].modify(0, f[(i - 1)].query(0, k));
       
    //     for (int day = 1; day <= min(i, k); ++day) {
    //         f[i].modify(day, f[(i - 1)].query(day - 1) - d);
    //         // cout << i << " " << day << " OK " << f[i].query(0, 0, k, day) << endl;
    //     }
    //     for (auto pi : c[i]) {
    //         int y = pi.first, v = pi.second;
    //         f[i].add(y, min(i, k), v);
    //     }
    // }
    SegmentTree f(-n - 1, k);
    for (int i = 1; i <= n; i++) {
        int e = 1 - i;
        f.modify(e, f.query(e + 1, e + 1 + k));
        f.add(1 + e, 1 + min(i, k), -d);
        for (auto pi : c[i]) {
            int y = pi.first, v = pi.second;
            f.add(y + e, min(i, k) + e, v);
        }
        // for (int j = e; j <= k + e; j++) {
        //     cout << f.query(j) << " ";
        // }
        // cout << "\n";
    }
    
    int maxv = f.query(-n + 1, k - n + 1);
    cout << maxv << endl;
}

signed main() {
    int c, t;
    cin >> c >> t;
    while (t--) {
        solve();
    }
}