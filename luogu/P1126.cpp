#include <bits/stdc++.h>
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

istream &operator>>(istream &in, PII &a) {
    return in >> a.first >> a.second;
}

const unordered_map<char, int> mp={{'N', 0}, {'E', 1}, {'S', 2}, {'W', 3}};
struct state {
    PII a;
    int f;
};

void main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
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
    q.push({s, x});
    while (!q.empty()) {
        
    }
}
}


signed main() {
    Problem::main();
    return 0;
}
