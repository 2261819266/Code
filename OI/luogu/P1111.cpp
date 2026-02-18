#include <iostream>
#include <algorithm>
#include <vector>

struct Edge {
    int u, v, w;
    bool operator<(const Edge &b) const {
        return w < b.w;
    }
};

using std::cin;
using std::cout;
using std::vector;
using std::sort;

vector<Edge> a;
vector<int> f;

int getf(int x) {
    if (f[x] == x) return x;
    return f[x] = getf(f[x]);
}

int main() {
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        a.push_back({u, v, w});
    }
    sort(a.begin(), a.end());
    f.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        f[i] = i;
    }
    int x = n - 1, ans = 0;
    for (Edge e : a) {
        int u = e.u, v = e.v, w = e.w;
        if (getf(u) != getf(v)) {
            f[getf(u)] = getf(v);
            x--;
        }
        ans = w;
        if (!x) 
            break;
    }
    if (x) cout << "-1\n";
    else cout << ans << "\n";
}
