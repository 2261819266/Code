#include <bits/stdc++.h>
#include <ctime>
#define int long long
#define endl "\n"

using namespace std;

template<typename T>
void assign(int n, T &x) {
    x.assign(n, {});
}

template<typename T, typename ...Args>
void assign(int n, T &x, Args &...y) {
    assign(n, x);
    assign(n, y...);
}

inline void init() {
    return;
}

const int inf = 0x3fffffffffffffff;
using PII = pair<int, int>;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update return a[k] = min(a[ls], a[rs]), (c[k] = a[ls] > a[rs] ? c[rs] : c[ls]), s[k] = (a[ls] == a[rs] ? s[ls] + s[rs] : (a[ls] > a[rs] ? s[rs] : s[ls])), 0;
#define pushdown a[ls] += b[k], a[rs] += b[k], b[ls] += b[k], b[rs] += b[k], b[k] = 0;
    int n;
    vector<int> a, b, c, s;
    SegTree(const vector<int> &A) : n(A.size() - 1), a(n << 2, inf), b(n << 2, 0), c(n << 2, 0), s(n << 2, 0) { build(1, 1, n, A); }

    int build(int k, int l, int r, const vector<int> &A) {
        if (l == r) return a[k] = A[l], c[k] = l, s[k] = 1;
        build(Ls, A), build(Rs, A);
        update
    }

    int add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k] += x, b[k] += x;
        pushdown
        add(Ls, L, R, x), add(Rs, L, R, x);
        update
    }

    PII query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return {inf, 0};
        if (l >= L && r <= R) return {a[k], c[k]};
        pushdown
        return min(query(Ls, L, R), query(Rs, L, R));
    }

    PII querys(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return {inf, 0};
        if (l >= L && r <= R) return {a[k], s[k]};
        pushdown
        PII x = querys(Ls, L, R), y = querys(Rs, L, R);
        return x.first == y.first ? (PII){x.first, x.second + y.second} : min(x, y);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a;
    assign(n + 1, a);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegTree sgt(a);









    auto dfs = [&](auto &&self, int l, int r) -> int {
        if (l > r) return 0;
        // if (l == r) return a[l] > 0;
        int mn = a[l], t = l, s = 0;
        // for (int i = l; i <= r; i++) {if (a[i] < mn) mn = a[i], t = i; s += !a[i];}
        // for (int i = l; i <= r; i++) {
        //     a[i] -= mn;
        // }
        PII p = sgt.query(1, 1, n, l, r);
        mn = p.first, t = p.second;
        sgt.add(1, 1, n, l, r, -mn);
        s = sgt.querys(1, 1, n, l, r).second;
        return min(r - l + 1 - s * !mn, self(self, l, t - 1) + self(self, t + 1, r) + mn);
    };
    cout << dfs(dfs, 1, n) << endl;
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
