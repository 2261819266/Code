#include <iostream>
#include <vector>
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::swap;

vector<int> f, s, p, v, d;

void init(int u) {
    if (!s[u] || ! d[u]) {
        init(f[u]);
        s[u] = s[f[u]] + v[u];
        d[u] = d[f[u]] + 1;
    }
}

int getLCA(int u, int V) {
    if (d[u] < d[V]) swap(u, V);
    while (d[u] > d[V]) u = f[u];
    while (u != V) u = f[u], V = f[V];
    return u;
}

int F(int U, int V, int x) {
    int l = getLCA(U, V);
    int ans = (x >= p[l]) * v[l];
    for (int i = U; i != l; i = f[i]) ans += (x >= p[i]) * v[i];
    for (int i = V; i != l; i = f[i]) ans += (x >= p[i]) * v[i];
    return ans;
}

signed main() {
    
#ifndef LOCAL
    fo(war)
#endif
    int n, q;
    cin >> n >> q;
    f.assign(n + 1, 0);
    s.assign(n + 1, 0);
    p.assign(n + 1, 0);
    v.assign(n + 1, 0);
    d.assign(n + 1, 0);
    for (int i = 1; i < n; i++) {
        int U, V;
        cin >> U >> V;
        if (U < V) swap(U ,V);
        f[U] = V;
    }
    for (int i = 1; i <= n; i++) {
        cin >> p[i] >> v[i];
    }
    d[1] = 1;
    s[1] = v[1];
    for (int i = 1; i <= n; i++) {
        init(i);
    }
    while (q--) {
        int U, V, W;
        cin >> U >> V >> W;
        int l = getLCA(U, V);
        
        int L = 0, R = 1e18 + 100;
        while (L < R) {
            int mid = ((L + R) >> 1);
            if (F(U, V, mid) >= W) {
                R = mid;
            } else {
                L = mid + 1;
            }
        }
        if (L > 1e18) {
            cout << "Impossible\n";
        } else cout << L << "\n";
    }
}