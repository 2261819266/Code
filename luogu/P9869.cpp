#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <stack>
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

// vector<int> vis, p, f, dep;

// bool dfs(int u, int root, int d = 1) {
//     if (f[u] >= 0) return f[u];
//     vis[u] = root;
//     dep[u] = d;
//     int v = p[u];
//     if(u == v) return false;
//     if (!p[v]) return true;
//     if (vis[v] == root) return f[u] = (dep[u] - dep[v]) % 2 == 0;
//     return f[u] = dfs(v, root, d + 1);
// };

// bool bfs(int s, int root) {
//     if (f[s] >= 0) return f[s];
//     vector<int> st = {s};
//     while (!st.empty()) {
//         int u = st.back();
//         if (vis[u]) {
//             st.pop_back();
//             if (!st.empty()) f[st[st.size() - 1]] = f[u];
//             continue;
//         }
//         vis[u] = root;
//         int v = p[u];
//         if (u == v) f[u] = false;
//         else if (!p[v]) f[u] = true;
//         else if (vis[v]) f[u] = (dep[u] - dep[v]) % 2 == 0;
//         else {
//             st.push_back(v);
//             dep[v] = dep[u] + 1;
//         }
//     }
//     return f[s];
// }

int solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> e(n + 1, vector<int>());

    auto addedge = [&](int u, int v) {
        e[u].push_back(v);
    };
    auto addedge_ = [&](int u, int v) {
        int w = e.size();
        e.push_back({v});
        e[u].push_back(w);
    };
    vector<int> op(n + 1), ok(n + 1), p(n + 1);
    // p.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) p[i] = i;
    while (m--) {
        char c;
        cin >> c;
        if (c == '+' || c == '-') {
            int u, v;
            cin >> u >> v;
            p[u] = p[v];
            op[u] = (c == '-') ^ op[v];
            ok[u] = ok[v];
            if (c == '-' && u == v) {
                p[u] = 0;
            }
            if (p[u] == u && op[u]) p[u] = 0;
        } else {
            int i;
            cin >> i;
            if (c == 'U') {
                ok[i] = 1;
                p[i] = 0;
            } else {
                p[i] = i;
                ok[i] = 1;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (ok[i]) {
            // ans += !p[i];
            continue;
        }
        if (!op[i]) {
            addedge_(i, p[i]);
            addedge_(p[i], i);
        } else {
            addedge(i, p[i]);
            addedge(p[i], i);
        }
    }
    vector<int> vis, f, dep;
    auto dfs = [&](const auto &self, int u, int root, int d = 1) -> bool {
        if (u < p.size() && !p[u]) return f[u] = true;
        if (f[u] > 0) return f[u];
        if (vis[u] == root) return f[u];
        vis[u] = root;
        dep[u] = d;
        f[u] = false;
        for (int v : e[u]) {
            if (f[v]) f[u] |= true;
            // if(u == v) f[u] |= false;
            // else 
            if (v < p.size() && !p[v]) f[u] |= true;
            else if (vis[v] && dep[u] - dep[v] != 1) f[u] |= (dep[u] - dep[v]) % 2 == 0;
            else f[u] |= self(self, v, root, d + 1);
        }
        return f[u];
    };

    vis.assign(e.size(), 0);
    f.assign(e.size(), -1);
    dep.assign(e.size(), 0);
    for (int i = 1; i <= n; i++) {
        ans += dfs(dfs, i, i);
    }
    return ans;
}

void main() {
    int c, t;
    cin >> c >> t;
    while (t--) {
        cout << solve() << endl;
    }
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}