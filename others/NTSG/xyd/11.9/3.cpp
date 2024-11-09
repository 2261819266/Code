#include <bits/stdc++.h>
#include <vector>
#define int long long
#define Problem polaris
#define endl "\n"
#define space " "
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);

using namespace std;



namespace Problem {
#define max(x, y) ((x) < (y) ? (y) : (x))
template<typename t>
istream &operator>>(istream &in, vector<t> &a) {
    for (t &i : a) in >> i;
    return in;
}

template<typename t>
ostream &operator<<(ostream &out, const vector<t> &a) {
    for (const t &i : a) out << i << " ";
    return out;
}

const int inf = 0x7fffffff;
const int M = 1e9 + 7;

vector<int> V;

void init(int n) {
    V.assign(n + 3, 0);
    V[0] = 1;
    for (int i = 1; i <= n + 2; i++) {
        V[i] = (V[i - 1] * 2) % M;
    }
}

void main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> e(n + 1, vector<int>());
    vector<vector<int>> d(n + 1, vector<int>(n + 1, inf));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int ans = 0;
    init(n);
    for (int i = 1; i <= n; i++) {
        queue<int> q;
        q.push(i);
        d[i][i] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : e[u]) {
                if (d[i][v] == inf) {
                    q.push(v);
                    d[i][v] = d[i][u] + 1;
                }
            }
        }
        // cout << d[i] << endl;
        sort(d[i].begin() + 1, d[i].end());
        for (int j = 1; j <= n; j++) {
            (ans += d[i][j] * V[n  - j]) %= M;
        }
    }
    cout << ans << endl;
}
}


signed main() {
#ifndef LOCAL
    fo(polaris)
#endif
    Problem::main();
    return 0;
}
