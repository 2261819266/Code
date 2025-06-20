#include <bits/stdc++.h>
#include <vector>
#define int long long
#define Problem C
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

using PII = pair<int, int>;

PII operator+(const PII &x, const PII &y) {
    return {x.first + y.first, x.second + y.second};
}

const PII &operator+=(PII &x, const PII &y) {
    return x = x + y;
}

const PII nxt[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const PII sc[12] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {2, 0}, {0, 2}, {-2, 0}, {0, -2}, {1, 1}, {-1, 1}, {-1, 1}, {-1, -1}};
int n, m;

bool check(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

bool check(const PII &x) {
    return check(x.first, x.second);
}

void main() {
#define F(x) f[(x).first][(x).second]
    cin >> n >> m;
    vector<vector<int>> a(n, (vector<int>(m, 0))), f;
    f = a;
    int cnt = 0;
    cin >> a;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (f[i][j] || a[i][j] == -1) continue;
            queue<PII> q;
            q.push({i, j});
            cnt++;
            f[i][j] = cnt;
            while (!q.empty()) {
                PII u = q.front();
                q.pop();
                for (PII k: nxt) {
                    k += u;
                    if (check(k) && a[k.first][k.second] != -1 && !f[k.first][k.second]) f[k.first][k.second] = cnt, q.push(k);
                }
            }
        }
    }
    // for (const vector<int> i : f) {
    //     // cout << i << endl;
    //     for (int j : i) {
    //         cout << j << "\t";
    //     }
    //     cout << endl;
    // }
    vector<int> c(cnt + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[f[i][j]] += a[i][j];
        }
    }
    c[0] = 0;
    if (!cnt) { cout << 0; return; }
    if (cnt == 1) { cout << c[1]; return; }
    // sort(c.begin(), c.end(), [](int x, int y) { return x > y; });
    // cout << c[0] + c[1];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // cout << c[f[i][j]] << "\t";
            if (a[i][j] >= 0) continue;
            for (PII p : nxt) {
                p += {i, j};
                for (PII q : nxt) {
                    q += {i, j};
                    if (check(p) && check(q) && F(p) != F(q)) ans = max(ans, c[F(p)] + c[F(q)]);
                }
            }
        }
        // cout << endl;
    }
    cout << ans;
}
}


signed main() {
#ifndef LOCAL
    fo(C)
#endif
    Problem::main();
    return 0;
}
