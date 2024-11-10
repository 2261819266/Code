#include <bits/stdc++.h>
#include <functional>
#include <unordered_map>
#include <vector>
#define int long long
#define Problem P1126
#define endl "\n"
#define space " "

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
    for (const t &i : a) out << i;
    return out;
}

using PII = pair<int, int>;

PII operator+(const PII &x, const PII &y) {
    return {x.first + y.first, x.second + y.second};
}

istream &operator>>(istream &in, PII &a) {
    return in >> a.first >> a.second;
}

unordered_map<char, int> mp = {{'N', 0}, {'E', 1}, {'S', 2}, {'W', 3}};
int n, m;
const PII nxt[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// bool check(const PII &p) {
//     int x = p.first, y = p.second;
//     return x >= 0 && y >= 0 && x <= n && y <= m;
// }

bool check(const PII &p) {
    int x = p.first, y = p.second;
    return x > 0 && y > 0 && x < n && y < m;
}

struct state {
    PII a;
    int f;
    int d;

    state operator+(const PII &q) const { return {a + q, f, d}; }

    state operator+=(const PII &q) { return *this = *this + q; }

    operator bool() {
        return check(a);
    }

    state operator*(int x) const { return {a, (f + x + 4) % 4, d}; }

    state operator*=(int x) { return *this = *this * x; }

    state operator+(int x) const { return {a, f, d + 1}; }
    state operator+=(int x) { return *this = {a, f, d + 1}; }
};

// struct Hash {
//     int operator()(state s) { return hash<state>()(s.a); }
// };

vector<vector<vector<int>>> vis;

void main() {
#define VIS(x) vis[x.a.first][x.a.second][x.f]
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
    vis.assign(n + 1, vector<vector<int>>(m + 1, vector<int>(4, 0)));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            if (x) {
                int di = max(0, i - 1);
                int dj = max(0, j - 1);
                a[i][j] = a[i][dj] = a[di][j] = a[di][dj] = 1;
            }
        }
    }
    PII s, t;
    cin >> s >> t;
    queue<state> q;
    char x;
    cin >> x;
    q.push({s, mp[x], 0});
    VIS(q.front()) = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    while (!q.empty()) {
        state u = q.front();
        q.pop();
        // cout << u.a.first << space << u.a.second << space << u.f << space << u.d << endl;
        if (u.a == t) {
            cout << u.d << endl;
            return ;
        }
        for (int i = -1; i <= 1; i += 2) {
            state v = u * i;
            if (!v || VIS(v) || a[v.a.first][v.a.second]) continue;
            VIS(v) = 1;
            q.push(v + 1ll);
        }
        state v = u;
        for (int i = 0; i < 3; i++) {
            v += nxt[u.f];
            if (!v || VIS(v) || a[v.a.first][v.a.second]) break;
            VIS(v) = 1;
            q.push(v + 1ll);
        }
    }
    cout << -1 << endl; 
}
}


signed main() {
    Problem::main();
    return 0;
}
