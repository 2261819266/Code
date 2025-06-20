#include <bits/stdc++.h>
#include <cmath>
#include <istream>
#include <ostream>
#include <vector>

using namespace std;

namespace P11217 {

istream &operator>>(istream &in, __int128 &x) {
    long long y;
    in >> y;
    x = y;
    return in;
}

ostream &operator<<(ostream &out, __int128 x) {
    long long y = x;
    return out << y;
}

#define int long long 
#define endl "\n"


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
#define push_down a[ls] += b[k] * lm, a[rs] += b[k] * rm, b[ls] += b[k], b[rs] += b[k], b[k] = 0;
private:    
    vector<int> a, b;
    int n;
    int modify(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] = x;
        i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
        updata 
    }

    int add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k] += num * x, b[k] += x;
        push_down
        add(Ls, L, R, x), add(Rs, L, R, x);
        updata
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        push_down
        return query(Ls, L, R) + query(Rs, L, R);
    }

    int solve(int k, int l, int r, int w) {
        if (l == r) return a[k] <= w; 
        if (w >= a[k]) return num;
        if (w <= 0) return 0;
        push_down
        return solve(Ls, w) + solve(Rs, w - a[ls]);
    }


    int build(int k, int l, int r, const vector<int> &A) {
        if (l == r) return a[k] = A[l];
        build(Ls, A), build(Rs, A);
        updata
    }

public:

    SegTree(int N) : n(N) {
        a.assign(n << 2, 0);
        b.assign(n << 2, 0);
    }

    void modify(int i, int x) {
        modify(1, 1, n, i, x);
    }

    void add(int L, int R, int x) {
        add(1, 1, n, L, R, x);
    }

    int query(int L, int R) {
        return query(1, 1, n, L, R);
    }

    int solve(int w) {
        if (w > a[1]) return n;
        return solve(1, 1, n, w);
    }

    void build(const vector<int> &A) {
        build(1, 1, n, A);
    }
};

signed test_SegTree_P3372_main() {
    int n, m;
    cin >> n >> m;
    SegTree a(n);
    for (int i = 1;i <= n; i++) {
        int x;
        cin >> x;
        a.modify(i, x);
    }
    while (m--) {
        int k, x, y, z;
        cin >> k >> x >> y;
        if (k == 1) {
            cin >> z;
            a.add(x, y, z);
        } else {
            cout << a.query(x, y) << endl;
        }
    }
    return 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, m, W;
    cin >> n >> m >> W;
    SegTree a(n);
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    a.build(A);
    while (m--) {
        int l, r, x, w = W;
        cin >> l >> r >> x;
        a.add(l, r, x);
        int k = 1, ans = 0;
        if (n > 1e5) {
            int S = a.query(1, n);
            int K = log2(w / S) - 1;
            if (K < 0) K = 0;
            k <<= K;
            w -= S * ((1 << (K)) - 1);
            ans += K * n;
        }
        
        while (w > 0) {
            // int s = 6;
            int s = a.solve(w / k + (bool)(w % k));
            // w -= k * 100;
            if (!s) s = 1;
            if (a.query(1, s) * k < w && s != n) s++;
            ans += s;
            w -= a.query(1, s) * k;
            if (w <= 0) ans--;
            k <<= 1;
        }
        cout << ans << endl;
    }
    return 0;
}

}

signed main() {
    // return P11217::test_SegTree_P3372_main();
    return P11217::main();
}