#include <bits/stdc++.h>
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

template<typename T> vector<T> operator+(const vector<T> &A, const vector<T> &B) {
    int n = A.size(), m = B.size(), k = max(m, n);
    vector<T> C(k, 0);
    for (int i = 0; i < k; i++) {
        if (i < n) C[i] += A[i];
        if (i < m) C[i] += B[i];
    }
    return C;
}

template<typename T> vector<T> operator+=(vector<T> &A, const vector<T> &B) { return A = A + B; }

int solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<PII>> e(n + 1, vector<PII>());
    vector<int> p(n + 1, 0), U(n + 1, 0);
    for (int i = 1; i <= n; i++) p[i] = i;

    auto new_node = [&](int x) -> int {
        p[x] = e.size();
        e.push_back(vector<PII>());
        return p[x];
    };

    auto addedge = [&](int u, int v, int w) {
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    };

    while (m--) {
        char c;
        int u, v;
        cin >> c >> u;
        if (c < 'A') {
            cin >> v;
            if (u == v) {
                if (c == '-') U[u] = 1;
                continue;
            }
            U[u] = U[v];
            u = new_node(u), v = p[v];
            addedge(u, v, c == '-');
        } else {
            U[u] = c == 'U';
            new_node(u);
        }
    }

    for (int i = 1; i <= n; i++) addedge(i, p[i], 0);

    vector<int> vis(e.size(), 0), dis(e.size(), 0), vs(e.size(), 0);

    auto dfs = [&](auto &&self, int u) -> bool {
        vis[u] = true;
        if (u <= n && U[u]) return false;
        for (PII P : e[u]) {
            int v = P.first, w = P.second;
            if (vis[v]) {
                if ((dis[u] + w - dis[v]) % 2) return false;
                continue;
            }
            dis[v] = dis[u] + w;
            if (!self(self, v)) return false;
        }
        return true;
    };

    auto update = [&](auto &&self, int u) -> void {
        vs[u] = true;
        for (PII P : e[u]) {
            int v = P.first;
            if (v <= n) U[v] = 1;
            if (vs[v]) continue;
            self(self, v);
        }
    };

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        if (vis[i] && (!U[i] || vs[i])) continue;
        if (!dfs(dfs, i) || U[i]) {
            U[i] = 1;
            update(update, i);
        }
    }

    for (int i = 1; i <= n; i++) {
        ans += U[i];
    }
    return ans;
}


void main() {
    int c, T;
    cin >> c >> T;
    while (T--) {
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