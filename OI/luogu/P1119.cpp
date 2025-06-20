#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::min;

vector<int> T;
struct Edge { int v, w; };
vector<vector<Edge>> E;
const int inf = 0x3fffffff;

int main() {
    int n, m, q;
    cin >> n >> m;
    T.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> T[i];
    }
    E.assign(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u++, v++;
        E[u].push_back({v, w});
        E[v].push_back({u, w});
    }
    cin >> q;
    int now = 0;
    vector<vector<vector<int>>> f(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, inf)));
    for (int i = 1; i <= n; i++) {
        f[0][i][i] = 0;
        for (Edge e : E[i]) {
            f[0][i][e.v] = e.w;
        }
    }
    while (q--) {
        int x, y, t;
        cin >> x >> y >> t;
        x++, y++;
        if (t < T[1]) {
            cout << "-1\n";
            continue;
        }
        while (now < n && t >= T[now + 1]) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    f[now + 1][i][j] = min(f[now][i][j], f[now][i][now + 1] + f[now][now + 1][j]);
                }
            }
            now++;
        }
        // for (int i = 0; i <= now; i++) {
        //     cout << f[i][x][y] << " ";
        // }
        int ans = f[now][x][y];
        if (x > now || y > now || ans == inf) ans = -1;
        cout << ans << "\n";
    }
}
