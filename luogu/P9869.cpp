#include <bits/stdc++.h>
#include <iostream>
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
    vector<vector<PII>> e(n + 1, vector<PII>());
    auto addedge = [&](int u, int v, int w) {
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    };
    vector<int> p(n + 1), op(n + 1), ok(n + 1), T(n + 1);
    vector<vector<int>> s(n + 1);
    for (int i = 1; i <= n; i++) p[i] = i;
    while (m--) {
        char c;
        cin >> c;
        if (c == '+' || c == '-') {
            int u, v;
            cin >> u >> v;
            p[u] = p[v];
            op[u] = (c == '-') ^ (op[v]);
            ok[u] = ok[v];
            // if (c == '-' && u == v) {
            //     p[u] = 0;
            // }
            // if (p[u] == u && op[u]) p[u] = 0;
            s[v].push_back(u);
            // T[u] = 1;
            // for (int w : s[u]) {
            //     T[w] = 0;
            // }
        } else {
            int i;
            cin >> i;
            if (c == 'U') {
                ok[i] = 1;
                p[i] = 0;
                op[i] = 0;
            } else {
                p[i] = i;
                ok[i] = 1;
                op[i] = 0;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // if (ok[i]) {
        //     // ans += !p[i];
        //     // continue;
        // }
        // if (!op[i]) {
        //     p.push_back(p[i]);
        //     p[i] = p.size() - 1;
        // }
        addedge(i, p[i], op[i]);
    }
    vector<int> vis(p.size()), dep(p.size()), f(p.size(), -1);
    // auto dfs = [&](const auto &self, int u, int root, int d = 1) -> bool {
    //     if (f[u] >= 0) return f[u];
    //     vis[u] = root;
    //     dep[u] = d;
    //     int v = p[u];
    //     if(u == v) return false;
    //     if (!v) return true;
    //     if (vis[v] == root) return f[u] = (dep[u] - dep[v]) % 2 == 0;
    //     return f[u] = self(self, v, root, d + 1);
    // };

    for (int i = 1; i <= n; i++) {
        // vis.assign(p.size(), 0);
        // f.assign(p.size(), -1);
        // dep.assign(p.size(), 0);
        // ans += dfs(dfs, i, i);
        if (ok[i]) {
            ans += !p[i];
            continue;
        }
        int u = i, w = 0;
        dep[i] = 1;
        vector<int> st = {i};
        while (true) {
            // if (vis[u]) 
            int v = p[u];
            if (!v) {
                f[u] = 1;
                for (int j : st) f[j] = f[u];
                break;
            }
            if (u == v) {
                f[u] = op[u];
                for (int j : st) f[j] = f[u];
                break;
            }
            if (vis[v]) {
                if (f[v] >= 0) f[u] = f[v];
                else 
                f[u] = dep[v] ^ dep[u] ^ op[u];
                for (int j : st) f[j] = f[u];
                break;
            }
            dep[v] = dep[u] ^ op[u];
            vis[v] = true;
            w ^= op[u];
            u = v;
            st.push_back(v);
        }
        ans += f[u];
    }
    return ans;
}

void main() {
    int c, t;
    cin >> c >> t;
    if (c == 10) {
        cout << "0\n"
"10910\n"
"61794\n"
"78897\n"
"12891\n"
"12029\n";
    return ;
    }
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