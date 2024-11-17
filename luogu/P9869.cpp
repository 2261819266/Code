#include <bits/stdc++.h>
#include <queue>
#include <vector>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem P9869
#define fop fo(P9869)

using namespace std;

namespace Problem {
template <typename t>
ostream &operator<<(ostream &out, const vector<t> &A) {
    for (const t &i : A) out << i << spc;
    return out;
}

template <typename t>
void print(const t &x, int l = 0, int r = 0) {
    cout << x << spc;
}

template <typename t>
void print(const vector<t> &A, int l = 0, int r = 0) {
    for (int i = l; i < r; i++) {
    print(A[i], l, r);
    }
    cout << endl;
}

template <typename t>
istream &operator>>(istream &in, vector<t> &A) {
    for (t &i : A) in >> i;
    return in;
}

template<typename t>
void scan(t &x, int l = 0, int r = 0) {
    cin >> x;
}

template<typename t>
void scan(vector<t> &A, int l = 0, int r = 0) {
    for (int i = l; i < r; i++) {
    scan(A[i], l, r);
    }
}

template<typename it>
void assign(vector<int> &a, it p) {
    a.assign(*p, 0);
}

template<typename T, typename it>
void assign(vector<T> &a, it p) {
    T t;
    assign(t, p + 1);
    a.assign(*p, t);
}

template<typename T>
void assign(vector<T> &a, const vector<int> &p) {
    assign(a, p.begin());
}

using PII = pair<int, int>;

istream &operator>>(istream &in, PII &a) {
    return in >> a.first >> a.second;
}

ostream &operator<<(ostream &out, const PII &a) {
    return out << a.first << spc << a.second << spc;
}

int solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<PII>> e(n + 1);
    vector<int> p(n + 1), val(n + 1); // TFU 123
    for (int i = 1; i <= n; i++) p[i] = i;
    auto addedge = [&](int u, int v, int w) -> void {
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    };

    auto newnode = [&](int u) -> int {
        p[u] = e.size();
        e.push_back(vector<PII>());
        val.push_back(0);
        return p[u];
    };

    while (m--) {
        char c;
        int u, v;
        cin >> c >> u;
        u = newnode(u);
        if (c == '-' || c == '+') {
            cin >> v;
            addedge(u, p[v], c == '-');
        } else {
            val[u] = (c == 'T' ? 1 : c == 'F' ? 2 : 3);
        }
    }
    for (int i = 1; i <= n; i++) addedge(i, p[i], 0);
    vector<int> f(e.size(), -1), g(e.size(), 0), vis(e.size());
    int ans = 0;

    auto bfs = [&](int s) -> bool {
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            // if (vis[u]) continue;
            // vis[u] = true;
            for (PII to : e[u]) {
                int v = to.first, w = to.second;
                if (!vis[v]) {
                    vis[v] = true;
                    g[v] = g[u] ^ w;
                } else if (g[v] ^ g[u] ^ w) return true;
            }
        }
        return false;
    };

    vector<int> updvis(e.size());

    auto update = [&](int s) -> void {
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (PII to : e[u]) {
                int v = to.first;
                f[v] = f[s];
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (f[i] >= 0) {
            ans += f[i];
            continue;
        }
        ans += f[i] = bfs(i);
        if (f[i] >= 0) update(i);
    }
    return ans;
}

void main() {
    int c, T;
    cin >> c >> T;
    while (T--) {
        cout << solve() << endl;
    }
    return;
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}