#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem P1074
#define fop fo(P1074)

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

const int n = 9, m = 4;
int a[n][n];

int f(int x, int y) { return 10 - max(abs(x - m), abs(y - m)); }

bool checkX(int x, int y) {
    vector<int> vis(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (a[x][i] && vis[a[x][i]]) return false;
        vis[a[x][i]] = true;
    }
    return true;
}

bool checkY(int x, int y) {
    vector<int> vis(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (a[i][y] && vis[a[i][y]]) return false;
        vis[a[i][y]] = true;
    }
    return true;
}

bool checkChunk(int x, int y) {
    vector<int> vis(n + 1, 0);
    x = x / 3 * 3, y = y / 3 * 3;
    for (int i = x; i < x + 3; i++) {
        for (int j = y; j < y + 3; j++) {
            if (a[i][j] && vis[a[i][j]]) return false;
            vis[a[i][j]] = true;
        }
    }
    return true;
}

bool check(int x, int y) { return checkX(x, y) & checkY(x, y) & checkChunk(x, y); }




int ans = -1;

void update() {
    int y = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            y += f(i, j) * a[i][j];
        }
    }
    if (y > ans) ans = y;
}

void update(int t) {
    if (t > ans) ans = t;
}

vector<int> get(int x, int y) {
    vector<int> vis(n + 1, 0);
    for (int i = 0; i < n; i++) vis[a[x][i]] = vis[a[i][y]] = true;
    x = x / 3 * 3;
    y = y / 3 * 3;
    for (int i = x; i < x + 3; i++) {
        for (int j = y; j < y + 3; j++) {
            vis[a[i][j]]++;
        }
    }
    return vis;
}

int X, Y, vis = 0, Z;
int I;
vector<vector<int>> T(n, vector<int>(9, 0));
vector<vector<vector<int>>> S(n, vector<vector<int>>(9, vector<int>(10, 0)));
vector<PII> A;
map<PII, int> mp;

PII getnext(int x, int y) { return A[mp[{x, y}] + 1]; }

void dfs(int x = 0, int y = 0, int t = 0, const vector<vector<vector<int>>> &P = S) {
    PII nxt = getnext(x, y);
    if (y == -1 && x == -1) update(t);
    else {
        // vis = true;
        if (!a[x][y]) {
            for (int i = 1; i <= n; i++) {
                a[x][y] = i;
                if (!P[x][y][i]) {
                    auto Q = P;
                    for (int j = 0; j < n; j++) Q[x][j][i] = Q[j][y][i] = true;
                    for (int j = x / 3 * 3; j < x / 3 * 3 + 3; j++) {
                        for (int k = y / 3 * 3; k < y / 3 * 3 + 3; k++) {
                            Q[j][k][i] = true;
                        }
                    }
                    dfs(nxt.first, nxt.second, t + f(x, y) * i, Q);
                }
            }
        a[x][y] = 0;
    } else dfs(nxt.first, nxt.second, t, P);
    }
} 

void main() {
    for (auto &i : a) for (auto &j : i) cin >> j;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!check(i, j)) {
                cout << -1;
                return;
            }
        }
    }
    while (true) {
        int k = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (a[i][j]) continue;
                int t = 0, s;
                vector<int> v = get(i, j);
                for (int l = 1; l <= n; l++) {
                    t += !!v[l];
                    if (!v[l]) s = l;
                }
                if (t == n - 1) {
                    k++;
                    a[i][j] = s;
                    // cerr << i << spc << j << spc << s << endl;
                }
                if (t > Z && !a[i][j] && t < n - 1) X = i, Y = j, Z = t;
            }
        }
        if (!k) break;
    }
    
    // for (const auto &i : a) {
    //     for (auto j : i) cout << j << spc;
    //     cout << endl;
    // }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<int> v = get(i, j);
            int t = 0;
            for (int l = 1; l <= n; l++) t += !v[l];
            T[i][j] = t;
            S[i][j] = v;
            // cout << T[i][j] << spc;
        }
        // cout << endl;
    }


    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (T[j][k] == i) mp[{j, k}] = A.size(), A.push_back({j, k});
            }
        }
    }

    int t = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t += a[i][j] * f(i, j);
        }
    }

    A.push_back({-1, -1});
    
    // cerr << clock() << endl;
    dfs(A.front().first, A.front().second, t, S);
    cout << ans << endl;
    // cerr << clock() << endl;
}
}

signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}