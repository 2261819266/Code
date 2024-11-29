#ifndef __TREE_DECOMPOSITION__
#define __TREE_DECOMPOSITION__

#include <bits/stdc++.h>
#define int long long
#define endl "\n"

using namespace std;

class TreeDecomposition {
    class SegTree {
    #define ls (k << 1)
    #define rs (ls | 1)
    #define mid ((l + r) >> 1)
    #define Ls ls, l, mid
    #define Rs rs, mid + 1, r
    #define update return a[k] = a[ls] + a[rs], 0;
    #define num (r - l + 1)
    #define lm (mid - l + 1)
    #define rm (r - mid)
        struct Node {
            Node(int _sum = 0, int _mx = 0, int _lazy = 0, int _tag = 0, int _l = 0, int _r = 0) : sum(_sum), mx(_mx), lazy(_lazy), tag(_tag), l(_l), r(_r) {}
            int sum, mx, lazy, tag, l, r;
            Node operator+(const Node &b) const { return {sum + b.sum, max(mx, b.mx), 0, 0, min(l, b.l), max(r, b.r)}; }
        };

        int n;
        vector<Node> a;

        public:
        SegTree() = default;
        SegTree(int N) : n(N), a(n << 2) {}
        SegTree(const vector<int> &data) : n(data.size() - 1), a(n << 2) { build(1, 1, n, data); }
        SegTree(const vector<int> &data, const vector<int> &rnk) : n(data.size() - 1), a(n << 2) { build(1, 1, n, data, [&](int x) { return rnk[x]; }); }
        SegTree(const vector<int> &data, int (*F)(int)) : n(data.size() - 1), a(n << 2) { build(1, 1, n, data, F); }

        int build(int k, int l, int r, const vector<int> &data, function<int(int)> F = [](int x) { return x; }) {
            if (l == r) return a[k] = {data[F(l)], data[F(l)], 0, l, r}, 0;
            build(Ls, data, F), build(Rs, data, F);
            update
        }

        int add(int k, int l, int r, int L, int R, int x) {
            if (l > R || L > r) return 0;
            if (l >= L && r <= R) return a[k] += x * num, b[k] += x, 
        }
    };
};

#undef int
#undef endl
#endif