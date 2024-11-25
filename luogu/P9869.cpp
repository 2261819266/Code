#include <bits/stdc++.h>
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

int rev(int x) { return x == 2 ? 2 : !x; }

struct Tribool {
    bool know;
    int type, op, base;

    Tribool(int _know = false, int _type = -1, int _op = 1, int _base = 0) :know(_know), type(_type), op(_op), base(_base) {}

    Tribool operator!() {
        if (know) {
            return {know, rev(type), op, base};
        } else {
            return {know, type, -op, base};
        }
    }
};

int solve() {
    int n, m;
    cin >> n >> m;
    vector<Tribool> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i].base = i;
    }
    while (m--) {
        char op;
        int x, y;
        cin >> op >> x;
        if (op < 'A') cin >> y;
        if (op == '+') a[x] = a[y];
        if (op == '-') a[x] = !a[y];
        if (op == 'T') a[x] = {true, 1, 1, x};
        if (op == 'F') a[x] = {true, 0, 1, x};
        if (op == 'U') a[x] = {true, 2, 1, x};
    }

    for (int i = 1; i <= n; i++) cout << a[i].know << spc << a[i].type << spc << a[i].op << spc << a[i].base << endl;
    cout << endl;

    vector<int> start(n + 1, -1), vis(n + 1, 0);

    auto solve = [&](auto &&self, int u, bool ring = false) -> int {
        if (ring) {
            if (start[u] == 2) return 2;
            start[u] = 2;
            return self(self, a[u].base, ring);
        }

        if (start[u] != -1) return start[u];
        if (vis[u]) return start[u] = 0;
        vis[u] = true;
        if (a[u].know) start[u] = a[u].type;
        else if (a[u].base == u) start[u] = a[u].op == -1 ? 2 : 0;
        else {
            int ret = 0;
            if (a[u].op == -1) ret = rev(self(self, a[u].base));
            else ret = self(self, a[u].base);
            if (start[u] != ret && start[u] != -1) start[u] = 2, self(self, a[u].base, true);
            else start[u] = ret;
        }
        return start[u];
    };

    int ans = 0;

    for (int i = 1; i <= n; i++) ans += solve(solve, i) == 2;
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